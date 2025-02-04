#include <windows.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>
#include <filesystem>
#include "nlohmann/json.hpp"
#include "OrcFxAPI.h"
#include "OrcFxAPI_wrapper.hpp"
#include "Utils.hpp"
#include "Actuator.hpp"

#define STRINGLENGTH 1024

using namespace Orcina;
using json = nlohmann::json;
namespace fs = std::filesystem;

const wchar_t controllerKeyName[] = L"BladedController";

typedef void (__cdecl *discon_func)(float*, int*, char*, char*, char*);

class Controller
{
public:
    Controller(TExtFnInfo& info)
        : model(info.ModelHandle), turbine(info.ObjectHandle), general(model.getGeneral()),
        environment(model.getEnvironment()), modelDirectory(info.lpModelDirectory)
    {
        try
        {
            initialise(info);
        }
        catch(const std::exception& exc)
        {
            unloadDll();
            throw;
        }
    }

    ~Controller()
    {
        if (!firstCall)
            finalise();
        unloadDll();
    }

    void initialise(TExtFnInfo& info)
    {
        if (turbine.getType() != otTurbine)
            throw std::runtime_error("External function must be associated with a turbine object.");

        setControlledBladeCount();

        dllCanBeShared = getBoolFromTag(turbine, L"ControllerDLLCanBeShared");
        useActuator = getBoolFromTag(turbine, L"UseActuator");

        setAccelRefPosRrtTurbine();

        lastUpdateTime = -std::numeric_limits<double>::infinity();

        simulationStartTime = model.getSimulationStartTime();

        momentScaleFactor = turbine.UnitsConversionFactor(L"FF.LL");
        velocityScaleFactor = turbine.UnitsConversionFactor(L"LL.TT^-1");
        accelerationScaleFactor = turbine.UnitsConversionFactor(L"LL.TT^-2");

        setTimeStep();

        if (useActuator)
            createActuators();

        loadDll();

        initialiseTextArguments(info.lpModelFileName);
    }

    void finalise()
    {
        // iStatus
        setRecord(1, -1);

        callDll();
    }

    void update(TExtFnInfo& info)
    {
        if (info.SimulationTime <= lastUpdateTime)
            return;

        const TTurbineInstantaneousCalculationData* const icd =
            static_cast<const TTurbineInstantaneousCalculationData* const>(info.lpInstantaneousCalculationData);

        lastUpdateTime = info.SimulationTime;

        if (firstCall)
        {
            torque = turbine.TimeHistory(L"Generator torque", pnInstantaneousValue)[0];
            yawError = std::numeric_limits<double>::quiet_NaN();
            nacelleYaw = std::numeric_limits<double>::quiet_NaN();
            setRecord(50, strnlen_s(accInfile, STRINGLENGTH));
            setRecord(51, strnlen_s(avcOutfile, STRINGLENGTH));
        }

        // iStatus
        setRecord(1, firstCall ? 0 : 1);

        firstCall = false;

        // length of avcMsg character array
        setRecord(49, STRINGLENGTH);

        // number of blades
        setRecord(61, icd->BladeCount);

        // blade pitch
        if (commonBladeControl)
        {
            double pitch = icd->BladePitchAngle;
            setRecord(28, 0); // 0 for common control
            setRecord(4, pitch);
            setRecord(33, pitch);
            setRecord(34, pitch);
        }
        else
        {
            setRecord(28, 1); // 1 for individual control
            for (int bladeIndex = 0; bladeIndex < controlledBladeCount; bladeIndex++)
            {
                int index = bladeIndex == 0 ? 4 : 33 + bladeIndex - 1;
                double pitch = radians(
                    turbine.TimeHistory(L"Blade pitch", pnInstantaneousValue, ObjectExtra::Turbine(1 + bladeIndex))[0]
                );
                setRecord(index, pitch);
            }
        }

        // yaw error
        double windDirection = environment.TimeHistory(L"Wind direction", pnInstantaneousValue, ObjectExtra::Environment(icd->TurbinePosition))[0];
        double turbineAzimuth = turbine.TimeHistory(L"Azimuth", pnInstantaneousValue)[0];
        yawError = suppressRangeJumps(yawError, windDirection - turbineAzimuth);
        setRecord(24, radians(yawError));

        // nacelle yaw angle from North
        setAzimuthNorth();
        nacelleYaw = suppressRangeJumps(
            nacelleYaw,
            turbineAzimuth - (azimuthNorth - 180)
        );
        setRecord(37, radians(nacelleYaw));

        // horizontal hub wind speed
        setRecord(27, icd->HorizontalHubWindSpeed / velocityScaleFactor);

        // rotor azimuth angle
        setRecord(60, icd->RotorAngle);

        // time
        setRecord(2, info.SimulationTime - simulationStartTime);

        // time step
        setRecord(3, dt);

        // generator speed
        setRecord(20, icd->GeneratorAngVel);

        // rotor speed
        setRecord(21, icd->MainShaftAngVel);

        // torque and power, DLL assumed to work in Nm
        double dllTorque = -torque * 1000 / momentScaleFactor;
        setRecord(23, dllTorque);
        setRecord(15, dllTorque * icd->GeneratorAngVel); // power not factored by efficiency

        // root in/out of plane bending moment, DLL assumed to work in Nm
        for (int bladeIndex = 0; bladeIndex < controlledBladeCount; bladeIndex++)
        {
            ObjectExtra oeBlade = ObjectExtra::Turbine(1 + bladeIndex);
            double ofMomentEx = turbine.TimeHistory(L"Root connection Ex moment", pnInstantaneousValue, oeBlade)[0];
            setRecord(69 + bladeIndex, -ofMomentEx * 1000 / momentScaleFactor);
            double ofMomentEy = turbine.TimeHistory(L"Root connection Ey moment", pnInstantaneousValue, oeBlade)[0];
            setRecord(30 + bladeIndex, -ofMomentEy * 1000 / momentScaleFactor);
        }

        // "nodding" acceleration
        TVector accelWrtTurbineRelGlobal = prod(icd->TurbineOrientation, icd->TurbineAcceleration);
        TVector angAccelWrtTurbineRelGlobal = icd->TurbineAngularAcceleration;
        if (!isZero(accelRefPosRrtTurbine))
        {
            TVector angVelWrtTurbineRelGlobal = icd->TurbineAngularVelocity;
            // calculate the translational acceleration at the user nominated acceleration reference position.
            accelWrtTurbineRelGlobal = sum(accelWrtTurbineRelGlobal, crossProd(angAccelWrtTurbineRelGlobal, accelRefPosRrtTurbine));
            accelWrtTurbineRelGlobal = sum(accelWrtTurbineRelGlobal, crossProd(angVelWrtTurbineRelGlobal, crossProd(angVelWrtTurbineRelGlobal, accelRefPosRrtTurbine)));
        }
        setRecord(53, accelWrtTurbineRelGlobal.Z / accelerationScaleFactor); // translational
        setRecord(83, -angAccelWrtTurbineRelGlobal.Y); // rotational, -ve convert to FAST coordinate system

        // hub moments
        double ofMomentLy = turbine.TimeHistory(L"Connection Ly moment", pnInstantaneousValue)[0];
        // assumes: DLL in Nm; ofx turbine Ly = -ve DLL Ly; and DLL load is rotor
        // side to gen side (whereas ofx connection load is parent to child)
        setRecord(75, ofMomentLy * 1000 / momentScaleFactor);

        double ofMomentLx = turbine.TimeHistory(L"Connection Lx moment", pnInstantaneousValue)[0];
        // assumes: DLL in Nm; ofx turbine Lx = DLL Lz; and DLL load is rotor
        // side to gen side (whereas ofx connection load is parent to child)
        setRecord(76, -ofMomentLx * 1000 / momentScaleFactor);

        callDll();

        if (aviFail < 0)
            throw std::runtime_error(std::string("Call to DISCON failed:\n") + avcMsg);

        // read output from DISCON and assign state to be returned by external functions
        pitch.clear();
        pitchDot.clear();
        pitchDotDot.clear();
        for (int bladeIndex = 0; bladeIndex < controlledBladeCount; bladeIndex++)
        {
            double pitchCommand = commonBladeControl ? getRecord(45) : getRecord(42 + bladeIndex);
            if (useActuator)
            {
                ActuatorState actuatorOutput = actuators[bladeIndex].output(pitchCommand);
                pitch.push_back(actuatorOutput.x);
                pitchDot.push_back(actuatorOutput.xdot);
                pitchDotDot.push_back(actuatorOutput.xdotdot);
            }
            else
            {
                pitch.push_back(pitchCommand);
                pitchDot.push_back(0);
                pitchDotDot.push_back(0);
            }
        }

        // DLL assumed to return value in Nm, first convert to OrcaFlex SI units (kN.m) and then to OrcaFlex model units
        torque = -getRecord(47) / 1000 * momentScaleFactor;

        yawDot = getRecord(48);
        yaw += yawDot * dt;
    }

    void calculate(TExtFnInfo& info)
    {
        update(info);
        switch (controlledVar(info.lpDataName))
        {
            case ControlledVar::torque:
            {
                info.Value = torque;
                break;
            }
            case ControlledVar::pitch:
            {
                TScalarStructValue *sv = static_cast<TScalarStructValue*>(info.lpStructValue);
                for (int bladeIndex = 0; bladeIndex < controlledBladeCount; bladeIndex++)
                {
                    sv[bladeIndex].Value = pitch[bladeIndex];
                    sv[bladeIndex].Velocity = pitchDot[bladeIndex];
                    sv[bladeIndex].Acceleration = pitchDotDot[bladeIndex];
                }
                break;
            }
        }
    }

    double getYaw()
    {
        return yaw;
    };

    double getYawDot()
    {
        return yawDot;
    };

    int addref()
    {
        return refCount++;
    }

    int decref()
    {
        return --refCount;
    }
private:
    GUID CreateGUID()
    {
        GUID result;
        if (!SUCCEEDED(CoCreateGuid(&result)))
            throw std::runtime_error("Cannot create GUID.");
        return result;
    }

    std::wstring GuidToString(const GUID guid)
    {
        wchar_t buff[37];
        swprintf(
            buff,
            sizeof(buff) / sizeof(wchar_t),
            L"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
            guid.Data1,
            guid.Data2,
            guid.Data3,
            guid.Data4[0],
            guid.Data4[1],
            guid.Data4[2],
            guid.Data4[3],
            guid.Data4[4],
            guid.Data4[5],
            guid.Data4[6],
            guid.Data4[7]
        );
        return buff;
    }

    std::wstring Win32errToString(DWORD err)
    {
        DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | 
            FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER;
        wchar_t* buffer;
        auto len = FormatMessage(flags, nullptr, err, 0, reinterpret_cast<wchar_t*>(&buffer), 0, nullptr);
        if (len == 0)
            return L"";
        std::wstring result = buffer;
        LocalFree(reinterpret_cast<HLOCAL>(buffer));
        return result;
    }

    bool convertTo8bitText(const std::wstring input, char* output, size_t outputLen)
    {
        BOOL usedDefaultChar;
        return WideCharToMultiByte(GetACP(), 0, input.c_str(), input.size(), output, outputLen, nullptr, &usedDefaultChar) && !usedDefaultChar;
    }

    bool tryGetBoolFromTag(OrcaFlexObject& modelObject, const std::wstring name, bool& value)
    {
        std::wstring tagValue;
        bool result = modelObject.tryGetTag(name, tagValue);
        if (!result)
        {
            value = false;
            return true;
        }
        if (tagValue == L"True")
        {
            value = true;
            return true;
        }
        if (tagValue == L"False")
        {
            value = false;
            return true;
        }
        value = false;
        return false;
    }

    bool getBoolFromTag(OrcaFlexObject& modelObject, const std::wstring name)
    {
        bool result;
        if (!tryGetBoolFromTag(turbine, name, result))
            throw std::runtime_error("Unrecognised value for " + utf16ToUtf8(name) + " tag: must be False or True.");
        return result;
    }

    double getDoubleFromTag(OrcaFlexObject& modelObject, const std::wstring name)
    {
        std::wstring wtext;
        if (!modelObject.tryGetTag(name, wtext))
            throw std::runtime_error(utf16ToUtf8(name) + " tag must be defined.");
        std::string text = utf16ToUtf8(wtext);
        double result;
        if (!TryStrToDouble(text, result))
            throw std::runtime_error("Cannot convert " + utf16ToUtf8(name) + " tag of " + text + " to numeric value.");
        return result;
    }

    float getRecord(const size_t index)
    {
        // convert between 1-based FORTRAN indexing and 0-based C++ indexing
        return avrSwap[index - 1];
    }

    void setRecord(const size_t index, const float value)
    {
        // convert between 1-based FORTRAN indexing and 0-based C++ indexing
        avrSwap[index - 1] = value;
    }

    void setControlledBladeCount()
    {
        if (turbine.DataNameValid(L"PitchControlMode")) // if v11.0a or later
        {
            commonBladeControl = turbine.GetDataString(L"PitchControlMode") == L"Common";
            controlledBladeCount = commonBladeControl ? 1 : turbine.GetDataInteger(L"BladeCount");
            if (controlledBladeCount > 3)
                throw std::runtime_error("Must not use pitch control on more than three blades.");
        }
        else
            throw std::runtime_error("Wrapper only supports OrcaFlex v11.0a and later.");
    }

    void setAccelRefPosRrtTurbine()
    {
        std::wstring posText;
        if (!turbine.tryGetTag(L"AccelRefPosRrtTurbine", posText))
            return;

        try
        {
            std::array<double, 3> data = json::parse(posText);
            accelRefPosRrtTurbine.X = data[0];
            accelRefPosRrtTurbine.Y = data[1];
            accelRefPosRrtTurbine.Z = data[2];
            return;
        }
        catch(const json::parse_error& exc)
        {
            throw std::runtime_error(std::string("Could not parse AccelRefPosRrtTurbine JSON, ") + exc.what() + ".");
        }
    }

    void setTimeStep()
    {
        int status;
        C_GetDataDouble(general.getHandle(), L"ActualOuterTimeStep", 0, &dt, &status);
        if (status == stOK)
            return;

        C_GetDataDouble(general.getHandle(), L"ImplicitConstantTimeStep", 0, &dt, &status);
        if (status == stOK)
            return;

        throw std::runtime_error("Turbine controllers require a constant time step.");
    }

    void setAzimuthNorth()
    {
        int status;
        C_GetDataDouble(general.getHandle(), L"NorthDirection", 0, &azimuthNorth, &status);
        if (status == stOK)
            return;
        if (status == stValueNotAvailable)
        {
            // assume 180 deg, so 0 deg wind is from North
            azimuthNorth = 180;
            return;
        }

        throw std::runtime_error("North direction cannot be determined.");
    }

    void createActuators()
    {
        double omega = getDoubleFromTag(turbine, L"ActuatorOmega");
        double gamma = getDoubleFromTag(turbine, L"ActuatorGamma");
        for (int bladeIndex = 0; bladeIndex < controlledBladeCount; bladeIndex++)
            actuators.push_back(Actuator(omega, gamma, dt));
    }

    void initialiseTextArguments(const std::wstring modelFileName)
    {
        std::wstring value;
        if (turbine.tryGetTag(L"InputFile", value) && !convertTo8bitText(fs::path(modelDirectory) / value, accInfile, STRINGLENGTH))
            throw std::runtime_error("Could not convert input file name to 8 bit text.");

        /* Specify a file name that dll output can be written to. In this example, we combine the
           model name, the turbine object name and add 5 extra characters. In the specific case of
           the ROSCO control dll, these extra characters will be removed and replace with 'RO.dbg' */
        value = fs::path(modelFileName).replace_extension("").generic_wstring() + L"_" + turbine.getName() + L"_     ";
        if (!convertTo8bitText(value, avcOutfile, STRINGLENGTH))
            throw std::runtime_error("Could not convert output file name to 8 bit text.");
    }

    void loadDll()
    {
        std::wstring sourceDllFileName = fs::path(modelDirectory) / turbine.getTag(L"ControllerDLL");
        if (dllCanBeShared)
            dllFileName = sourceDllFileName;
        else
        {
            std::wstring tmp = GuidToString(CreateGUID()) + L".dll";
            dllFileName = fs::path(fs::temp_directory_path()) / tmp;
            fs::copy(sourceDllFileName, dllFileName);
        }
        lib = LoadLibrary(dllFileName.c_str());
        if (!lib)
        {
            auto err = GetLastError();
            std::wstring msg = L"Could not load DLL " + sourceDllFileName + L", error code " + std::to_wstring(err) 
                + L", " + Win32errToString(err);
            throw std::runtime_error(utf16ToUtf8(msg));
        }

        discon = reinterpret_cast<discon_func>(GetProcAddress(lib, "DISCON"));
        if (!discon)
        {
            std::wstring msg = L"Could not import function named DISCON from DLL " + sourceDllFileName + L".";
            throw std::runtime_error(utf16ToUtf8(msg));
        }
    }

    void unloadDll()
    {
        if (lib)
            FreeLibrary(lib);
        if (!dllCanBeShared && !dllFileName.empty())
        {
            std::error_code err;
            fs::remove(dllFileName, err); // ignore errors
        }
    }

    void callDll()
    {
        discon(avrSwap, &aviFail, accInfile, avcOutfile, avcMsg);
    }
private:
    OrcaFlexModel model;
    OrcaFlexObject turbine;
    OrcaFlexObject general;
    OrcaFlexObject environment;
    std::wstring modelDirectory;
    int refCount = 0;
    bool commonBladeControl = false;
    int controlledBladeCount = -1;
    bool dllCanBeShared = false;
    bool useActuator = false;
    TVector accelRefPosRrtTurbine = { 0 };
    double lastUpdateTime = std::numeric_limits<double>::quiet_NaN();
    bool firstCall = true;
    double simulationStartTime = std::numeric_limits<double>::quiet_NaN();
    double momentScaleFactor = std::numeric_limits<double>::quiet_NaN();
    double velocityScaleFactor = std::numeric_limits<double>::quiet_NaN();
    double accelerationScaleFactor = std::numeric_limits<double>::quiet_NaN();
    double yaw = 0;
    double yawDot = 0;
    double dt = std::numeric_limits<double>::quiet_NaN();
    std::wstring dllFileName = L"";
    HMODULE lib = 0;
    discon_func discon = nullptr;
    float avrSwap[84] = { 0 };
    int aviFail = 0;
    char accInfile[STRINGLENGTH] = { 0 };
    char avcOutfile[STRINGLENGTH] = { 0 };
    char avcMsg[STRINGLENGTH] = { 0 };
    double torque = std::numeric_limits<double>::quiet_NaN();
    double yawError = std::numeric_limits<double>::quiet_NaN();
    double nacelleYaw = std::numeric_limits<double>::quiet_NaN();
    double azimuthNorth = std::numeric_limits<double>::quiet_NaN();
    std::vector<Actuator> actuators;
    std::vector<double> pitch;
    std::vector<double> pitchDot;
    std::vector<double> pitchDotDot;
};

extern "C"
{

void __stdcall BladedController(TExtFnInfo& info)
{
    try
    {
        switch(info.Action)
        {
        case eaInitialise:
        {
            int status;
            INT_PTR controllerPtr = C_GetNamedValue(info.ObjectHandle, controllerKeyName, &status);
            if (!checkStatus(info, L"Call to C_GetNamedValue from eaInitialise", status))
                return;

            Controller *controller;
            if (controllerPtr)
                controller = reinterpret_cast<Controller*>(controllerPtr);
            else
            {
                try
                {
                    controller = new Controller(info);
                }
                catch(const std::exception& exc)
                {
                    int status;
                    std::wstring error = OrcaFlexObject(info.ObjectHandle).getName() + L"\n\n" +
                        utf8ToUtf16(std::string("Could not initialise controller. ") + exc.what());
                    C_RecordExternalFunctionError(&info, error.c_str(), &status); // ignore status
                    return;
                }

                controllerPtr = reinterpret_cast<INT_PTR>(controller);
                C_SetNamedValue(info.ObjectHandle, controllerKeyName, controllerPtr, &status);
                if (!checkStatus(info, L"Call to C_SetNamedValue from eaInitialise", status))
                    return;
            }
            controller->addref();
            info.lpData = static_cast<void*>(controller);
            break;
        }
        case eaFinalise:
        {
            Controller *controller = static_cast<Controller*>(info.lpData);
            if (controller->decref() == 0)
            {
                int status;
                C_SetNamedValue(info.ObjectHandle, controllerKeyName, 0, &status);
                if (!checkStatus(info, L"Call to C_SetNamedValue from eaFinalise", status))
                    return;
                delete controller;
            }
            break;
        }
        case eaCalculate:
        {
            Controller *controller = static_cast<Controller*>(info.lpData);
            try
            {
                controller->calculate(info);
            }
            catch(const std::exception& exc)
            {
                int status;
                std::wstring error = OrcaFlexObject(info.ObjectHandle).getName() + L"\n\n" + utf8ToUtf16(exc.what());
                C_RecordExternalFunctionError(&info, error.c_str(), &status); // ignore status
                return;
            }
            break;
        }
        }
    }
    catch(const std::exception& exc)
    {
        int status;
        std::wstring msg = L"Unexpected error, " + utf8ToUtf16(exc.what());
        C_RecordExternalFunctionError(&info, msg.c_str(), &status); // ignore status
    }
}

void __stdcall YawController(TExtFnInfo& info)
{
    try
    {
        switch(info.Action)
        {
        case eaInitialise:
        {
            int status;
            OrcaFlexObject modelObject(info.ObjectHandle);
            std::wstring objectName = modelObject.GetDataString(L"Name");
            std::wstring turbineName;
            if (!modelObject.tryGetTag(L"TurbineName", turbineName))
                throw std::runtime_error(
                  "to use the constraint '" + utf16ToUtf8(objectName) + "' to impose yaw controller demand, "
                  "it must have an object tag named 'TurbineName', which should contain the associated turbine object name. "
                  "No such tag was found."
                );

            TObjectInfo objectInfo;
            C_ObjectCalled(info.ModelHandle, turbineName.c_str(), &objectInfo, &status);
            std::wstring msg = L"The '" + objectName + L"' constraint is being used to impose yaw controller demand for '" +
                               turbineName + L"'. However, this turbine cannot be found in the model. Please review the 'TurbineName' object "
                               L"tag for '" + objectName + L"', ";
            if (!checkStatus(info, msg, status))
                return;

            info.lpData = static_cast<void*>(objectInfo.ObjectHandle);
            break;
        }
        case eaCalculate:
        {
            int status;

            TOrcFxAPIHandle turbineHandle = static_cast<TOrcFxAPIHandle>(info.lpData);
            INT_PTR controllerPtr = C_GetNamedValue(turbineHandle, controllerKeyName, &status);
            if (!checkStatus(info, L"Call to C_GetNamedValue from eaCalculate", status))
                return;

            Controller *controller;
            if (controllerPtr)
                controller = reinterpret_cast<Controller*>(controllerPtr);
            else
                throw std::runtime_error("the turbine's controller was not found. Ensure controllers are active for the associated turbine object.");

            double yaw = controller->getYaw();
            double yawDot = controller->getYawDot();

            double c = cos(yaw);
            double s = sin(yaw);

            TExternallyCalculatedImposedMotionStructValue* motionValue = 
                static_cast<TExternallyCalculatedImposedMotionStructValue*>(info.lpStructValue);

            motionValue->Orientation = {
                { c, s, 0 },
                { -s, c, 0 },
                { 0, 0, 1 }
            };
            motionValue->AngularVelocity = { 0.0, 0.0, yawDot };
            break;
        }
        }
    }
    catch(const std::exception& exc)
    {
        int status;
        std::wstring msg = L"Unexpected error, " + utf8ToUtf16(exc.what());
        C_RecordExternalFunctionError(&info, msg.c_str(), &status); // ignore status
    }
}

}