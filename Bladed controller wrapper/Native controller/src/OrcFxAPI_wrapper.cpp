#include <vector>
#include "OrcFxAPI_wrapper.hpp"

namespace Orcina {

template<typename T>
class Backref
{
public:
    Backref(const T* ref, TOrcFxAPIHandle handle, const wchar_t* name) : handle(handle), name(name)
    {
        int status;
        C_SetNamedValue(handle, name, reinterpret_cast<INT_PTR>(ref), &status);
        checkStatus(status);
    }
    ~Backref()
    {
        int status;
        C_SetNamedValue(handle, name, 0, &status);
        checkStatus(status);
    }
    static T* getRef(TOrcFxAPIHandle handle, const wchar_t* name)
    {
        int status;
        INT_PTR value = C_GetNamedValue(handle, name, &status);
        checkStatus(status);
        return reinterpret_cast<T*>(value);
    }
private:
    TOrcFxAPIHandle handle;
    const wchar_t* name;
};

void checkStatus(int status)
{
    if (status != stOK)
    {
        int length = C_GetLastErrorStringA(nullptr);
        std::vector<char> msg(length);
        C_GetLastErrorStringA(&msg[0]);
        throw OrcFxAPI_error(status, std::string(&msg[0], length-1));
    }
}

std::wstring DLLVersion()
{
    int status;
    int OK;
    TDLLVersion version;
    C_GetDLLVersion(nullptr, &version, &OK, &status);
    checkStatus(status);
    return version;
}

int BinaryFileType(const std::wstring& fileName)
{
    int status;
    int result;
    C_GetBinaryFileType(fileName.c_str(), &result, &status);
    checkStatus(status);
    return result;
}

std::wstring FileCreatorVersion(const std::wstring fileName)
{
    int status;
    int length = C_GetFileCreatorVersion(fileName.c_str(), nullptr, &status);
    checkStatus(status);

    std::vector<wchar_t> value(length);
    C_GetFileCreatorVersion(fileName.c_str(), &value[0], &status);
    checkStatus(status);
    return std::wstring(&value[0], length-1);
}

// Period

Period Period::Default(int modelState)
{
    int periodNum = (modelState == msInStaticState) ? pnStaticState : pnWholeSimulation;
    return Period(periodNum);
}

Period::operator const TPeriod () const
{
    TPeriod result = { periodNum, 0, fromTime, toTime };
    return result;
}

// ObjectExtra

ObjectExtra ObjectExtra::Environment(double X, double Y, double Z)
{
    TVector pos = { X, Y, Z };
    return Environment(pos);
}

ObjectExtra ObjectExtra::Environment(const TVector& pos)
{
    ObjectExtra result;
    result.environmentPos = pos;
    return result;
}


ObjectExtra ObjectExtra::Buoy(double X, double Y, double Z)
{
    TVector pos = { X, Y, Z };
    return Buoy(pos);
}

ObjectExtra ObjectExtra::Buoy(const TVector& pos)
{
    ObjectExtra result;
    result.rigidBodyPos = pos;
    return result;
}

ObjectExtra ObjectExtra::Wing(const std::wstring& name)
{
    ObjectExtra result;
    result.wingName = name;
    return result;
}

ObjectExtra ObjectExtra::Vessel(double X, double Y, double Z)
{
    TVector pos = { X, Y, Z };
    return Vessel(pos);
}

ObjectExtra ObjectExtra::Vessel(const TVector& pos)
{
    ObjectExtra result;
    result.rigidBodyPos = pos;
    return result;
}

ObjectExtra ObjectExtra::AirGap(double X, double Y, double Z, double seaSurfaceScalingFactor)
{
    TVector pos = { X, Y, Z };
    return AirGap(pos, seaSurfaceScalingFactor);
}

ObjectExtra ObjectExtra::AirGap(const TVector& pos, double seaSurfaceScalingFactor)
{
    ObjectExtra result;
    result.rigidBodyPos = pos;
    result.seaSurfaceScalingFactor = seaSurfaceScalingFactor;
    return result;
}

ObjectExtra ObjectExtra::Constraint(double X, double Y, double Z)
{
    TVector pos = { X, Y, Z };
    return Constraint(pos);
}

ObjectExtra ObjectExtra::Constraint(const TVector& pos)
{
    ObjectExtra result;
    result.rigidBodyPos = pos;
    return result;
}

ObjectExtra ObjectExtra::Support(int supportIndex)
{
    ObjectExtra result;
    result.supportIndex = supportIndex;
    return result;
}

ObjectExtra ObjectExtra::Support(int supportIndex, const std::wstring& supportedLineName)
{
    ObjectExtra result;
    result.supportIndex = supportIndex;
    result.supportedLineName = supportedLineName;
    return result;
}

ObjectExtra ObjectExtra::Winch(int connectionPoint)
{
    ObjectExtra result;
    result.winchConnectionPoint = connectionPoint;
    return result;
}

ObjectExtra ObjectExtra::LineNodeNum(int nodeNum)
{
    ObjectExtra result;
    result.linePoint = ptNodeNum;
    result.nodeNum = nodeNum;
    return result;
}

ObjectExtra ObjectExtra::LineArclength(double arclength)
{
    ObjectExtra result;
    result.linePoint = ptArcLength;
    result.arclength = arclength;
    return result;
}

ObjectExtra ObjectExtra::LineEndA()
{
    ObjectExtra result;
    result.linePoint = ptEndA;
    return result;
}

ObjectExtra ObjectExtra::LineEndB()
{
    ObjectExtra result;
    result.linePoint = ptEndB;
    return result;
}

ObjectExtra ObjectExtra::LineTouchdown()
{
    ObjectExtra result;
    result.linePoint = ptTouchdown;
    return result;
}

ObjectExtra ObjectExtra::Turbine(int bladeIndex, double arclength)
{
    ObjectExtra result;
    result.linePoint = ptArcLength;
    result.arclength = arclength;
    result.bladeIndex = bladeIndex;
    return result;
}

ObjectExtra ObjectExtra::Turbine(int bladeIndex)
{
    ObjectExtra result;
    result.bladeIndex = bladeIndex;
    return result;
}

ObjectExtra ObjectExtra::TurbineEndA(int bladeIndex)
{
    ObjectExtra result;
    result.linePoint = ptEndA;
    result.bladeIndex = bladeIndex;
    return result;
}

ObjectExtra ObjectExtra::TurbineEndB(int bladeIndex)
{
    ObjectExtra result;
    result.linePoint = ptEndB;
    result.bladeIndex = bladeIndex;
    return result;
}

ObjectExtra ObjectExtra::MorisonElement(int elementIndex, double arclength)
{
    ObjectExtra result;
    result.linePoint = ptArcLength;
    result.arclength = arclength;
    result.elementIndex = elementIndex;
    return result;
}

ObjectExtra ObjectExtra::MorisonElement(int elementIndex)
{
    ObjectExtra result;
    result.elementIndex = elementIndex;
    return result;
}

ObjectExtra::operator const TObjectExtra2 () const
{
    TObjectExtra2 result = { sizeof(result) };
    result.EnvironmentPos = environmentPos;
    result.LinePoint = linePoint;
    result.NodeNum = nodeNum;
    result.ArcLength = arclength;
    result.RadialPos = radialPos;
    result.Theta = theta;
    result.WingName = wingName.c_str();
    result.ClearanceLineName = clearanceLineName.c_str();
    result.WinchConnectionPoint = winchConnectionPoint;
    result.RigidBodyPos = rigidBodyPos;
    result.ExternalResultText = externalResultText.c_str();
    result.DisturbanceVesselName = disturbanceVesselName.c_str();
    result.SupportIndex = supportIndex;
    result.SupportedLineName = supportedLineName.c_str();
    result.BladeIndex = bladeIndex;
    result.ElementIndex = elementIndex;
    return result;
}

// ArclengthRange

ArclengthRange::operator const TArclengthRange () const
{
    TArclengthRange result = { sizeof(result) };
    result.Mode = mode;
    result.FromArclength = fromArclength;
    result.ToArclength = toArclength;
    result.FromSection = fromSection;
    result.ToSection = toSection;
    return result;
}

// ViewParameters

ViewParameters::operator const TViewParameters () const
{
    TViewParameters result = { sizeof(result) };
    result.ViewSize = viewSize;
    result.ViewAzimuth = viewAzimuth;
    result.ViewElevation = viewElevation;
    result.ViewCentre = viewCentre;
    result.Height = height;
    result.Width = width;
    result.BackgroundColour = backgroundColour;
    result.DrawViewAxes = drawViewAxes;
    result.DrawScaleBar = drawScaleBar;
    result.DrawGlobalAxes = drawGlobalAxes;
    result.DrawEnvironmentAxes = drawEnvironmentAxes;
    result.DrawLocalAxes = drawLocalAxes;
    result.DrawOutOfBalanceForces = drawOutOfBalanceForces;
    result.DrawNodeAxes = drawNodeAxes;
    result.GraphicsMode = graphicsMode;
    result.FileFormat = fileFormat;
    result.ViewGamma = viewGamma;
    result.RelativeToObjectHandle = relativeToObjectHandle;
    result.DisturbanceVesselHandle = disturbanceVesselHandle;
    result.DisturbancePosition = disturbancePosition;
    result.ShadedFillMode = shadedFillMode;
    result.DrawNameLabels = drawNameLabels;
    result.DrawConnections = drawConnections;
    result.LabelScale = labelScale;
    result.DrawOrigins = drawOrigins;
    result.MonochromeOutput = monochromeOutput;
    result.AddDetailsToOutput = addDetailsToOutput;
    result.JpegCompressionQuality = jpegCompressionQuality;
    return result;
}

// DataObject

int DataObject::GetDataType(const std::wstring& dataName) const
{
    int status;
    int result;
    C_GetDataType(handle, dataName.c_str(), &result, &status);
    checkStatus(status);
    return result;
}

int DataObject::GetVariableDataType(const std::wstring& dataName, int index) const
{
    int status;
    int result;
    C_GetVariableDataType(handle, dataName.c_str(), index+1, &result, &status);
    checkStatus(status);
    return result;
}

bool DataObject::DataNameValid(const std::wstring& dataName) const
{
    int status;
    int dataType;
    C_GetDataType(handle, dataName.c_str(), &dataType, &status);
    return status == stOK;
}

bool DataObject::DataRequiresIndex(const std::wstring& dataName) const
{
    int status;
    BOOL result;
    C_DataRequiresIndex(handle, dataName.c_str(), &result, &status);
    checkStatus(status);
    return result;
}

void DataObject::BeginDataChange()
{
    int status;
    C_BeginDataChange(handle, &status);
    checkStatus(status);
}

void DataObject::EndDataChange()
{
    int status;
    C_EndDataChange(handle, &status);
    checkStatus(status);
}

int DataObject::GetDataRowCount(const std::wstring& dataName) const
{
    int status;
    int result;
    C_GetDataRowCount(handle, dataName.c_str(), &result, &status);
    checkStatus(status);
    return result;
}

void DataObject::SetDataRowCount(const std::wstring& dataName, int value)
{
    int status;
    C_SetDataRowCount(handle, dataName.c_str(), value, &status);
    checkStatus(status);
}

void DataObject::InsertDataRow(const std::wstring& indexedDataName, int index)
{
    int status;
    C_InsertDataRow(handle, indexedDataName.c_str(), index+1, &status);
    checkStatus(status);
}

void DataObject::DeleteDataRow(const std::wstring& indexedDataName, int index)
{
    int status;
    C_DeleteDataRow(handle, indexedDataName.c_str(), index+1, &status);
    checkStatus(status);
}

double DataObject::GetDataDouble(const std::wstring& dataName, int index) const
{
    int status;
    double result;
    C_GetDataDouble(handle, dataName.c_str(), index+1, &result, &status);
    checkStatus(status);
    return result;
}

double DataObject::GetDataDouble(const std::wstring& dataName) const
{
    return GetDataDouble(dataName, -1);
}

std::vector<double> DataObject::GetDataDoubleArray(const std::wstring& dataName) const
{
    int count = GetDataRowCount(dataName);
    std::vector<double> result(count);
    for (int i=0; i<count; i++)
    {
        result[i] = GetDataDouble(dataName, i);
    }
    return result;
}

void DataObject::SetDataDouble(const std::wstring& dataName, int index, double value)
{
    int status;
    C_SetDataDouble(handle, dataName.c_str(), index+1, value, &status);
    checkStatus(status);
}

void DataObject::SetDataDouble(const std::wstring& dataName, double value)
{
    SetDataDouble(dataName, -1, value);
}

void DataObject::SetDataDoubleArray(const std::wstring& dataName, const std::vector<double>& values)
{
    int count = static_cast<int>(values.size());
    SetDataRowCount(dataName, count);
    for (int i=0; i<count; i++)
    {
        SetDataDouble(dataName, i, values[i]);
    }
}

int DataObject::GetDataInteger(const std::wstring& dataName, int index) const
{
    int status;
    int result;
    C_GetDataInteger(handle, dataName.c_str(), index+1, &result, &status);
    checkStatus(status);

    int dataType;
    C_GetDataType(handle, dataName.c_str(), &dataType, &status);
    checkStatus(status);
    if (dataType == dtIntegerIndex)
    {
        result--;
    }

    return result;
}

int DataObject::GetDataInteger(const std::wstring& dataName) const
{
    return GetDataInteger(dataName, -1);
}

std::vector<int> DataObject::GetDataIntegerArray(const std::wstring& dataName) const
{
    int count = GetDataRowCount(dataName);
    std::vector<int> result(count);
    for (int i=0; i<count; i++)
    {
        result[i] = GetDataInteger(dataName, i);
    }
    return result;
}

void DataObject::SetDataInteger(const std::wstring& dataName, int index, int value)
{
    int status;
    int dataType;
    C_GetDataType(handle, dataName.c_str(), &dataType, &status);
    checkStatus(status);
    if (dataType == dtIntegerIndex)
    {
        value++;
    }

    C_SetDataInteger(handle, dataName.c_str(), index + 1, value, &status);
    checkStatus(status);
}

void DataObject::SetDataInteger(const std::wstring& dataName, int value)
{
    SetDataInteger(dataName, -1, value);
}

void DataObject::SetDataIntegerArray(const std::wstring& dataName, const std::vector<int>& values)
{
    int count = static_cast<int>(values.size());
    SetDataRowCount(dataName, count);
    for (int i=0; i<count; i++)
    {
        SetDataInteger(dataName, i, values[i]);
    }
}

std::wstring DataObject::GetDataString(const std::wstring& dataName, int index) const
{
    int status;
    int length = C_GetDataString(handle, dataName.c_str(), index+1, nullptr, &status);
    checkStatus(status);

    std::vector<wchar_t> value(length);
    C_GetDataString(handle, dataName.c_str(), index+1, &value[0], &status);
    checkStatus(status);
    return std::wstring(&value[0], length-1);
}

std::wstring DataObject::GetDataString(const std::wstring& dataName) const
{
    return GetDataString(dataName, -1);
}

std::vector<std::wstring> DataObject::GetDataStringArray(const std::wstring& dataName) const
{
    int count = GetDataRowCount(dataName);
    std::vector<std::wstring> result(count);
    for (int i=0; i<count; i++)
    {
        result[i] = GetDataString(dataName, i);
    }
    return result;
}

void DataObject::SetDataString(const std::wstring& dataName, int index, const std::wstring& value)
{
    int status;
    C_SetDataString(handle, dataName.c_str(), index+1, value.c_str(), &status);
    checkStatus(status);
}

void DataObject::SetDataString(const std::wstring& dataName, const std::wstring& value)
{
    SetDataString(dataName, -1, value);
}

void DataObject::SetDataStringArray(const std::wstring& dataName, const std::vector<std::wstring>& values)
{
    int count = static_cast<int>(values.size());
    SetDataRowCount(dataName, count);
    for (int i=0; i<count; i++)
    {
        SetDataString(dataName, i, values[i]);
    }
}

double DataObject::UnitsConversionFactor(const std::wstring& units)
{
    int status;
    double result;
    C_GetUnitsConversionFactor(handle, units.c_str(), &result, &status);
    checkStatus(status);
    return result;
}

// OrcaFlexObject

OrcaFlexObject OrcaFlexObject::CreateClone(const std::wstring& name, TOrcFxAPIHandle modelHandle) const
{
    int status;
    TOrcFxAPIHandle clonedObjectHandle;
    C_CreateClone2(handle, modelHandle, &clonedObjectHandle, &status);
    checkStatus(status);

    OrcaFlexObject result = OrcaFlexObject(handle, clonedObjectHandle, type);
    if (!name.empty())
    {
        result.setName(name);
    }
    return result;
}

OrcaFlexObject OrcaFlexObject::CreateClone(const std::wstring& name, OrcaFlexModel& model) const
{
    return CreateClone(name, model.getHandle());
}

OrcaFlexObject OrcaFlexObject::CreateClone(const std::wstring& name) const
{
    return CreateClone(name, modelHandle);
}

OrcaFlexObject OrcaFlexObject::CreateClone(OrcaFlexModel& model) const
{
    return CreateClone(L"", model.getHandle());
}

OrcaFlexObject OrcaFlexObject::CreateClone() const
{
    return CreateClone(L"", modelHandle);
}

void OrcaFlexObject::InvokeWizard()
{
    int status;
    C_InvokeWizard(handle, &status);
    checkStatus(status);
}

TOrcFxAPIHandle OrcaFlexObject::getModelHandle(TOrcFxAPIHandle handle)
{
    int status;
    TOrcFxAPIHandle result;
    C_GetModelHandle(handle, &result, &status);
    checkStatus(status);

    return result;
}

int OrcaFlexObject::getType(TOrcFxAPIHandle handle)
{
    int status;
    int length = C_GetDataString(handle, L"name", -1, nullptr, &status);
    checkStatus(status);

    std::vector<wchar_t> value(length);
    C_GetDataString(handle, L"name", -1, &value[0], &status);
    checkStatus(status);
    auto name = std::wstring(&value[0], length - 1);

    TObjectInfo objectInfo;
    C_ObjectCalled(getModelHandle(handle), name.c_str(), &objectInfo, &status);
    checkStatus(status);

    return objectInfo.ObjectType;
}

int OrcaFlexObject::getVarID(const std::wstring& varName) const
{
    int status;
    int result;
    C_GetVarID(handle, varName.c_str(), &result, &status);
    checkStatus(status);
    return result;
}

int OrcaFlexObject::getModelState() const
{
    return OrcaFlexModel::getState(modelHandle);
}

bool OrcaFlexObject::tryGetTag(const std::wstring name, std::wstring &value) const
{
    int status;
    int length = C_GetTag(handle, name.c_str(), nullptr, &status);
    if (status == stTagNotFound)
    {
        value = L"";
        return false;
    }
    checkStatus(status);

    std::vector<wchar_t> buff(length);
    C_GetTag(handle, name.c_str(), &buff[0], &status);
    checkStatus(status);

    value = std::wstring(&buff[0], length-1);
    return true;
}

std::wstring OrcaFlexObject::getTag(const std::wstring name) const
{
    std::wstring value;
    tryGetTag(name, value);
    return value;
}

static const wchar_t* EnumerateVarsBackrefName = L"__EnumerateVarsBackref";

void __stdcall EnumerateVarsProc(const TVarInfo* varInfo)
{
    std::vector<std::wstring>* vars = Backref<std::vector<std::wstring>>::getRef(varInfo->ObjectHandle, EnumerateVarsBackrefName);
    vars->push_back(varInfo->lpVarName);
}

std::vector<std::wstring> OrcaFlexObject::Vars(int resultType, const TObjectExtra2* objectExtra) const
{
    int status;
    int varCount;
    std::vector<std::wstring> result;
    Backref<std::vector<std::wstring>> backref(&result, handle, EnumerateVarsBackrefName);
    C_EnumerateVars2(handle, objectExtra, resultType, EnumerateVarsProc, &varCount, &status);
    checkStatus(status);
    return result;
}

std::vector<std::wstring> OrcaFlexObject::Vars(int resultType, const ObjectExtra& objectExtra) const
{
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return Vars(resultType, &apiObjectExtra);
}

std::vector<std::wstring> OrcaFlexObject::Vars(const ObjectExtra& objectExtra) const
{
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return Vars(rtTimeHistory, &apiObjectExtra);
}

std::vector<std::wstring> OrcaFlexObject::Vars(int resultType) const
{
    return Vars(resultType, nullptr);
}

std::vector<std::wstring> OrcaFlexObject::Vars() const
{
    return Vars(rtTimeHistory, nullptr);
}

static const wchar_t* EnumerateVarDetailsBackrefName = L"__EnumerateVarDetailsBackref";

void __stdcall EnumerateVarDetailsProc(const TVarInfo* varInfo)
{
    std::vector<Orcina::VarDetails>* vars = Backref<std::vector<Orcina::VarDetails>>::getRef(varInfo->ObjectHandle, EnumerateVarDetailsBackrefName);
    vars->push_back(Orcina::VarDetails(varInfo->lpVarName, varInfo->lpVarUnits, varInfo->lpFullName));
}

std::vector<Orcina::VarDetails> OrcaFlexObject::VarDetails(int resultType, const TObjectExtra2* objectExtra) const
{
    int status;
    int varCount;
    std::vector<Orcina::VarDetails> result;
    Backref<std::vector<Orcina::VarDetails>> backref(&result, handle, EnumerateVarDetailsBackrefName);
    C_EnumerateVars2(handle, objectExtra, resultType, EnumerateVarDetailsProc, &varCount, &status);
    checkStatus(status);
    return result;
}

std::vector<Orcina::VarDetails> OrcaFlexObject::VarDetails(int resultType, const ObjectExtra& objectExtra) const
{
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return VarDetails(resultType, &apiObjectExtra);
}

std::vector<Orcina::VarDetails> OrcaFlexObject::VarDetails(const ObjectExtra& objectExtra) const
{
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return VarDetails(rtTimeHistory, &apiObjectExtra);
}

std::vector<Orcina::VarDetails> OrcaFlexObject::VarDetails(int resultType) const
{
    return VarDetails(resultType, nullptr);
}

std::vector<Orcina::VarDetails> OrcaFlexObject::VarDetails() const
{
    return VarDetails(rtTimeHistory, nullptr);
}

Period OrcaFlexObject::getDefaultPeriod() const
{
    return Period::Default(getModelState());
}

int OrcaFlexObject::getNumOfSamples(const TPeriod* period) const
{
    int status;
    int result = C_GetNumOfSamples(modelHandle, period, &status);
    checkStatus(status);
    return result;
}

std::vector<double> OrcaFlexObject::TimeHistory(const std::wstring& varName, const TObjectExtra2* objectExtra, const TPeriod* period) const
{
    int status;
    std::vector<double> result(getNumOfSamples(period));
    C_GetTimeHistory2(handle, objectExtra, period, getVarID(varName), &result[0], &status);
    checkStatus(status);
    return result;
}

std::vector<double> OrcaFlexObject::TimeHistory(const std::wstring& varName, const Period& period, const ObjectExtra& objectExtra) const
{
    const TPeriod apiPeriod = period;
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return TimeHistory(varName, &apiObjectExtra, &apiPeriod);
}

std::vector<double> OrcaFlexObject::TimeHistory(const std::wstring& varName, const ObjectExtra& objectExtra) const
{
    const TPeriod apiPeriod = getDefaultPeriod();
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return TimeHistory(varName, &apiObjectExtra, &apiPeriod);
}

std::vector<double> OrcaFlexObject::TimeHistory(const std::wstring& varName, const Period& period) const
{
    const TPeriod apiPeriod = period;
    return TimeHistory(varName, nullptr, &apiPeriod);
}

std::vector<double> OrcaFlexObject::TimeHistory(const std::wstring& varName) const
{
    const TPeriod apiPeriod = getDefaultPeriod();
    return TimeHistory(varName, nullptr, &apiPeriod);
}

double OrcaFlexObject::StaticResult(const std::wstring& varName, const TObjectExtra2* objectExtra) const
{
    int status;
    double result;
    C_GetStaticResult2(handle, objectExtra, getVarID(varName), &result, &status);
    checkStatus(status);
    return result;
}

double OrcaFlexObject::StaticResult(const std::wstring& varName, const ObjectExtra& objectExtra) const
{
    const TObjectExtra2 apiObjectExtra = objectExtra;
    return StaticResult(varName, &apiObjectExtra);
}

double OrcaFlexObject::StaticResult(const std::wstring& varName) const
{
    return StaticResult(varName, nullptr);
}

std::vector<double> OrcaFlexObject::RangeGraphXaxis(const std::wstring& varName, const TArclengthRange* arclengthRange, const TPeriod* period) const
{
    int status;
    int varID = getVarID(varName);
    TPeriod apiPeriod;
    if (period == nullptr)
    {
        BOOL isFrequencyDomainDynamics;
        C_GetModelProperty(handle, propIsFrequencyDomainDynamics, &isFrequencyDomainDynamics, &status);
        checkStatus(status);
        if (isFrequencyDomainDynamics)
        {
            apiPeriod = Period(pnStaticState);
        } else {
            apiPeriod = getDefaultPeriod();
        }
        period = &apiPeriod;
    }
    int pointCount = C_GetRangeGraphNumOfPoints3(handle, period, arclengthRange, varID, &status);
    checkStatus(status);
    std::vector<double> result(pointCount);
    C_GetRangeGraph4(handle, nullptr, period, arclengthRange, varID, &result[0], nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &status);
    return result;
}

std::vector<double> OrcaFlexObject::RangeGraphXaxis(const std::wstring& varName, const ArclengthRange& arclengthRange, const Period& period) const
{
    const TPeriod apiPeriod = period;
    const TArclengthRange apiArclengthRange = arclengthRange;
    return RangeGraphXaxis(varName, &apiArclengthRange, &apiPeriod);
}

std::vector<double> OrcaFlexObject::RangeGraphXaxis(const std::wstring& varName, const ArclengthRange& arclengthRange) const
{
    const TArclengthRange apiArclengthRange = arclengthRange;
    return RangeGraphXaxis(varName, &apiArclengthRange, nullptr);
}

std::vector<double> OrcaFlexObject::RangeGraphXaxis(const std::wstring& varName, const Period& period) const
{
    const TPeriod apiPeriod = period;
    return RangeGraphXaxis(varName, nullptr, &apiPeriod);
}

std::vector<double> OrcaFlexObject::RangeGraphXaxis(const std::wstring& varName) const
{
    return RangeGraphXaxis(varName, nullptr, nullptr);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const TPeriod* period, const TObjectExtra2* objectExtra, const TArclengthRange* arclengthRange) const
{
    int status;
    int varID = getVarID(varName);
    TPeriod apiPeriod;
    if (period == nullptr)
    {
        apiPeriod = getDefaultPeriod();
        period = &apiPeriod;
    }
    int pointCount = C_GetRangeGraphNumOfPoints3(handle, period, arclengthRange, varID, &status);
    checkStatus(status);
    RangeGraphValues result(pointCount);
    C_GetRangeGraph4(handle, objectExtra, period, arclengthRange, varID, &result.xValues[0], &result.min[0], &result.max[0],
        &result.mean[0], &result.stdDev[0], &result.upper[0], &result.lower[0], &status);
    checkStatus(status);
    return result;
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const Period& period, const ObjectExtra& objectExtra, ArclengthRange& arclengthRange) const
{
    TPeriod apiPeriod = period;
    TObjectExtra2 apiObjectExtra = objectExtra;
    TArclengthRange apiArclengthRange = arclengthRange;
    return RangeGraph(varName, &apiPeriod, &apiObjectExtra, &apiArclengthRange);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const Period& period, const ObjectExtra& objectExtra) const
{
    TPeriod apiPeriod = period;
    TObjectExtra2 apiObjectExtra = objectExtra;
    return RangeGraph(varName, &apiPeriod, &apiObjectExtra, nullptr);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const Period& period, const ArclengthRange& arclengthRange) const
{
    TPeriod apiPeriod = period;
    TArclengthRange apiArclengthRange = arclengthRange;
    return RangeGraph(varName, &apiPeriod, nullptr, &apiArclengthRange);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const ObjectExtra& objectExtra, const ArclengthRange& arclengthRange) const
{
    TObjectExtra2 apiObjectExtra = objectExtra;
    TArclengthRange apiArclengthRange = arclengthRange;
    return RangeGraph(varName, nullptr, &apiObjectExtra, &apiArclengthRange);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const Period& period) const
{
    TPeriod apiPeriod = period;
    return RangeGraph(varName, &apiPeriod, nullptr, nullptr);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const ObjectExtra& objectExtra) const
{
    TObjectExtra2 apiObjectExtra = objectExtra;
    return RangeGraph(varName, nullptr, &apiObjectExtra, nullptr);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName, const ArclengthRange& arclengthRange) const
{
    TArclengthRange apiArclengthRange = arclengthRange;
    return RangeGraph(varName, nullptr, nullptr, &apiArclengthRange);
}

RangeGraphValues OrcaFlexObject::RangeGraph(const std::wstring& varName) const
{
    return RangeGraph(varName, nullptr, nullptr, nullptr);
}

// OrcaFlexModel

void OrcaFlexModel::init(TOrcFxAPIHandle modelHandle, bool ownsModelHandle)
{
    progressHandlerCallback = nullptr;
    staticsProgressHandler = nullptr;
    dynamicsProgressHandler = nullptr;
    postCalculationActionHandler = nullptr;
    handle = modelHandle;
    ownsHandle = ownsModelHandle;
}

void OrcaFlexModel::init(const std::wstring& fileName, int threadCount)
{
    int status;

    TCreateModelParams params = { sizeof(params) };
    params.ThreadCount = threadCount;
    TOrcFxAPIHandle modelHandle;
    C_CreateModel2(&modelHandle, threadCount>0 ? &params : nullptr, &status);
    checkStatus(status);

    init(modelHandle, true);

    if (!fileName.empty())
    {
        int ft;
        C_GetBinaryFileType(fileName.c_str(), &ft, &status);
        if (status != stOK || ft == ftDataFile) {
            C_LoadData(handle, fileName.c_str(), &status);
        } else {
            C_LoadSimulation(handle, fileName.c_str(), &status);
        }
        checkStatus(status);
    }
}

OrcaFlexModel::OrcaFlexModel(const std::wstring& fileName, int threadCount) : HandleObject(nullptr)
{
    init(fileName, threadCount);
};

OrcaFlexModel::OrcaFlexModel(const std::wstring& fileName) : HandleObject(nullptr)
{
    init(fileName, -1);
};

OrcaFlexModel::OrcaFlexModel(int threadCount) : HandleObject(nullptr)
{
    init(L"", threadCount);
};

OrcaFlexModel::OrcaFlexModel(TOrcFxAPIHandle modelHandle) : HandleObject(nullptr)
{
    init(modelHandle, false);
};

OrcaFlexModel::OrcaFlexModel() : HandleObject(nullptr)
{
    init(L"", -1);
};

OrcaFlexModel::~OrcaFlexModel()
{
    if (ownsHandle)
    {
        int status;
        C_DestroyModel(handle, &status);
        checkStatus(status);
    }
};

static const wchar_t* ProgressHandlerBackrefName = L"__ProgressHandlerBackref";

void __stdcall ProgressHandlerProc(TOrcFxAPIHandle modelHandle, int progress, BOOL* cancel)
{
    int status;
    INT_PTR backref = C_GetNamedValue(modelHandle, ProgressHandlerBackrefName, &status);
    checkStatus(status);
    OrcaFlexModel* model = reinterpret_cast<OrcaFlexModel*>(backref);
    *cancel = model->getProgressHandler()(*model, progress);
}

ProgressHandlerCallback OrcaFlexModel::getProgressHandler()
{
    return progressHandlerCallback;
}

void OrcaFlexModel::setProgressHandler(ProgressHandlerCallback value)
{
    int status;
    progressHandlerCallback = value;
    if (progressHandlerCallback != nullptr)
    {
        C_SetNamedValue(handle, ProgressHandlerBackrefName, reinterpret_cast<INT_PTR>(this), &status);
        checkStatus(status);
        C_SetProgressHandler(handle, ProgressHandlerProc, &status);
        checkStatus(status);
    }
    else
    {
        C_SetProgressHandler(handle, nullptr, &status);
        checkStatus(status);
        C_SetNamedValue(handle, ProgressHandlerBackrefName, 0, &status);
        checkStatus(status);
    }
}

OrcaFlexObject OrcaFlexModel::CreateObject(int type)
{
    int status;
    TOrcFxAPIHandle objectHandle;
    C_CreateObject(handle, type, &objectHandle, &status);
    checkStatus(status);
    return OrcaFlexObject(handle, objectHandle, type);
}

OrcaFlexObject OrcaFlexModel::CreateObject(int type, const std::wstring& name)
{
    OrcaFlexObject result = CreateObject(type);
    result.setName(name);
    return result;
}

void OrcaFlexModel::DestroyObject(OrcaFlexObject object)
{
    int status;
    C_DestroyObject(object.getHandle(), &status);
    checkStatus(status);
}

void OrcaFlexModel::DeleteUnusedTypes()
{
    int status;
    C_ModifyModel(handle, modifyModelActionDeleteUnusedTypes, &status);
    checkStatus(status);
}

void OrcaFlexModel::DeleteUnusedVariableDataSources()
{
    int status;
    C_ModifyModel(handle, modifyModelActionDeleteUnusedVariableDataSources, &status);
    checkStatus(status);
}

static const wchar_t* EnumerateObjectsBackrefName = L"__EnumerateObjectsBackref";

void __stdcall EnumerateObjectsProc(TOrcFxAPIHandle modelHandle, const TObjectInfo* objectInfo)
{
    std::vector<OrcaFlexObject>* objects = Backref<std::vector<OrcaFlexObject>>::getRef(modelHandle, EnumerateObjectsBackrefName);
    objects->push_back(OrcaFlexObject(modelHandle, objectInfo->ObjectHandle, objectInfo->ObjectType));
}

std::vector<OrcaFlexObject> OrcaFlexModel::getObjects() const
{
    int status;
    int objectCount;
    std::vector<OrcaFlexObject> result;
    Backref<std::vector<OrcaFlexObject>> backref(&result, handle, EnumerateObjectsBackrefName);
    C_EnumerateObjects(handle, EnumerateObjectsProc, &objectCount, &status);
    checkStatus(status);
    return result;
}

int OrcaFlexModel::getState() const
{
    return getState(handle);
}

int OrcaFlexModel::getState(TOrcFxAPIHandle handle)
{
    int status;
    int result;
    C_GetModelState(handle, &result, &status);
    checkStatus(status);
    return result;
}

OrcaFlexObject OrcaFlexModel::objectCalled(const std::wstring& name) const
{
    int status;
    TObjectInfo objectInfo;
    C_ObjectCalled(handle, name.c_str(), &objectInfo, &status);
    checkStatus(status);
    return OrcaFlexObject(handle, objectInfo.ObjectHandle, objectInfo.ObjectType);
}

OrcaFlexObject OrcaFlexModel::getGeneral() const
{
    int status;
    TOrcFxAPIHandle objectHandle;
    C_GetModelProperty(handle, propGeneralHandle, &objectHandle, &status);
    checkStatus(status);
    return OrcaFlexObject(handle, objectHandle, otGeneral);
}

OrcaFlexObject OrcaFlexModel::getEnvironment() const
{
    int status;
    TOrcFxAPIHandle objectHandle;
    C_GetModelProperty(handle, propEnvironmentHandle, &objectHandle, &status);
    checkStatus(status);
    return OrcaFlexObject(handle, objectHandle, otEnvironment);
}

int OrcaFlexModel::getThreadCount() const
{
    int status;
    int result = C_GetModelThreadCount(handle, &status);
    checkStatus(status);
    return result;
}

void OrcaFlexModel::setThreadCount(int value)
{
    int status;
    C_SetModelThreadCount(handle, value, &status);
    checkStatus(status);
}

void OrcaFlexModel::GetRecommendedTimeSteps(double& innerTimeStep, double& outerTimeStep) const
{
    int status;
    TTimeSteps timeSteps = { sizeof(timeSteps) };
    C_GetRecommendedTimeSteps(handle, &timeSteps, &status);
    checkStatus(status);
    innerTimeStep = timeSteps.InnerTimeStep;
    outerTimeStep = timeSteps.OuterTimeStep;
}

TSimulationTimeStatus OrcaFlexModel::getSimulationTimeStatus() const
{
    int status;
    TSimulationTimeStatus result;
    C_GetSimulationTimeStatus(handle, &result, &status);
    checkStatus(status);
    return result;
}

double OrcaFlexModel::getSimulationStartTime() const
{
    return getSimulationTimeStatus().StartTime;
}

double OrcaFlexModel::getSimulationStopTime() const
{
    return getSimulationTimeStatus().StopTime;
}

double OrcaFlexModel::getSimulationCurrentTime() const
{
    return getSimulationTimeStatus().CurrentTime;
}

double OrcaFlexModel::getSimulationTimeToGo() const
{
    int status;
    double result = C_GetSimulationTimeToGo(handle, &status);
    checkStatus(status);
    return result;
}

bool OrcaFlexModel::getSimulationComplete() const
{
    int status;
    BOOL result;
    C_GetSimulationComplete(handle, &result, &status);
    checkStatus(status);
    return result != 0;
}

double OrcaFlexModel::getSimulationDrawTime() const
{
    int status;
    double result = C_GetSimulationDrawTime(handle, &status);
    checkStatus(status);
    return result;
}

void OrcaFlexModel::setSimulationDrawTime(double value)
{
    int status;
    C_SetSimulationDrawTime(handle, value, &status);
    checkStatus(status);
}

ViewParameters OrcaFlexModel::getDefaultViewParameters() const
{
    int status;
    TViewParameters result = { sizeof(result) };
    C_GetDefaultViewParameters(handle, &result, &status);
    checkStatus(status);
    return ViewParameters(result);
}

void OrcaFlexModel::SaveModelView(const std::wstring& fileName, const ViewParameters& viewParameters) const
{
    int status;
    TViewParameters apiViewParameters = viewParameters;
    C_SaveModel3DViewBitmapToFile(handle, &apiViewParameters, fileName.c_str(), &status);
    checkStatus(status);
}

HBITMAP OrcaFlexModel::GetModelView(const std::wstring& fileName, const ViewParameters& viewParameters) const
{
    int status;
    HBITMAP result;
    TViewParameters apiViewParameters = viewParameters;
    C_CreateModel3DViewBitmap(handle, &apiViewParameters, &result, &status);
    checkStatus(status);
    return result;
}

void OrcaFlexModel::Reset()
{
    int status;
    C_ResetModel(handle, &status);
    checkStatus(status);
}

void OrcaFlexModel::Clear()
{
    int status;
    C_ClearModel(handle, &status);
    checkStatus(status);
}

void OrcaFlexModel::LoadData(const std::wstring& fileName)
{
    int status;
    C_LoadData(handle, fileName.c_str(), &status);
    checkStatus(status);
}

void OrcaFlexModel::SaveData(const std::wstring& fileName) const
{
    int status;
    C_SaveData(handle, fileName.c_str(), &status);
    checkStatus(status);
}

void OrcaFlexModel::LoadSimulation(const std::wstring& fileName)
{
    int status;
    C_LoadSimulation(handle, fileName.c_str(), &status);
    checkStatus(status);
}

void OrcaFlexModel::SaveSimulation(const std::wstring& fileName) const
{
    int status;
    C_SaveSimulation(handle, fileName.c_str(), &status);
    checkStatus(status);
}

std::vector<std::wstring> OrcaFlexModel::getWarnings() const
{
    int status;
    int count = C_GetNumOfWarnings(handle, &status);
    checkStatus(status);

    std::vector<std::wstring> result;
    result.reserve(count);
    for (int index = 0; index < count; index++)
    {
        int stage;
        int length = C_GetWarningText(handle, index, &stage, nullptr, &status);
        checkStatus(status);

        std::vector<wchar_t> text(length);
        C_GetWarningText(handle, index, &stage, &text[0], &status);
        checkStatus(status);

        result.push_back(std::wstring(&text[0], length-1));
    }

    return result;
}

static const wchar_t* StaticsProgressHandlerBackrefName = L"__StaticsProgressHandlerBackref";

void __stdcall StaticsProgressHandlerProc(TOrcFxAPIHandle modelHandle, const wchar_t* progress, BOOL* cancel)
{
    OrcaFlexModel* model = Backref<OrcaFlexModel>::getRef(modelHandle, StaticsProgressHandlerBackrefName);
    *cancel = model->getStaticsProgressHandler()(*model, progress);
}

void OrcaFlexModel::CalculateStatics()
{
    int status;
    if (staticsProgressHandler != nullptr)
    {
        Backref<OrcaFlexModel> backref(this, handle, StaticsProgressHandlerBackrefName);
        C_CalculateStatics(handle, StaticsProgressHandlerProc, &status);
    }
    else
    {
        C_CalculateStatics(handle, nullptr, &status);
    }
    checkStatus(status);
}

void OrcaFlexModel::UseCalculatedPositions(bool setLinesToUserSpecifiedStartingShape)
{
    int status;
    TUseCalculatedPositionsForStaticsParameters params = { sizeof(params) };
    C_GetDefaultUseCalculatedPositionsForStaticsParameters(&params, &status);
    checkStatus(status);

    params.SetLinesToUserSpecifiedStartingShape = setLinesToUserSpecifiedStartingShape;
    C_UseCalculatedPositionsForStatics(handle, &params, &status);
    checkStatus(status);
}

void OrcaFlexModel::UseCalculatedPositions()
{
    UseCalculatedPositions(false);
}

static const wchar_t* DynamicsProgressHandlerBackrefName = L"__DynamicsProgressHandlerBackref";

void __stdcall DynamicsProgressHandlerProc(TOrcFxAPIHandle modelHandle, double simulationTime, double simulationStart, double simulationStop, BOOL* cancel)
{
    OrcaFlexModel* model = Backref<OrcaFlexModel>::getRef(modelHandle, DynamicsProgressHandlerBackrefName);
    *cancel = model->getDynamicsProgressHandler()(*model, simulationTime, simulationStart, simulationStop);
}

void OrcaFlexModel::RunSimulation(const TRunSimulationParameters* params)
{
    if (getState() <= msInStaticState)
    {
        OrcaFlexObject general = getGeneral();
        int status;
        int result;
        C_GetDataType(general.handle, L"AnalysisRunStatics", &result, &status);
        if (status != stOK || general.GetDataString(L"AnalysisRunStatics") == L"Yes")
        {
            CalculateStatics();
        }
    }

    int status;
    if (dynamicsProgressHandler != nullptr)
    {
        Backref<OrcaFlexModel> backref(this, handle, DynamicsProgressHandlerBackrefName);
        C_RunSimulation2(handle, DynamicsProgressHandlerProc, params, &status);
    }
    else
    {
        C_RunSimulation2(handle, nullptr, params, &status);
    }
    checkStatus(status);
}

void OrcaFlexModel::RunSimulation(int autoSaveIntervalMinutes, const std::wstring& autoSaveFileName)
{
    TRunSimulationParameters params = { sizeof(params) };
    params.EnableAutoSave = true;
    params.AutoSaveIntervalMinutes = autoSaveIntervalMinutes;
    params.AutoSaveFileName = autoSaveFileName.c_str();
    RunSimulation(&params);
}

void OrcaFlexModel::RunSimulation()
{
    RunSimulation(nullptr);
}

void OrcaFlexModel::PauseSimulation()
{
    int status;
    C_PauseSimulation(handle, &status);
    checkStatus(status);
}

void OrcaFlexModel::ExtendSimulation(double time)
{
    int status;
    C_ExtendSimulation(handle, time, &status);
    checkStatus(status);
}

static const wchar_t* PostCalculationActionHandlerBackrefName = L"__PostCalculationActionHandlerBackref";

void __stdcall PostCalculationActionHandlerProc(TOrcFxAPIHandle modelHandle, const wchar_t* progress, BOOL* cancel)
{
    OrcaFlexModel* model = Backref<OrcaFlexModel>::getRef(modelHandle, PostCalculationActionHandlerBackrefName);
    *cancel = model->getPostCalculationActionHandler()(*model, progress);
}

void OrcaFlexModel::ExecutePostCalculationActions(const std::wstring& fileName, int actionType, bool treatExecutionErrorsAsWarnings)
{
    int status;
    if (postCalculationActionHandler != nullptr)
    {
        Backref<OrcaFlexModel> backref(this, handle, PostCalculationActionHandlerBackrefName);
        C_ExecutePostCalculationActions(handle, fileName.c_str(), PostCalculationActionHandlerProc, actionType, treatExecutionErrorsAsWarnings, &status);
    }
    else
    {
        C_ExecutePostCalculationActions(handle, fileName.c_str(), nullptr, actionType, treatExecutionErrorsAsWarnings, &status);
    }
    checkStatus(status);
}

Period OrcaFlexModel::getDefaultPeriod() const
{
    return Period::Default(getState());
}

std::vector<double> OrcaFlexModel::SampleTimes(const Period& period) const
{
    int status;
    const TPeriod apiPeriod = period;
    int sampleCount = C_GetNumOfSamples(handle, &apiPeriod, &status);
    checkStatus(status);

    std::vector<double> result(sampleCount);
    C_GetSampleTimes(handle, &apiPeriod, &result[0], &status);
    checkStatus(status);

    return result;
}

std::vector<double> OrcaFlexModel::SampleTimes() const
{
    return SampleTimes(getDefaultPeriod());
}

}