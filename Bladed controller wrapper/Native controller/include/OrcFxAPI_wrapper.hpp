#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

#include "OrcFxAPI.h"

namespace Orcina {

void checkStatus(int status);
std::wstring DLLVersion();
int BinaryFileType(const std::wstring& fileName);
std::wstring FileCreatorVersion(const std::wstring fileName);

class Uncopyable
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable &);
    Uncopyable& operator=(const Uncopyable&);
};

class OrcFxAPI_error : public std::runtime_error
{
private:
    int status;
public:
    OrcFxAPI_error(int status, const std::string& what_arg)
        : runtime_error(what_arg), status(status) {};
    int getStatus() const { return status; };
};

class Period
{
public:
    Period(double fromTime, double toTime)
        : periodNum(pnSpecifiedPeriod), fromTime(fromTime), toTime(toTime) {};
    Period(int periodNum)
        : periodNum(periodNum), fromTime(0.0), toTime(0.0) {};
    static Period Default(int modelState);
    operator const TPeriod () const;
public:
    int periodNum;
    double fromTime;
    double toTime;
};

class ObjectExtra
{
public:
    ObjectExtra()
        : environmentPos(), linePoint(), nodeNum(), arclength(), radialPos(), theta(), wingName(),
        clearanceLineName(), winchConnectionPoint(), rigidBodyPos(), externalResultText(),
        disturbanceVesselName(), supportIndex(), supportedLineName(), bladeIndex(), elementIndex(),
        seaSurfaceScalingFactor() {};
    static ObjectExtra Environment(double X, double Y, double Z);
    static ObjectExtra Environment(const TVector& pos);
    static ObjectExtra Buoy(double X, double Y, double Z);
    static ObjectExtra Buoy(const TVector& pos);
    static ObjectExtra Wing(const std::wstring& name);
    static ObjectExtra Vessel(double X, double Y, double Z);
    static ObjectExtra Vessel(const TVector& pos);
    static ObjectExtra AirGap(double X, double Y, double Z, double seaSurfaceScalingFactor);
    static ObjectExtra AirGap(const TVector& pos, double seaSurfaceScalingFactor);
    static ObjectExtra Constraint(double X, double Y, double Z);
    static ObjectExtra Constraint(const TVector& pos);
    static ObjectExtra Support(int supportIndex);
    static ObjectExtra Support(int supportIndex, const std::wstring& supportedLineName);
    static ObjectExtra Winch(int connectionPoint);
    static ObjectExtra LineNodeNum(int nodeNum);
    static ObjectExtra LineArclength(double arclength);
    static ObjectExtra LineEndA();
    static ObjectExtra LineEndB();
    static ObjectExtra LineTouchdown();
    static ObjectExtra Turbine(int bladeIndex, double arclength);
    static ObjectExtra Turbine(int bladeIndex);
    static ObjectExtra TurbineEndA(int bladeIndex);
    static ObjectExtra TurbineEndB(int bladeIndex);
    static ObjectExtra MorisonElement(int elementIndex, double arclength);
    static ObjectExtra MorisonElement(int elementIndex);
    operator const TObjectExtra2 () const;
public:
    TVector environmentPos;
    int linePoint;
    int nodeNum;
    double arclength;
    int radialPos;
    double theta;
    std::wstring wingName;
    std::wstring clearanceLineName;
    int winchConnectionPoint;
    TVector rigidBodyPos;
    std::wstring externalResultText;
    std::wstring disturbanceVesselName;
    int supportIndex;
    std::wstring supportedLineName;
    int bladeIndex;
    int elementIndex;
    double seaSurfaceScalingFactor;
};

class VarDetails
{
public:
    VarDetails(const std::wstring& varName, const std::wstring& varUnits, const std::wstring& fullName)
        : varName(varName), varUnits(varUnits), fullName(fullName) {};
public:
    const std::wstring varName;
    const std::wstring varUnits;
    const std::wstring fullName;
};

class ArclengthRange
{
public:
    ArclengthRange()
        : mode(armEntireLine), fromArclength(), toArclength(), fromSection(), toSection() {};
    ArclengthRange(double fromArclength, double toArclength)
        : mode(armSpecifiedArclengths), fromArclength(fromArclength), toArclength(toArclength), fromSection(), toSection() {};
    ArclengthRange(int fromSection, int toSection)
        : mode(armSpecifiedSections), fromArclength(), toArclength(), fromSection(fromSection), toSection(toSection) {};
    operator const TArclengthRange () const;
public:
    int mode;
    double fromArclength;
    double toArclength;
    int fromSection;
    int toSection;
};

class RangeGraphValues
{
public:
    RangeGraphValues(int count)
    {
        xValues.resize(count);
        min.resize(count);
        max.resize(count);
        mean.resize(count);
        stdDev.resize(count);
        upper.resize(count);
        lower.resize(count);
    };
public:
    std::vector<double> xValues;
    std::vector<double> min;
    std::vector<double> max;
    std::vector<double> mean;
    std::vector<double> stdDev;
    std::vector<double> upper;
    std::vector<double> lower;
};

class ViewParameters
{
public:
    ViewParameters()
        : viewSize(), viewAzimuth(), viewElevation(), viewCentre(), height(), width(), backgroundColour(),
        drawViewAxes(), drawScaleBar(), drawGlobalAxes(), drawEnvironmentAxes(), drawLocalAxes(),
        drawOutOfBalanceForces(), drawNodeAxes(), graphicsMode(), fileFormat(), viewGamma(),
        relativeToObjectHandle(), disturbanceVesselHandle(), disturbancePosition(), shadedFillMode(),
        drawNameLabels(), drawConnections(), labelScale(), drawOrigins(), monochromeOutput(),
        addDetailsToOutput(), jpegCompressionQuality() {};
    ViewParameters(const TViewParameters& params)
        : viewSize(params.ViewSize), viewAzimuth(params.ViewAzimuth), viewElevation(params.ViewElevation),
        viewCentre(params.ViewCentre), height(params.Height), width(params.Width),
        backgroundColour(params.BackgroundColour),
        drawViewAxes(params.DrawViewAxes), drawScaleBar(params.DrawScaleBar), drawGlobalAxes(params.DrawGlobalAxes),
        drawEnvironmentAxes(params.DrawEnvironmentAxes), drawLocalAxes(params.DrawLocalAxes),
        drawOutOfBalanceForces(params.DrawOutOfBalanceForces), drawNodeAxes(params.DrawNodeAxes),
        graphicsMode(params.GraphicsMode), fileFormat(params.FileFormat), viewGamma(params.ViewGamma),
        relativeToObjectHandle(params.RelativeToObjectHandle), disturbanceVesselHandle(params.DisturbanceVesselHandle),
        disturbancePosition(params.DisturbancePosition), shadedFillMode(params.ShadedFillMode),
        drawNameLabels(params.DrawNameLabels), drawConnections(params.DrawConnections), labelScale(params.LabelScale),
        drawOrigins(params.DrawOrigins), monochromeOutput(params.MonochromeOutput),
        addDetailsToOutput(params.AddDetailsToOutput), jpegCompressionQuality(params.JpegCompressionQuality) {};
    operator const TViewParameters () const;
public:
    double viewSize;
    double viewAzimuth;
    double viewElevation;
    TVector viewCentre;
    int height;
    int width;
    COLORREF backgroundColour;
    BOOL drawViewAxes;
    BOOL drawScaleBar;
    BOOL drawGlobalAxes;
    BOOL drawEnvironmentAxes;
    BOOL drawLocalAxes;
    BOOL drawOutOfBalanceForces;
    BOOL drawNodeAxes;
    int graphicsMode;
    int fileFormat;
    double viewGamma;
    TOrcFxAPIHandle relativeToObjectHandle;
    TOrcFxAPIHandle disturbanceVesselHandle;
    TVector2 disturbancePosition;
    int shadedFillMode;
    BOOL drawNameLabels;
    BOOL drawConnections;
    int labelScale;
    BOOL drawOrigins;
    BOOL monochromeOutput;
    BOOL addDetailsToOutput;
    int jpegCompressionQuality;
};

class HandleObject
{
public:
    TOrcFxAPIHandle getHandle() const { return handle; };
protected:
    HandleObject(TOrcFxAPIHandle handle) : handle(handle) {};
protected:
    TOrcFxAPIHandle handle;
};

class DataObject : public HandleObject
{
public:
    std::wstring getName() const { return GetDataString(L"Name"); };
    void setName(const std::wstring& value) { SetDataString(L"Name", value); };
    int GetDataType(const std::wstring& dataName) const;
    int GetVariableDataType(const std::wstring& dataName, int index) const;
    bool DataNameValid(const std::wstring& dataName) const;
    bool DataRequiresIndex(const std::wstring& dataName) const;
    void BeginDataChange();
    void EndDataChange();
    int GetDataRowCount(const std::wstring& dataName) const;
    void SetDataRowCount(const std::wstring& dataName, int value);
    void InsertDataRow(const std::wstring& indexedDataName, int index);
    void DeleteDataRow(const std::wstring& indexedDataName, int index);
    double GetDataDouble(const std::wstring& dataName, int index) const;
    double GetDataDouble(const std::wstring& dataName) const;
    std::vector<double> GetDataDoubleArray(const std::wstring& dataName) const;
    void SetDataDouble(const std::wstring& dataName, int index, double value);
    void SetDataDouble(const std::wstring& dataName, double value);
    void SetDataDoubleArray(const std::wstring& dataName, const std::vector<double>& values);
    int GetDataInteger(const std::wstring& dataName, int index) const;
    int GetDataInteger(const std::wstring& dataName) const;
    std::vector<int> GetDataIntegerArray(const std::wstring& dataName) const;
    void SetDataInteger(const std::wstring& dataName, int index, int value);
    void SetDataInteger(const std::wstring& dataName, int value);
    void SetDataIntegerArray(const std::wstring& dataName, const std::vector<int>& values);
    std::wstring GetDataString(const std::wstring& dataName, int index) const;
    std::wstring GetDataString(const std::wstring& dataName) const;
    std::vector<std::wstring> GetDataStringArray(const std::wstring& dataName) const;
    void SetDataString(const std::wstring& dataName, int index, const std::wstring& value);
    void SetDataString(const std::wstring& dataName, const std::wstring& value);
    void SetDataStringArray(const std::wstring& dataName, const std::vector<std::wstring>& values);
    double UnitsConversionFactor(const std::wstring& units);
protected:
    DataObject(TOrcFxAPIHandle handle)
        : HandleObject(handle) {};
};

class OrcaFlexModel;

class OrcaFlexObject : public DataObject
{
    friend class OrcaFlexModel;
    friend void __stdcall EnumerateObjectsProc(TOrcFxAPIHandle, const TObjectInfo*);
public:
    OrcaFlexObject(TOrcFxAPIHandle modelHandle, TOrcFxAPIHandle handle)
        : DataObject(handle), modelHandle(modelHandle), type(getType(handle)) {};
    OrcaFlexObject(TOrcFxAPIHandle handle)
        : DataObject(handle), modelHandle(getModelHandle(handle)), type(getType(handle)) {};
    OrcaFlexObject CreateClone(const std::wstring& name, OrcaFlexModel& model) const;
    OrcaFlexObject CreateClone(const std::wstring& name) const;
    OrcaFlexObject CreateClone(OrcaFlexModel& model) const;
    OrcaFlexObject CreateClone() const;
    void InvokeWizard();
    int getType() const { return type; };
    bool tryGetTag(const std::wstring name, std::wstring &value) const;
    std::wstring getTag(const std::wstring name) const;
    std::vector<std::wstring> Vars(int resultType, const ObjectExtra& objectExtra) const;
    std::vector<std::wstring> Vars(const ObjectExtra& objectExtra) const;
    std::vector<std::wstring> Vars(int resultType) const;
    std::vector<std::wstring> Vars() const;
    std::vector<Orcina::VarDetails> VarDetails(int resultType, const ObjectExtra& objectExtra) const;
    std::vector<Orcina::VarDetails> VarDetails(const ObjectExtra& objectExtra) const;
    std::vector<Orcina::VarDetails> VarDetails(int resultType) const;
    std::vector<Orcina::VarDetails> VarDetails() const;
    std::vector<double> TimeHistory(const std::wstring& varName, const Period& period, const ObjectExtra& objectExtra) const;
    std::vector<double> TimeHistory(const std::wstring& varName, const ObjectExtra& objectExtra) const;
    std::vector<double> TimeHistory(const std::wstring& varName, const Period& period) const;
    std::vector<double> TimeHistory(const std::wstring& varName) const;
    double StaticResult(const std::wstring& varName, const ObjectExtra& objectExtra) const;
    double StaticResult(const std::wstring& varName) const;
    std::vector<double> RangeGraphXaxis(const std::wstring& varName, const ArclengthRange& arclengthRange, const Period& period) const;
    std::vector<double> RangeGraphXaxis(const std::wstring& varName, const ArclengthRange& arclengthRange) const;
    std::vector<double> RangeGraphXaxis(const std::wstring& varName, const Period& period) const;
    std::vector<double> RangeGraphXaxis(const std::wstring& varName) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const Period& period, const ObjectExtra& objectExtra, ArclengthRange& arclengthRange) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const Period& period, const ObjectExtra& objectExtra) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const Period& period, const ArclengthRange& arclengthRange) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const ObjectExtra& objectExtra, const ArclengthRange& arclengthRange) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const Period& period) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const ObjectExtra& objectExtra) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const ArclengthRange& arclengthRange) const;
    RangeGraphValues RangeGraph(const std::wstring& varName) const;
private:
    OrcaFlexObject(TOrcFxAPIHandle modelHandle, TOrcFxAPIHandle handle, int type)
        : DataObject(handle), modelHandle(modelHandle), type(type) {};
    OrcaFlexObject CreateClone(const std::wstring& name, TOrcFxAPIHandle modelHandle) const;
    static TOrcFxAPIHandle getModelHandle(TOrcFxAPIHandle handle);
    static int getType(TOrcFxAPIHandle handle);
    int getVarID(const std::wstring& varName) const;
    int getModelState() const;
    Period getDefaultPeriod() const;
    std::vector<std::wstring> Vars(int resultType, const TObjectExtra2* objectExtra) const;
    std::vector<Orcina::VarDetails> VarDetails(int resultType, const TObjectExtra2* objectExtra) const;
    int getNumOfSamples(const TPeriod* period) const;
    std::vector<double> TimeHistory(const std::wstring& varName, const TObjectExtra2* objectExtra, const TPeriod* period) const;
    double StaticResult(const std::wstring& varName, const TObjectExtra2* objectExtra) const;
    std::vector<double> RangeGraphXaxis(const std::wstring& varName, const TArclengthRange* arclengthRange, const TPeriod* period) const;
    RangeGraphValues RangeGraph(const std::wstring& varName, const TPeriod* period, const TObjectExtra2* objectExtra, const TArclengthRange* arclengthRange) const;
private:
    TOrcFxAPIHandle modelHandle;
    int type;
};

typedef std::function<bool(OrcaFlexModel& model, int progress)> ProgressHandlerCallback;
typedef std::function<bool(OrcaFlexModel& model, const std::wstring& progress)> StaticsProgressHandlerCallback;
typedef std::function<bool(OrcaFlexModel& model, double simulationTime, double simulationStart, double simulationStop)> DynamicsProgressHandlerCallback;
typedef std::function<bool(OrcaFlexModel& model, const std::wstring& progress)> PostCalculationActionHandlerCallback;

class OrcaFlexModel : public HandleObject, private Uncopyable
{
public:
    OrcaFlexModel(const std::wstring& fileName, int threadCount);
    OrcaFlexModel(const std::wstring& fileName);
    OrcaFlexModel(int threadCount);
    OrcaFlexModel(TOrcFxAPIHandle modelHandle);
    OrcaFlexModel();
    ~OrcaFlexModel();
    ProgressHandlerCallback getProgressHandler();
    void setProgressHandler(ProgressHandlerCallback value);
    StaticsProgressHandlerCallback getStaticsProgressHandler() { return staticsProgressHandler; };
    void setStaticsProgressHandler(StaticsProgressHandlerCallback value) { staticsProgressHandler = value; };
    DynamicsProgressHandlerCallback getDynamicsProgressHandler() { return dynamicsProgressHandler; };
    void setDynamicsProgressHandler(DynamicsProgressHandlerCallback value) { dynamicsProgressHandler = value; };
    PostCalculationActionHandlerCallback getPostCalculationActionHandler() { return postCalculationActionHandler; };
    void setPostCalculationActionHandler(PostCalculationActionHandlerCallback value) { postCalculationActionHandler = value; };
    OrcaFlexObject CreateObject(int type);
    OrcaFlexObject CreateObject(int type, const std::wstring& name);
    void DestroyObject(OrcaFlexObject object);
    void DeleteUnusedTypes();
    void DeleteUnusedVariableDataSources();
    std::vector<OrcaFlexObject> getObjects() const;
    int getState() const;
    static int getState(TOrcFxAPIHandle handle);
    OrcaFlexObject objectCalled(const std::wstring& name) const;
    OrcaFlexObject getGeneral() const;
    OrcaFlexObject getEnvironment() const;
    int getThreadCount() const;
    void setThreadCount(int value);
    void GetRecommendedTimeSteps(double& innerTimeStep, double& outerTimeStep) const;
    double getSimulationStartTime() const;
    double getSimulationStopTime() const;
    double getSimulationCurrentTime() const;
    double getSimulationTimeToGo() const;
    bool getSimulationComplete() const;
    double getSimulationDrawTime() const;
    void setSimulationDrawTime(double value);
    ViewParameters getDefaultViewParameters() const;
    void SaveModelView(const std::wstring& fileName, const ViewParameters& viewParameters) const;
    HBITMAP GetModelView(const std::wstring& fileName, const ViewParameters& viewParameters) const;
    void Reset();
    void Clear();
    void LoadData(const std::wstring& fileName);
    void SaveData(const std::wstring& fileName) const;
    void LoadSimulation(const std::wstring& fileName);
    void SaveSimulation(const std::wstring& fileName) const;
    std::vector<std::wstring> getWarnings() const;
    void CalculateStatics();
    void UseCalculatedPositions(bool setLinesToUserSpecifiedStartingShape);
    void UseCalculatedPositions();
    void RunSimulation(int autoSaveIntervalMinutes, const std::wstring& autoSaveFileName);
    void RunSimulation();
    void PauseSimulation();
    void ExtendSimulation(double time);
    void ExecutePostCalculationActions(const std::wstring& fileName, int actionType, bool treatExecutionErrorsAsWarnings=false);
    std::vector<double> SampleTimes(const Period& period) const;
    std::vector<double> SampleTimes() const;
private:
    bool ownsHandle;
    void init(TOrcFxAPIHandle modelHandle, bool ownsModelHandle);
    void init(const std::wstring& fileName, int threadCount);
    Period getDefaultPeriod() const;
    TSimulationTimeStatus getSimulationTimeStatus() const;
    void RunSimulation(const TRunSimulationParameters* params);
private:
    ProgressHandlerCallback progressHandlerCallback;
    StaticsProgressHandlerCallback staticsProgressHandler;
    DynamicsProgressHandlerCallback dynamicsProgressHandler;
    PostCalculationActionHandlerCallback postCalculationActionHandler;
};

}