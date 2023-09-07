#ifndef _orcfxapi_
#define _orcfxapi_

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <stdint.h>
#include <windows.h>

#pragma pack(push, 1)

#ifdef __cplusplus
namespace Orcina {
extern "C" {
#endif /* __cplusplus */

/* Status constants returned by API functions */
#define stOK 0
#define stDLLsVersionError 1
#define stCreateModelError 2
#define stModelHandleError 3
#define stObjectHandleError 4
#define stInvalidObjectType 5
#define stFileNotFound 6
#define stFileReadError 7
#define stTimeHistoryError 8
#define stNoSuchNodeNum 9
#define stInvalidPropertyNum 10
#define stInvalidPeriod 12
#define stInvalidVarNum 13
#define stRangeGraphError 14
#define stInvalidObjectExtra 15
#define stNotEnoughVars 16
#define stInvalidVars 17
#define stUnrecognisedVarNum 18
#define stInvalidHandle 19
#define stUnexpectedError 20
#define stInvalidIndex 21
#define stNoSuchObject 23
#define stNotAVariantArray 24
#define stLicensingError 25
#define stUnrecognisedVarName 26
#define stStaticsFailed 27
#define stFileWriteError 28
#define stOperationCancelled 29
#define stSolveEquationFailed 30
#define stInvalidDataName 31
#define stInvalidDataType 32
#define stInvalidDataAccess 33
#define stInvalidVersion 34
#define stInvalidStructureSize 35
#define stRequiredModulesNotEnabled 36
#define stPeriodNotYetStarted 37
#define stCouldNotDestroyObject 38
#define stInvalidModelState 39
#define stSimulationError 40
#define stInvalidModule 41
#define stInvalidResultType 42
#define stInvalidViewParameters 43
#define stCannotExtendSimulation 44
#define stUnrecognisedObjectTypeName 45
#define stUnknownModelState 46
#define stFunctionNotAvailable 47
#define stStructureSizeTooSmall 48
#define stInvalidParameter 49
#define stResponseGraphError 50
#define stResultsNotAvailableWhenNotIncludedInStatics 51
#define stInvalidFileType 52
#define stBatchScriptFailed 53
#define stInvalidTimeHistoryValues 54
#define stResultsNotLogged 55
#define stWizardFailed 56
#define stDLLInitFailed 57
#define stInvalidArclengthRange 58
#define stValueNotAvailable 59
#define stInvalidValue 60
#define stModalAnalysisFailed 61
#define stVesselTypeDataImportFailed 62
#define stOperationNotAvailable 63
#define stFatigueAnalysisFailed 64
#define stExtremeStatisticsFailed 65
#define stTagNotFound 66
#define stInvalidFileFormat 67
#define stThreadAffinityError 68
#define stFileReadParentError 69

/* Users can use error numbers from here up */
#define stUserDefinedError 100000

/* Object type constants */
#define otNull 0
#define otGeneral 1
#define otEnvironment 3
#define otVessel 5
#define otLine 6
#define ot6DBuoy 7
#define ot3DBuoy 8
#define otWinch 9
#define otLink 10
#define otShape 11
#define otConstraint 12
#define otTurbine 13
#define otDragChain 14
#define otLineType 15
#define otClumpType 16
#define otWingType 17
#define otVesselType 18
#define otDragChainType 19
#define otFlexJointType 20
#define otStiffenerType 21
#define otFlexJoint 41
#define otAttachedBuoy 43
#define otFrictionCoefficients 47
/* define otSolidFrictionCoefficients for back-compat reasons */
#define otSolidFrictionCoefficients otFrictionCoefficients
#define otRayleighDampingCoefficients 48
#define otWakeModel 49
#define otPyModel 50
#define otLineContact 51
#define otCodeChecks 52
#define otShear7Data 53
#define otVIVAData 54
#define otSupportType 55
#define otMorisonElementType 57
#define otExpansionTable 58
#define otBrowserGroup 61
#define otMultiBodyGroup 62

/* Object type constants (additional for GUI copy / paste actions) */
#define otMultipleObjects 56

/* Object type constants (variable data sources) */
#define otDragCoefficient 1000
#define otAxialStiffness 1001
#define otBendingStiffness 1002
#define otBendingConnectionStiffness 1003
#define otWingOrientation 1004
#define otKinematicViscosity 1005
#define otFluidTemperature 1006
#define otCurrentSpeed 1007
#define otCurrentDirection 1008
#define otExternalFunction 1009
#define otHorizontalVariationFactor 1010
#define otLoadForce 1011
#define otLoadMoment 1012
#define otExpansionFactor 1013
#define otPayoutRate 1014
#define otWinchPayoutRate otPayoutRate /* backwards compatibility */
#define otWinchTension 1015
#define otVerticalVariationFactor 1016
#define otTorsionalStiffness 1017
#define otMinimumBendRadius 1018
#define otLiftCoefficient 1019
#define otLiftCloseToSeabed 1020
#define otDragCloseToSeabed 1021
#define otDragAmplificationFactor 1022
#define otLineTypeDiameter 1023
#define otStressStrainRelationship 1024
#define otCoatingOrLining 1025
#define otContentsFlowVelocity 1026
#define otAddedMassRateOfChangeCloseToSurface 1027
#define otAddedMassCloseToSurface 1028
#define otContactStiffness 1029
#define otSupportsStiffness 1030
#define otConstraintTranslationalStiffness 1031
#define otConstraintRotationalStiffness 1032
#define otConstraintTranslationalDamping 1033
#define otConstraintRotationalDamping 1034
#define otAddedMassCloseToSeabed 1035
#define otSeabedTangentialResistance 1036

/* Variable Data Names */
#define vdnWingAzimuth TEXT("WingAzimuth")
#define vdnWingDeclination TEXT("WingDeclination")
#define vdnWingGamma TEXT("WingGamma")
#define vdnAppliedForceX TEXT("AppliedForceX")
#define vdnAppliedForceY TEXT("AppliedForceY")
#define vdnAppliedForceZ TEXT("AppliedForceZ")
#define vdnAppliedMomentX TEXT("AppliedMomentX")
#define vdnAppliedMomentY TEXT("AppliedMomentY")
#define vdnAppliedMomentZ TEXT("AppliedMomentZ")
#define vdnGlobalAppliedForceX TEXT("GlobalAppliedForceX")
#define vdnGlobalAppliedForceY TEXT("GlobalAppliedForceY")
#define vdnGlobalAppliedForceZ TEXT("GlobalAppliedForceZ")
#define vdnGlobalAppliedMomentX TEXT("GlobalAppliedMomentX")
#define vdnGlobalAppliedMomentY TEXT("GlobalAppliedMomentY")
#define vdnGlobalAppliedMomentZ TEXT("GlobalAppliedMomentZ")
#define vdnLocalAppliedForceX TEXT("LocalAppliedForceX")
#define vdnLocalAppliedForceY TEXT("LocalAppliedForceY")
#define vdnLocalAppliedForceZ TEXT("LocalAppliedForceZ")
#define vdnLocalAppliedMomentX TEXT("LocalAppliedMomentX")
#define vdnLocalAppliedMomentY TEXT("LocalAppliedMomentY")
#define vdnLocalAppliedMomentZ TEXT("LocalAppliedMomentZ")
#define vdnRefCurrentSpeed TEXT("RefCurrentSpeed")
#define vdnRefCurrentDirection TEXT("RefCurrentDirection")
#define vdnWholeSimulationTension TEXT("WholeSimulationTension")
#define vdnWholeSimulationPayoutRate TEXT("WholeSimulationPayoutRate")
#define vdnXBendStiffness TEXT("xBendStiffness")
#define vdnXBendMomentIn TEXT("xBendMomentIn")
#define vdnYBendMomentIn TEXT("yBendMomentIn")
#define vdnXBendMomentOut TEXT("xBendMomentOut")
#define vdnYBendMomentOut TEXT("yBendMomentOut")
#define vdnAxialStiffness TEXT("AxialStiffness")
#define vdnTorsionalStiffness TEXT("TorsionalStiffness")
#define vdnPayoutRate TEXT("PayoutRate")
#define vdnExternallyCalculatedPrimaryMotion TEXT("ExternallyCalculatedPrimaryMotion")
#define vdnExternallyCalculatedImposedMotion TEXT("ExternallyCalculatedImposedMotion")
#define vdnPitchController TEXT("PitchController")
#define vdnGeneratorTorqueController TEXT("GeneratorTorqueController")
#define vdnGeneratorMotionController TEXT("GeneratorMotionController")

/* Move objects specification */
#define sbDisplacement 0
#define sbPolarDisplacement 1
#define sbNewPosition 2
#define sbRotation 3

/* Module constants */
#define moduleDynamics 0
#define moduleVIV 1

/* Modify model actions */
#define modifyModelActionDeleteUnusedTypes 0
#define modifyModelActionDeleteUnusedVariableDataSources 1

/* Licence reconnection constants */
#define lrBegin 0
#define lrContinue 1
#define lrEnd 2

/* External function capabilities */
#define efcUnicode 0x00000001
#define efcImplicitIntegration 0x00000002

/* Period constants */
#define pnBuildUp 0
/* Stage n has Period number n */
#define pnSpecifiedPeriod 32001
#define pnLatestWave 32002
#define pnWholeSimulation 32003
#define pnStaticState 32004
#define pnInstantaneousValue 32005

/* For TObjectExtra.LinePoint */
#define ptEndA 0
#define ptEndB 1
#define ptTouchdown 2
#define ptNodeNum 3
#define ptArcLength 4

/* For TObjectExtra.RadialPos */
#define rpInner 0
#define rpOuter 1
#define rpMid 2

/* Special integer value equivalent to '~' in OrcaFlex UI */
#define OrcinaDefaultWord 65500

/* For C_GetDataType */
#define dtDouble 0
#define dtInteger 1
#define dtString 2
#define dtVariable 3
#define dtIntegerIndex 4
#define dtBoolean 5

/* For C_PerformDataAction */
#define daIsDefault 0
#define daHasChanged 1
#define daIsMarkedAsChanged 2
#define daSetToDefault 3
#define daSetToOriginalValue 4
#define daMarkAsChanged 5

/* For C_EnumerateVars */
#define rtTimeHistory 0
#define rtRangeGraph 1
#define rtLinkedStatistics 2
#define rtFrequencyDomain 3

/* For range graph arclength range modes */
#define armEntireRange 0
#define armEntireLine armEntireRange /* legacy name */
#define armSpecifiedArclengths 1
#define armSpecifiedSections 2

/* For C_GetModelState */
#define msReset 0
#define msCalculatingStatics 1
#define msInStaticState 2
#define msRunningSimulation 3
#define msSimulationStopped 4
#define msSimulationStoppedUnstable 5

/* For TNewModelParams */
#define mtStandard 0
#define mtVariation 1
#define mtRestart 2

/* For C_GetDiffractionState */
#define dsReset 0
#define dsCalculating 1
#define dsCalculationComplete 2

/* For C_GetBinaryFileType */
#define ftDataFile 0
#define ftStaticStateSimulationFile 1
#define ftDynamicSimulationFile 2

/* Data file type for memory load and save */
#define dftBinary 0
#define dftText 1

/* Spreadsheet file type for memory save */
#define sftCsv 0
#define sftTab 1
#define sftXlsx 2

/* For C_CreateTimeHistorySummary */
#define thstSpectralDensity 0
#define thstEmpiricalDistribution 1
#define thstRainflowHalfCycles 2
#define thstRainflowAssociatedMean 3

/* For TViewParameters.GraphicsMode */
#define gmWireFrame 0
#define gmShaded 1

/* For TViewParameters.ShadedFillMode */
#define fmSolid 0
#define fmMesh 1

/* For TViewParameters.FileFormat */
#define bffWindowsBitmap 0
#define bffPNG 1
#define bffGIF 2
#define bffJPEG 3
#define bffPDF 4
#define bffRGB 5

/* For C_SaveExternalProgramFile */
#define eftShear7dat 0
#define eftShear7mds 1
#define eftShear7out 2
#define eftShear7plt 3
#define eftShear7anm 4
#define eftShear7dmg 5
#define eftShear7fat 6
#define eftShear7out1 7
#define eftShear7out2 8
#define eftShear7allOutput 9
#define eftShear7str 10
#define eftVIVAInput 11
#define eftVIVAOutput 12
#define eftVIVAModes 13
#define eftShear7cat 14
#define eftShear7inhyst 15
#define eftShear7curv 16
#define eftShear7zetahyst 17
#define eftShear7sth 18
#define eftShear7dth 19

/* For C_SaveSpreadsheet */
#define sptSummaryResults 0
#define sptFullResults 1
#define sptWaveSearch 2
#define sptVesselDisplacementRAOs 3
#define sptVesselSpectralResponse 4
#define sptLineClashingReport 5
#define sptDetailedProperties 6
#define sptLineTypesPropertiesReport 7
#define sptCodeChecksProperties 8
#define sptSupportGeometryTable 9
#define sptAirGapReport 10
#define sptDiffractionResults 11
#define sptDiffractionMeshDetails 12
#define sptDiffractionWaveComponents 13

/* For C_SaveDiffractionMesh */
#define emtAutoGeneratedControlSurface 0
#define emtAutoGeneratedFreeSurfacePanelledZone 1

/* For frequency domain process type */
#define iptWave 0
#define iptWind 1
#define iptWaveDrift 2

/* For TExtremeStatisticsSpecification.Distribution */
#define evdRayleigh 0
#define evdWeibull 1
#define evdGPD 2

/* For TExtremeStatisticsSpecification.ExtremesToAnalyse */
#define exUpperTail 0
#define exLowerTail 1

/* For C_CreatePanelMesh */
#define mfWamitGdf 0
#define mfWamitFdf 1
#define mfWamitCsf 2
#define mfNemohDat 3
#define mfHydrostarHst 4
#define mfAqwaDat 5
#define mfSesamFem 6
#define mfGmshMsh 7
#define mfWavefrontObj 8

#define msNone 0
#define msXZ 1
#define msYZ 2
#define msXZYZ 3

/* For C_AssignWireFrameFromPanelMesh */
#define wftEdges 0
#define wftPanels 1
#define WireFrameFromPanelMeshOptions(Symmetry, WireFrameType) (Symmetry) | ((WireFrameType) << 3)

/* For C_ExecutePostCalculationActions */
#define atInProcPython 0
#define atCmdScript 1

/* Object extra fields, also used by user defined results */
#define oefEnvironmentPos 0
#define oefLinePoint 1
#define oefRadialPos 2
#define oefTheta 3
#define oefWingName 4
#define oefClearanceLineName 5
#define oefWinchConnectionPoint 6
#define oefRigidBodyPos 7
#define oefExternalResultText 8
#define oefDisturbanceVesselName 9
#define oefSupportIndex 10
#define oefSupportedLineName 11
#define oefBladeIndex 12
#define oefElementIndex 13
#define oefSeaSurfaceScalingFactor 14

/* For user defined results, values for LineResultPoints */
#define lrpNone 0
#define lrpWholeLine 1
#define lrpNodes 2
#define lrpMidSegments 3
#define lrpMidSegmentsAndEnds 4
#define lrpEnds 5

/* For TModeDetails.ModeType */
#define mtNotAvailable -1
#define mtTransverse 0
#define mtMostlyTransverse 1
#define mtInline 2
#define mtMostlyInline 3
#define mtAxial 4
#define mtMostlyAxial 5
#define mtMixed 6
#define mtRotational 7
#define mtMostlyRotational 8

/* For diffraction output */
#define dotHeadings 0
#define dotFrequencies 1
#define dotAngularFrequencies 2
#define dotPeriods 3
#define dotPeriodsOrFrequencies 4
#define dotHydrostaticResults 5
#define dotAddedMass 6
#define dotInfiniteFrequencyAddedMass 7
#define dotDamping 8
#define dotLoadRAOsHaskind 9
#define dotLoadRAOsDiffraction 10
#define dotDisplacementRAOs 11
#define dotMeanDriftHeadingPairs 12
#define dotQTFHeadingPairs 13
#define dotQTFFrequencies 14
#define dotQTFAngularFrequencies 15
#define dotQTFPeriods 16
#define dotQTFPeriodsOrFrequencies 17
#define dotMeanDriftLoadPressureIntegration 18
#define dotMeanDriftLoadControlSurface 19
#define dotFieldPointPressure 20
#define dotFieldPointRAO 21
#define dotFieldPointVelocity 22
#define dotFieldPointRAOGradient 23
#define dotPanelCount 24
#define dotPanelGeometry 25
#define dotPanelPressure 26
#define dotPanelVelocity 27
#define dotQuadraticLoadFromPressureIntegration 28
#define dotQuadraticLoadFromControlSurface 29
#define dotDirectPotentialLoad 30
#define dotIndirectPotentialLoad 31
#define dotExtraRollDamping 32
#define dotRollDampingPercentCritical 33
#define dotPanelPressureDiffraction 34
#define dotPanelPressureRadiation 35
#define dotPanelVelocityDiffraction 36
#define dotPanelVelocityRadiation 37
#define dotMeanDriftLoadMomentumConservation 38

/* For fatigue output */
#define fotOutputPointCount 0
#define fotHomogeneousPipeOutputPointDetails 1
#define fotComponentOutputPointDetails 2
#define fotMooringOutputPointDetails 3
#define fotShear7OutputPointDetails 4
#define fotHistogramOutputPointDetails 5
#define fotTheta 6
#define fotDeterministicLoadCaseDamage 7
#define fotSpectralLoadCaseDamage 8
#define fotShear7LoadCaseDamage 9
#define fotOverallDamage 10
#define fotHistogramBins 11
#define fotHistogramLoadCaseCycleRate 12
#define fotHistogramCombinedCycleRate 13

/* For C_GetModelProperty */
#define propIsTimeDomainDynamics 0
#define propIsFrequencyDomainDynamics 1
#define propIsDeterministicFrequencyDomainDynamics 2
#define propGeneralHandle 3
#define propEnvironmentHandle 4
#define propFrictionCoefficientsHandle 5
/* define propSolidFrictionCoefficientsHandle for back-compat reasons */
#define propSolidFrictionCoefficientsHandle propFrictionCoefficientsHandle
#define propLineContactHandle 6
#define propCodeChecksHandle 7
#define propShear7DataHandle 8
#define propVIVADataHandle 9
#define propIsPayoutRateNonZero 10
#define propCanResumeSimulation 11
#define propStageZeroIsBuildUp 12
#define propTargetRestartStateRecordingTimes 13
#define propActualRestartStateRecordingTimes 14
#define propEulerBucklingLimitExceededForLine 15
#define propEulerBucklingLimitExceededForModel 16

struct TOrcFxAPIHandleImpl;
typedef struct TOrcFxAPIHandleImpl *TOrcFxAPIHandle;

typedef struct {
    int PeriodNum;
    int Unused;
    double FromTime;
    double ToTime;
} TPeriod;

#ifdef _IndexedVectorsAndMatrices_
typedef double TVector[3];
typedef double TVector2[2];
typedef double TVector6[6];
typedef TVector TMatrix[3];
typedef TVector2 TMatrix2[2];
typedef TVector6 TMatrix6[6];
#else
typedef struct { double X, Y, Z; } TVector;
typedef struct { double X, Y; } TVector2;
typedef struct { double TX, TY, TZ, RX, RY, RZ; } TVector6;
typedef struct { TVector X, Y, Z; } TMatrix;
typedef struct { TVector2 X, Y; } TMatrix2;
typedef struct { TVector6 TX, TY, TZ, RX, RY, RZ; } TMatrix6;
#endif

typedef struct {
    double Re;
    double Im;
} TComplex;

typedef TVector TPanel[4];

typedef struct {
    int Size;
    int ThreadCount;
} TCreateModelParams;

typedef struct {
    int Size;
    int ModelType;
    LPCSTR ParentFileName;
} TNewModelParamsA;

typedef struct {
    int Size;
    int ModelType;
    LPCWSTR ParentFileName;
} TNewModelParamsW;

#ifdef UNICODE
#define TNewModelParams TNewModelParamsW
#else
#define TNewModelParams TNewModelParamsA
#endif

typedef struct {
    TVector EnvironmentPos;
    int LinePoint;
    int NodeNum;
    double ArcLength;
    int RadialPos;
    double Theta;
} TObjectExtra;

typedef struct {
    int Size;
    TVector EnvironmentPos;
    int LinePoint;
    int NodeNum;
    double ArcLength;
    int RadialPos;
    double Theta;
    LPCSTR WingName;
    LPCSTR ClearanceLineName;
    int WinchConnectionPoint;
    TVector RigidBodyPos;
    LPCSTR ExternalResultText;
    LPCSTR DisturbanceVesselName;
    int SupportIndex;
    LPCSTR SupportedLineName;
    int BladeIndex;
    int ElementIndex;
    double SeaSurfaceScalingFactor;
} TObjectExtra2A;

typedef struct {
    int Size;
    TVector EnvironmentPos;
    int LinePoint;
    int NodeNum;
    double ArcLength;
    int RadialPos;
    double Theta;
    LPCWSTR WingName;
    LPCWSTR ClearanceLineName;
    int WinchConnectionPoint;
    TVector RigidBodyPos;
    LPCWSTR ExternalResultText;
    LPCWSTR DisturbanceVesselName;
    int SupportIndex;
    LPCWSTR SupportedLineName;
    int BladeIndex;
    int ElementIndex;
    double SeaSurfaceScalingFactor;
} TObjectExtra2W;

#ifdef UNICODE
#define TObjectExtra2 TObjectExtra2W
#else
#define TObjectExtra2 TObjectExtra2A
#endif

typedef struct {
    double StdDev;
    double Mean;
    double TimeOfMax;
    double ValueAtMax;
    double LinkedValueAtMax;
    double TimeOfMin;
    double ValueAtMin;
    double LinkedValueAtMin;
} TStatisticsQuery;

typedef struct {
    int Size;
    double Mean;
    double StdDev;
    double m0;
    double m2;
    double m4;
    double Tz;
    double Tc;
    double Bandwidth;
    double RMS;
} TTimeSeriesStatistics;

typedef struct {
    int Size;
    double StaticValue;
    double StdDev;
    double Amplitude;
    double PhaseLag;
    double m0;
    double m1;
    double m2;
    double m3;
    double m4;
    double Tz;
    double Tc;
    double Bandwidth;
} TFrequencyDomainResults;

typedef struct {
    int WaveTrainIndex;
    double Frequency;
    double Amplitude;
    double PhaseLagWrtWaveTrainTime;
    double PhaseLagWrtSimulationTime;
    double WaveNumber;
    double Direction;
} TWaveComponent;

typedef struct {
    int WaveTrainIndex;
    double Frequency;
    double FrequencyLowerBound;
    double FrequencyUpperBound;
    double Amplitude;
    double PhaseLagWrtWaveTrainTime;
    double PhaseLagWrtSimulationTime;
    double WaveNumber;
    double Direction;
} TWaveComponent2;

typedef struct {
    double Frequency;
    double FrequencyLowerBound;
    double FrequencyUpperBound;
    double Amplitude;
    double PhaseLagWrtWindTime;
    double PhaseLagWrtSimulationTime;
} TWindComponent;

typedef struct {
    int ProcessType;
    int ProcessIndex;
    double Frequency;
    double FrequencyLowerBound;
    double FrequencyUpperBound;
} TFrequencyDomainProcessComponent;

typedef struct {
    int ProcessType;
    int ProcessIndex;
    double Frequency;
    double FrequencyLowerBound;
    double FrequencyUpperBound;
    double PhaseLagWrtSimulationTime;
} TFrequencyDomainProcessComponent2;

typedef struct {
    TOrcFxAPIHandle ObjectHandle;
    int PointIndex;
} TMoveObjectPoint;

typedef struct {
    int Size;
    int MoveSpecifiedBy;
    TVector Displacement;
    double PolarDisplacementDirection;
    double PolarDisplacementDistance;
    TMoveObjectPoint NewPositionReferencePoint;
    TVector NewPosition;
    double RotationAngle;
    TVector2 RotationCentre;
} TMoveObjectSpecification;

typedef struct {
    int Size;
    double Mass;
    TVector CentreOfMass;
    TMatrix MassMomentOfInertia;
    double Volume;
    TVector CentreOfVolume;
} TCompoundProperties;

typedef struct {
    int Size;
    double *lpX;
    double *lpY;
} TGraphCurve;

typedef char TCurveNameA[30];
typedef wchar_t TCurveNameW[30];
#ifdef UNICODE
#define TCurveName TCurveNameW
#else
#define TCurveName TCurveNameA
#endif

typedef char TDLLVersionA[16];
typedef wchar_t TDLLVersionW[16];
#ifdef UNICODE
#define TDLLVersion TDLLVersionW
#else
#define TDLLVersion TDLLVersionA
#endif

typedef char TObjectNameA[50];
typedef wchar_t TObjectNameW[50];
#ifdef UNICODE
#define TObjectName TObjectNameW
#else
#define TObjectName TObjectNameA
#endif

typedef struct {
    TOrcFxAPIHandle ObjectHandle;
    int ObjectType;
    TObjectNameA ObjectName;
} TObjectInfoA;

typedef struct {
    TOrcFxAPIHandle ObjectHandle;
    int ObjectType;
    TObjectNameW ObjectName;
} TObjectInfoW;

#ifdef UNICODE
#define TObjectInfo TObjectInfoW
#else
#define TObjectInfo TObjectInfoA
#endif

typedef struct {
    int Size;
    TCurveNameA Min;
    TCurveNameA Max;
    TCurveNameA Mean;
    TCurveNameA StdDev;
    TCurveNameA Upper;
    TCurveNameA Lower;
} TRangeGraphCurveNamesA;

typedef struct {
    int Size;
    TCurveNameW Min;
    TCurveNameW Max;
    TCurveNameW Mean;
    TCurveNameW StdDev;
    TCurveNameW Upper;
    TCurveNameW Lower;
} TRangeGraphCurveNamesW;

#ifdef UNICODE
#define TRangeGraphCurveNames TRangeGraphCurveNamesW
#else
#define TRangeGraphCurveNames TRangeGraphCurveNamesA
#endif

typedef struct {
    int Size;
    int Mode;
    double FromArclength;
    double ToArclength;
    int FromSection;
    int ToSection;
} TArclengthRange;

typedef struct {
    int Size;
    int FirstMode;
    int LastMode;
    BOOL IncludeCoupledObjects;
} TModesFilesParameters;

typedef TModesFilesParameters TShear7MdsFileParameters;
typedef TModesFilesParameters TVIVAModesFilesParameters;

typedef struct {
    int Size;
    double ViewSize;
    double ViewAzimuth;
    double ViewElevation;
    TVector ViewCentre;
    int Height;
    int Width;
    COLORREF BackgroundColour;
    BOOL DrawViewAxes;
    BOOL DrawScaleBar;
    BOOL DrawGlobalAxes;
    BOOL DrawEnvironmentAxes;
    BOOL DrawLocalAxes;
    BOOL DrawOutOfBalanceForces;
    BOOL DrawNodeAxes;
    int GraphicsMode;
    int FileFormat;
    double ViewGamma;
    TOrcFxAPIHandle RelativeToObjectHandle;
    TOrcFxAPIHandle DisturbanceVesselHandle;
    TVector2 DisturbancePosition;
    int ShadedFillMode;
    BOOL DrawNameLabels;
    BOOL DrawConnections;
    int LabelScale;
    BOOL DrawOrigins;
    BOOL MonochromeOutput;
    BOOL AddDetailsToOutput;
    int JpegCompressionQuality;
} TViewParameters;

typedef struct {
    int Size;
    int FileFormat;
    int JpegCompressionQuality;
} TBitmapCanvasSaveFormat;

typedef struct {
    int Size;
    BOOL CalculateShapes;
    int FirstMode;
    int LastMode;
    BOOL IncludeCoupledObjects;
    BOOL AnglesReportedInRadians;
} TModalAnalysisSpecification;

typedef struct {
    int Size;
    int ModeNumber;
    double Period;
    double *lpShapeWrtGlobal;
    double *lpShapeWrtLocal;
    int ModeType;
    double PercentageInInlineDirection;
    double PercentageInAxialDirection;
    double PercentageInTransverseDirection;
    double PercentageInRotationalDirection;
    double Mass;
    double Stiffness;
} TModeDetails;

typedef struct {
    TOrcFxAPIHandle Owner;
    double Arclength;
} TModeLoadOutputPoint;

typedef struct {
    TVector Force;
    TVector Moment;
} TModeLoad;

typedef struct {
    int Size;
    int MaxNumberOfIterations;
    double Tolerance;
    double MaxStep;
    double Delta;
} TSolveEquationParameters;

typedef struct {
    int Size;
    int VarID;
    LPCSTR lpVarName;
    LPCSTR lpVarUnits;
    LPCSTR lpFullName;
    TOrcFxAPIHandle ObjectHandle;
} TVarInfoA;

typedef struct {
    int Size;
    int VarID;
    LPCWSTR lpVarName;
    LPCWSTR lpVarUnits;
    LPCWSTR lpFullName;
    TOrcFxAPIHandle ObjectHandle;
} TVarInfoW;

#ifdef UNICODE
#define TVarInfo TVarInfoW
#else
#define TVarInfo TVarInfoA
#endif

typedef struct {
    int Size;
    double InnerTimeStep;
    double OuterTimeStep;
} TTimeSteps;

typedef struct {
    int Size;
    BOOL SetLinesToUserSpecifiedStartingShape;
} TUseCalculatedPositionsForStaticsParameters;

typedef struct {
    int Size;
    BOOL EnableAutoSave;
    int AutoSaveIntervalMinutes;
    LPCSTR AutoSaveFileName;
} TRunSimulationParametersA;

typedef struct {
    int Size;
    BOOL EnableAutoSave;
    int AutoSaveIntervalMinutes;
    LPCWSTR AutoSaveFileName;
} TRunSimulationParametersW;

#ifdef UNICODE
#define TRunSimulationParameters TRunSimulationParametersW
#else
#define TRunSimulationParameters TRunSimulationParametersA
#endif

typedef struct {
    int Size;
    char Codec[4];
    double Interval;
} TAVIFileParameters;

typedef struct {
    double StartTime;
    double StopTime;
    double CurrentTime;
} TSimulationTimeStatus;

typedef struct {
    int Size;
    double SpectralDensityFundamentalFrequency;
} TTimeHistorySummarySpecification;

typedef struct {
    int Count;
    LPCSTR *lpNames;
    LPCSTR *lpValues;
} TObjectTagsA;

typedef struct {
    int Count;
    LPCWSTR *lpNames;
    LPCWSTR *lpValues;
} TObjectTagsW;

#ifdef UNICODE
#define TObjectTags TObjectTagsW
#else
#define TObjectTags TObjectTagsA
#endif

typedef struct {
    double Value;
    double Count;
} TCycleBin;

typedef struct {
    double Lower;
    double Upper;
} TInterval;

typedef struct {
    int Size;
    int Distribution;
    int ExtremesToAnalyse;
    double Threshold;
    double DeclusterPeriod;
} TExtremeStatisticsSpecification;

typedef struct {
    int Size;
    double StormDurationHours;
    double RiskFactor;
    double ConfidenceLevel;
} TExtremeStatisticsQuery;

typedef struct {
    int Size;
    double MostProbableExtremeValue;
    double ExtremeValueWithRiskFactor;
    double ReturnLevel;
    TInterval ConfidenceInterval;
    double Sigma;
    double SigmaStdError;
    double Xi;
    double XiStdError;
} TExtremeStatisticsOutput;

typedef struct {
    double Value;
    double LowerBound;
    double UpperBound;
} TWaveScatterBin;

typedef struct {
    int Size;
    LPCSTR BatchScriptFileName;
    LPCSTR TextDataFilePath;
    LPCSTR FatigueAnalysisFileName;
    LPCSTR FatigueLoadCaseSimulationPath;
} TWaveScatterAutomationSpecificationA;

typedef struct {
    int Size;
    LPCWSTR BatchScriptFileName;
    LPCWSTR TextDataFilePath;
    LPCWSTR FatigueAnalysisFileName;
    LPCWSTR FatigueLoadCaseSimulationPath;
} TWaveScatterAutomationSpecificationW;

#ifdef UNICODE
#define TWaveScatterAutomationSpecification TWaveScatterAutomationSpecificationW
#else
#define TWaveScatterAutomationSpecification TWaveScatterAutomationSpecificationA
#endif

typedef struct {
    TOrcFxAPIHandle ObjectHandle;
    TObjectExtra2A *lpObjectExtra;
    int VarID;
} TTimeHistorySpecificationA;

typedef struct {
    TOrcFxAPIHandle ObjectHandle;
    TObjectExtra2W *lpObjectExtra;
    int VarID;
} TTimeHistorySpecificationW;

#ifdef UNICODE
#define TTimeHistorySpecification TTimeHistorySpecificationW
#else
#define TTimeHistorySpecification TTimeHistorySpecificationA
#endif

typedef struct {
    TOrcFxAPIHandle Handle;
    int64_t Len;
} TMemBuffer;

typedef struct {
    double Volume;
    TVector CentreOfBuoyancy;
    double Mass;
    TVector CentreOfMass;
    TMatrix6 RestoringMatrix;
    TMatrix6 InertiaMatrix;
    double Awp;
    double Lxx;
    double Lyy;
    double Lxy;
    TVector2 CentreOfFloatation;
} TDiffractionBodyHydrostaticInfo;

typedef struct {
    int ObjectId;
    TPanel Vertices;
    TVector Centroid;
    TVector Normal;
    double Area;
} TDiffractionPanelGeometry;

typedef struct {
    double Frequency;
    double FrequencyLowerBound;
    double FrequencyUpperBound;
    double Amplitude;
    double WaveNumber;
    double Direction;
} TDiffractionWaveComponent;

typedef struct {
    double Arclength;
    int SNCurveIndex;
    int RadialPos;
    double SCF;
    double ThicknessCorrectionFactor;
} TFatigueHomogeneousPipeOutputPointDetails;

typedef struct {
    double Arclength;
} TFatigueComponentOutputPointDetails;

typedef struct {
    double Arclength;
    int TNCurveIndex;
} TFatigueMooringOutputPointDetails;

typedef struct {
    double Arclength;
    double xOverL;
} TFatigueShear7OutputPointDetails;

typedef struct {
    double Arclength;
    int RadialPos;
} THistogramOutputPointDetails;

typedef struct {
    double MinResponse;
    double MaxResponse;
    double MeanResponse;
    double Damage;
    double DamageRate;
} TFatigueDeterministicLoadCaseDamage;

typedef struct {
    double MeanResponse;
    double Damage;
    double DamageRate;
} TFatigueSpectralLoadCaseDamage;

typedef struct {
    double Damage;
    double DamageRate;
} TFatigueShear7LoadCaseDamage;

typedef struct {
    double Damage;
    double Life;
} TFatigueOverallDamage;

/*=============== External functions ============*/

typedef struct {
    int Size;
    int ID;
    LPCSTR lpName;
    LPCSTR lpUnits;
} TExtFnResultInfoA;

typedef struct {
    int Size;
    int ID;
    LPCWSTR lpName;
    LPCWSTR lpUnits;
} TExtFnResultInfoW;

#ifdef UNICODE
#define TExtFnResultInfo TExtFnResultInfoW
#else
#define TExtFnResultInfo TExtFnResultInfoA
#endif

#define eaInitialise 0
#define eaFinalise 1
#define eaCalculate 2
#define eaStoreStateCreate 3
#define eaStoreStateDestroy 4
#define eaCalculateNominalValue 5
#define eaDeriveResult 6
#define eaLogResultCreate 7
#define eaLogResultDestroy 8
#define eaTrackCalculation 9
#define eaRegisterResults 10

typedef struct {
    const int Size;
    const int Action;
    const double SimulationTime;
    double Value;
    const BOOL Successful;
    const TOrcFxAPIHandle ObjectHandle;
    const TObjectExtra2A * const lpObjectExtra;
    const char * const lpObjectParameters;
    const void * const lpWorkingDataHandle;
    void *lpData;
    const char * const lpDataSourceName;
    void *lpStateData;
    int LengthOfStateData;
    const char * const lpDataName;
    const void * const lpInstantaneousCalculationData;
    const char * const lpModelDirectory;
    BOOL UpdateDuringStatics;
    void *lpLogData;
    int LengthOfLogData;
    const int ResultID;
    const BOOL NewTimeStep;
    void *lpStructValue;
    const TOrcFxAPIHandle ModelHandle;
    const char * const lpModelFileName;
    const TOrcFxAPIHandle DataObjectHandle;
    BOOL CanResumeSimulation;
} TExtFnInfoA, TExternalFunctionInfoA;

typedef struct {
    const int Size;
    const int Action;
    const double SimulationTime;
    double Value;
    const BOOL Successful;
    const TOrcFxAPIHandle ObjectHandle;
    const TObjectExtra2W * const lpObjectExtra;
    const wchar_t * const lpObjectParameters;
    const void * const lpWorkingDataHandle;
    void *lpData;
    const wchar_t * const lpDataSourceName;
    void *lpStateData;
    int LengthOfStateData;
    const wchar_t * const lpDataName;
    const void * const lpInstantaneousCalculationData;
    const wchar_t * const lpModelDirectory;
    BOOL UpdateDuringStatics;
    void *lpLogData;
    int LengthOfLogData;
    const int ResultID;
    const BOOL NewTimeStep;
    void *lpStructValue;
    const TOrcFxAPIHandle ModelHandle;
    const wchar_t * const lpModelFileName;
    const TOrcFxAPIHandle DataObjectHandle;
    BOOL CanResumeSimulation;
} TExtFnInfoW, TExternalFunctionInfoW;

#ifdef UNICODE
#define TExternalFunctionInfo TExternalFunctionInfoW
#define TExtFnInfo TExtFnInfoW
#else
#define TExternalFunctionInfo TExternalFunctionInfoA
#define TExtFnInfo TExtFnInfoA
#endif

typedef struct {
    int Size;
    TVector Position;
    TMatrix NodeOrientation;
    TMatrix OrientationIn;
    TMatrix OrientationOut;
    TVector Velocity;
    TVector AngularVelocity;
    double AlphaIn;
    double AlphaOut;
    TVector2 CurvatureIn;
    TVector2 CurvatureOut;
    double NodeArcLength;
    double MidSegArcLengthIn;
    double MidSegArcLengthOut;
    double SegmentStrain;
    double SegmentTwist;
} TNodeInstantaneousCalculationData;

typedef struct {
    int Size;
    TVector Position;
    TMatrix Orientation;
    TVector Velocity;
    TVector AngularVelocity;
} TWingInstantaneousCalculationData;

typedef struct {
    int Size;
    TVector Position;
    TMatrix Orientation;
    TVector Velocity;
    TVector AngularVelocity;
    TVector LFPosition;
    TMatrix LFOrientation;
    TVector LFVelocity;
    TVector LFAngularVelocity;
    TVector WFPosition;
    TMatrix WFOrientation;
    TVector WFVelocity;
    TVector WFAngularVelocity;
} TVesselInstantaneousCalculationData;

typedef struct {
    int Size;
    TVector Position;
    TMatrix Orientation;
    TVector Velocity;
    TVector AngularVelocity;
    double ProportionWet;
    TVector WettedCentroidPosition;
    TVector FluidVelocity;
    double FluidDensity;
} TBuoyInstantaneousCalculationData;

typedef struct {
    int Size;
    TVector InFramePosition;
    TMatrix InFrameOrientation;
    TVector InFrameVelocity;
    TVector InFrameAngularVelocity;
    TVector OutFramePosition;
    TMatrix OutFrameOrientation;
    TVector OutFrameVelocity;
    TVector OutFrameAngularVelocity;
} TConstraintInstantaneousCalculationData;

typedef struct {
    int Size;
    double GeneratorAngVel;
    double MainShaftAngVel;
    int BladeCount;
    double BladePitchAngle;
    double RotorAngle;
    double HorizontalHubWindSpeed;
    TVector HubRelativeWindVelocity;
    TVector TurbinePosition;
    TMatrix TurbineOrientation;
    TVector TurbineVelocity;
    TVector TurbineAngularVelocity;
    TVector TurbineAcceleration;
    TVector TurbineAngularAcceleration;
} TTurbineInstantaneousCalculationData;

typedef struct {
    int Size;
    TVector Position;
    TMatrix Orientation;
    TVector Velocity;
    TVector AngularVelocity;
    TVector Acceleration;
    TVector AngularAcceleration;
} TExternallyCalculatedImposedMotionStructValue, TExternallyCalculatedPrimaryMotionStructValue;

typedef struct {
    int Size;
    double Value;
    double Velocity;
    double Acceleration;
} TScalarStructValue;

typedef struct {
    int Size;
    int Format;
    double Scale;
    int BodyNumber;
    BOOL IncludeDryPanels;
} TPanelMeshImportOptions;

typedef struct {
    int Size;
    TPeriod Period;
} TLineClashingReportParameters;

typedef struct {
    int Size;
    TPeriod Period;
} TAirGapReportParameters;

/*=============== Functions: Callback ===============*/

typedef void (__stdcall *TEnumerateObjectsProcA)(TOrcFxAPIHandle, const TObjectInfoA*);
typedef void (__stdcall *TEnumerateObjectsProcW)(TOrcFxAPIHandle, const TObjectInfoW*);
#ifdef UNICODE
#define TEnumerateObjectsProc TEnumerateObjectsProcW
#else
#define TEnumerateObjectsProc TEnumerateObjectsProcA
#endif

typedef void (__stdcall *TProgressHandlerProc)(TOrcFxAPIHandle, int, BOOL*);

typedef void (__stdcall *TStringProgressHandlerProcA)(TOrcFxAPIHandle, LPCSTR, BOOL*);
typedef void (__stdcall *TStringProgressHandlerProcW)(TOrcFxAPIHandle, LPCWSTR, BOOL*);
#ifdef UNICODE
#define TStringProgressHandlerProc TStringProgressHandlerProcW
#else
#define TStringProgressHandlerProc TStringProgressHandlerProcA
#endif

typedef TStringProgressHandlerProcW TStaticsProgressHandlerProcW;
typedef TStringProgressHandlerProcA TStaticsProgressHandlerProcA;
typedef TStringProgressHandlerProc TStaticsProgressHandlerProc;

typedef void (__stdcall *TDynamicsProgressHandlerProc)(TOrcFxAPIHandle, double, double, double, BOOL*);

typedef double (__stdcall *TSolveEquationCalcYProc)(INT_PTR, double, int*);

typedef void (__stdcall *TEnumerateVarsProcA)(const TVarInfoA*);
typedef void (__stdcall *TEnumerateVarsProcW)(const TVarInfoW*);
#ifdef UNICODE
#define TEnumerateVarsProc TEnumerateVarsProcW
#else
#define TEnumerateVarsProc TEnumerateVarsProcA
#endif

typedef void (__stdcall *TCorrectExternalFileReferencesProc)(TOrcFxAPIHandle);

typedef void (__stdcall *TLicenceNotFoundHandlerProc)(int, BOOL*, INT_PTR*);


/*=============== Functions: General ===============*/

void __stdcall C_AssignWireFrameFromPanelMesh(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle PanelMeshHandle,
    int Options,
    const TVector *lpImportOrigin,
    int *lpStatus
);

void __stdcall C_AttachToThread(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_ClearModel(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_CopyBuffer(
    TOrcFxAPIHandle SourceBufferHandle,
    unsigned char *lpDestBuffer,
    int64_t DestBufferLen,
    int *lpStatus
);

void __stdcall C_CreateClone(
    TOrcFxAPIHandle SourceObjectHandle,
    TOrcFxAPIHandle *lpClonedObjectHandle,
    int *lpStatus
);

void __stdcall C_CreateClone2(
    TOrcFxAPIHandle SourceObjectHandle,
    TOrcFxAPIHandle DestModelHandle,
    TOrcFxAPIHandle *lpClonedObjectHandle,
    int *lpStatus
);

void __stdcall C_CreateModel(
    TOrcFxAPIHandle *lpModelHandle,
    HWND hCaller,
    int *lpStatus
);

void __stdcall C_CreateModel2(
    TOrcFxAPIHandle *lpModelHandle,
    const TCreateModelParams *lpCreateModelParams,
    int *lpStatus
);

void __stdcall C_CreateObject(
    TOrcFxAPIHandle ModelHandle,
    int ObjectType,
    TOrcFxAPIHandle *lpObjectHandle,
    int *lpStatus
);

void __stdcall C_CreatePanelMeshA(
    LPCSTR lpFileName,
    int Format,
    double Scale,
    TOrcFxAPIHandle *lpPanelMeshHandle,
    int *lpPanelCount,
    int *lpSymmetry,
    int *lpStatus
);

void __stdcall C_CreatePanelMeshW(
    LPCWSTR lpFileName,
    int Format,
    double Scale,
    TOrcFxAPIHandle *lpPanelMeshHandle,
    int *lpPanelCount,
    int *lpSymmetry,
    int *lpStatus
);

#ifdef UNICODE
#define C_CreatePanelMesh C_CreatePanelMeshW
#else
#define C_CreatePanelMesh C_CreatePanelMeshA
#endif

void __stdcall C_CreatePanelMesh2A(
    LPCSTR lpFileName,
    const TPanelMeshImportOptions *lpOptions,
    TOrcFxAPIHandle *lpPanelMeshHandle,
    int *lpPanelCount,
    int *lpSymmetry,
    int *lpStatus
);

void __stdcall C_CreatePanelMesh2W(
    LPCWSTR lpFileName,
    const TPanelMeshImportOptions *lpOptions,
    TOrcFxAPIHandle *lpPanelMeshHandle,
    int *lpPanelCount,
    int *lpSymmetry,
    int *lpStatus
);

#ifdef UNICODE
#define C_CreatePanelMesh2 C_CreatePanelMesh2W
#else
#define C_CreatePanelMesh2 C_CreatePanelMesh2A
#endif

void __stdcall C_DefaultInMemoryLogging(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_DestroyModel(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_DestroyObject(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_DetachFromThread(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_DestroyPanelMesh(
    TOrcFxAPIHandle PanelMeshHandle,
    int *lpStatus
);

void __stdcall C_DisableInMemoryLogging(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_DisableModule(
    int Module,
    int *lpStatus
);

void __stdcall C_EnumerateObjectsA(
    TOrcFxAPIHandle ModelHandle,
    TEnumerateObjectsProcA EnumerateObjectsProc,
    int *lpNumOfObjects,
    int *lpStatus
);

void __stdcall C_EnumerateObjectsW(
    TOrcFxAPIHandle ModelHandle,
    TEnumerateObjectsProcW EnumerateObjectsProc,
    int *lpNumOfObjects,
    int *lpStatus
);

void __stdcall C_ExchangeObjects(
    TOrcFxAPIHandle ObjectHandle1,
    TOrcFxAPIHandle ObjectHandle2,
    int *lpStatus
);

#ifdef UNICODE
#define C_EnumerateObjects C_EnumerateObjectsW
#else
#define C_EnumerateObjects C_EnumerateObjectsA
#endif

void __stdcall C_ExecutePostCalculationActionsA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpFileName,
    TStringProgressHandlerProcA ReportProgressProc,
    int ActionType,
    BOOL TreatExecutionErrorsAsWarnings,
    int *lpStatus
);

void __stdcall C_ExecutePostCalculationActionsW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpFileName,
    TStringProgressHandlerProcW ReportProgressProc,
    int ActionType,
    BOOL TreatExecutionErrorsAsWarnings,
    int *lpStatus
);

#ifdef UNICODE
#define C_ExecutePostCalculationActions C_ExecutePostCalculationActionsW
#else
#define C_ExecutePostCalculationActions C_ExecutePostCalculationActionsA
#endif

void __stdcall C_ExternalFunctionPrintA(
    LPCSTR lpText,
    int *lpStatus
);

void __stdcall C_ExternalFunctionPrintW(
    LPCWSTR lpText,
    int *lpStatus
);

#ifdef UNICODE
#define C_ExternalFunctionPrint C_ExternalFunctionPrintW
#else
#define C_ExternalFunctionPrint C_ExternalFunctionPrintA
#endif

void __stdcall C_FinaliseLibrary(
    int *lpStatus
);

void __stdcall C_ForceInMemoryLogging(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_FreeBuffer(
    TOrcFxAPIHandle BufferHandle,
    int *lpStatus
);

void __stdcall C_GetActualRestartStateRecordingTimesA(
    LPCSTR lpSimFileName,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_GetActualRestartStateRecordingTimesW(
    LPCWSTR lpSimFileName,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetActualRestartStateRecordingTimes C_GetActualRestartStateRecordingTimesW
#else
#define C_GetActualRestartStateRecordingTimes C_GetActualRestartStateRecordingTimesA
#endif

void __stdcall C_GetBinaryFileTypeA(
    LPCSTR lpFileName,
    int *lpFileType,
    int *lpStatus
);

void __stdcall C_GetBinaryFileTypeW(
    LPCWSTR lpFileName,
    int *lpFileType,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetBinaryFileType C_GetBinaryFileTypeW
#else
#define C_GetBinaryFileType C_GetBinaryFileTypeA
#endif

INT_PTR __stdcall C_GetCallerLong(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_GetCompoundPropertiesA(
    int ObjectCount,
    TOrcFxAPIHandle *lpObjects,
    TOrcFxAPIHandle ReferenceObject,
    LPCSTR lpReferencePoint,
    TCompoundProperties *lpProperties,
    int *lpStatus
);

void __stdcall C_GetCompoundPropertiesW(
    int ObjectCount,
    TOrcFxAPIHandle *lpObjects,
    TOrcFxAPIHandle ReferenceObject,
    LPCWSTR lpReferencePoint,
    TCompoundProperties *lpProperties,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetCompoundProperties C_GetCompoundPropertiesW
#else
#define C_GetCompoundProperties C_GetCompoundPropertiesA
#endif

void __stdcall C_GetDLLVersionA(
    TDLLVersionA *lpRequiredDLLVersion,
    TDLLVersionA *lpDLLVersion,
    int *lpOK,
    int *lpStatus
);

void __stdcall C_GetDLLVersionW(
    TDLLVersionW *lpRequiredDLLVersion,
    TDLLVersionW *lpDLLVersion,
    int *lpOK,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetDLLVersion C_GetDLLVersionW
#else
#define C_GetDLLVersion C_GetDLLVersionA
#endif

int __stdcall C_GetFileCreatorVersionA(
    LPCSTR lpFileName,
    LPSTR lpVersion,
    int *lpStatus
);

int __stdcall C_GetFileCreatorVersionW(
    LPCWSTR lpFileName,
    LPWSTR lpVersion,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetFileCreatorVersion C_GetFileCreatorVersionW
#else
#define C_GetFileCreatorVersion C_GetFileCreatorVersionA
#endif

int __stdcall C_GetLastErrorStringA(
    LPSTR lpErrorString
);

int __stdcall C_GetLastErrorStringW(
    LPWSTR lpErrorString
);

#ifdef UNICODE
#define C_GetLastErrorString C_GetLastErrorStringW
#else
#define C_GetLastErrorString C_GetLastErrorStringA
#endif

void __stdcall C_GetLineTypeHandles(
    TOrcFxAPIHandle ObjectHandle,
    int NodeNum,
    TOrcFxAPIHandle *lpInLineTypeHandle,
    TOrcFxAPIHandle *lpOutLineTypeHandle,
    int *lpStatus
);

void __stdcall C_GetModelHandle(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle *lpModelHandle,
    int *lpStatus
);

int __stdcall C_GetModelThreadCount(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

INT_PTR __stdcall C_GetNamedValueA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpName,
    int *lpStatus
);

INT_PTR __stdcall C_GetNamedValueW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpName,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetNamedValue C_GetNamedValueW
#else
#define C_GetNamedValue C_GetNamedValueA
#endif

void __stdcall C_GetNodeArclengths(
    TOrcFxAPIHandle ObjectHandle,
    double *lpNodeArclengths,
    int *lpNodeCount,
    int *lpStatus
);

int __stdcall C_GetNumOfWarnings(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

int __stdcall C_GetObjectTypeA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpObjectTypeName,
    int *lpStatus
);

int __stdcall C_GetObjectTypeW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpObjectTypeName,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetObjectType C_GetObjectTypeW
#else
#define C_GetObjectType C_GetObjectTypeA
#endif

void __stdcall C_GetObjectTypeFromHandle(
    TOrcFxAPIHandle ObjectHandle,
    int *lpObjectType,
    int *lpStatus
);

int __stdcall C_GetObjectTypeNameA(
    TOrcFxAPIHandle ModelHandle,
    int ObjectType,
    LPSTR lpObjectTypeName,
    int *lpStatus
);

int __stdcall C_GetObjectTypeNameW(
    TOrcFxAPIHandle ModelHandle,
    int ObjectType,
    LPWSTR lpObjectTypeName,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetObjectTypeName C_GetObjectTypeNameW
#else
#define C_GetObjectTypeName C_GetObjectTypeNameA
#endif

void __stdcall C_GetPanels(
    TOrcFxAPIHandle PanelMeshHandle,
    TPanel *lpPanels,
    int *lpStatus
);

void __stdcall C_GetRestartParentFileNameA(
    LPCSTR lpFileName,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_GetRestartParentFileNameW(
    LPCWSTR lpFileName,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRestartParentFileName C_GetRestartParentFileNameW
#else
#define C_GetRestartParentFileName C_GetRestartParentFileNameA
#endif

void __stdcall C_GetRestartParentFileNamesA(
    TOrcFxAPIHandle ModelHandle,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_GetRestartParentFileNamesW(
    TOrcFxAPIHandle ModelHandle,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRestartParentFileNames C_GetRestartParentFileNamesW
#else
#define C_GetRestartParentFileNames C_GetRestartParentFileNamesA
#endif

void __stdcall C_GetUnitsConversionFactorA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpUnits,
    double *lpConversionFactor,
    int *lpStatus
);

void __stdcall C_GetUnitsConversionFactorW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpUnits,
    double *lpConversionFactor,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetUnitsConversionFactor C_GetUnitsConversionFactorW
#else
#define C_GetUnitsConversionFactor C_GetUnitsConversionFactorA
#endif

int __stdcall C_GetWarningTextA(
    TOrcFxAPIHandle ModelHandle,
    int Index,
    int *lpStage,
    LPCSTR lpWarningText,
    int *lpStatus
);

int __stdcall C_GetWarningTextW(
    TOrcFxAPIHandle ModelHandle,
    int Index,
    int *lpStage,
    LPCWSTR lpWarningText,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetWarningText C_GetWarningTextW
#else
#define C_GetWarningText C_GetWarningTextA
#endif

void __stdcall C_GroupGetFirstChild(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle *lpChildObjectHandle,
    int *lpStatus
);

void __stdcall C_GroupGetNextSibling(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle *lpSiblingObjectHandle,
    int *lpStatus
);

void __stdcall C_GroupGetParent(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle *lpParentObjectHandle,
    int *lpStatus
);

void __stdcall C_GroupGetPrevSibling(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle *lpSiblingObjectHandle,
    int *lpStatus
);

void __stdcall C_GroupMoveAfter(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle TargetObjectHandle,
    int *lpStatus
);

void __stdcall C_GroupMoveBefore(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle TargetObjectHandle,
    int *lpStatus
);

void __stdcall C_GroupSetParent(
    TOrcFxAPIHandle ObjectHandle,
    TOrcFxAPIHandle ParentObjectHandle,
    int *lpStatus
);

void __stdcall C_LoadDataA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpDataFileName,
    int *lpStatus
);

void __stdcall C_LoadDataW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpDataFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_LoadData C_LoadDataW
#else
#define C_LoadData C_LoadDataA
#endif

void __stdcall C_LoadDataMem(
    TOrcFxAPIHandle ModelHandle,
    int DataFileType,
    const unsigned char *lpBuffer,
    int64_t BufferLen,
    int *lpStatus
);

void __stdcall C_LoadSimulationA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpSimFileName,
    int *lpStatus
);

void __stdcall C_LoadSimulationW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpSimFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_LoadSimulation C_LoadSimulationW
#else
#define C_LoadSimulation C_LoadSimulationA
#endif

void __stdcall C_LoadSimulationMem(
    TOrcFxAPIHandle ModelHandle,
    const unsigned char *lpBuffer,
    int64_t BufferLen,
    int *lpStatus
);

void __stdcall C_ModifyModel(
    TOrcFxAPIHandle ModelHandle,
    int Action,
    int *lpStatus
);

BOOL __stdcall C_ModuleEnabled(
    TOrcFxAPIHandle ModelHandle,
    int Module,
    int *lpStatus
);

void __stdcall C_MoveObjects(
    const TMoveObjectSpecification *lpSpecification,
    int PointCount,
    const TMoveObjectPoint *lpPoints,
    int *lpStatus
);

void __stdcall C_NewModelA(
    TOrcFxAPIHandle ModelHandle,
    const TNewModelParamsA *lpParams,
    int *lpStatus
);

void __stdcall C_NewModelW(
    TOrcFxAPIHandle ModelHandle,
    const TNewModelParamsW *lpParams,
    int *lpStatus
);

#ifdef UNICODE
#define C_NewModel C_NewModelW
#else
#define C_NewModel C_NewModelA
#endif

void __stdcall C_ObjectCalledA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpObjectName,
    TObjectInfoA *lpObjectInfo,
    int *lpStatus
);

void __stdcall C_ObjectCalledW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpObjectName,
    TObjectInfoW *lpObjectInfo,
    int *lpStatus
);

#ifdef UNICODE
#define C_ObjectCalled C_ObjectCalledW
#else
#define C_ObjectCalled C_ObjectCalledA
#endif

void __stdcall C_RecordExternalFunctionErrorA(
    TExternalFunctionInfoA *lpExternalFunctionInfo,
    LPCSTR lpErrorString,
    int *lpStatus
);

void __stdcall C_RecordExternalFunctionErrorW(
    TExternalFunctionInfoW *lpExternalFunctionInfo,
    LPCWSTR lpErrorString,
    int *lpStatus
);

#ifdef UNICODE
#define C_RecordExternalFunctionError C_RecordExternalFunctionErrorW
#else
#define C_RecordExternalFunctionError C_RecordExternalFunctionErrorA
#endif

void __stdcall C_RegisterLicenceNotFoundHandler(
    TLicenceNotFoundHandlerProc Handler,
    int *lpStatus
);

void __stdcall C_RemoveRestartStateFromSimulationFileA(
    LPCSTR lpSimFileName,
    BOOL DoRemove,
    int64_t *lpBytesRemoved,
    int *lpStatus
);

void __stdcall C_RemoveRestartStateFromSimulationFileW(
    LPCWSTR lpSimFileName,
    BOOL DoRemove,
    int64_t *lpBytesRemoved,
    int *lpStatus
);

#ifdef UNICODE
#define C_RemoveRestartStateFromSimulationFile C_RemoveRestartStateFromSimulationFileW
#else
#define C_RemoveRestartStateFromSimulationFile C_RemoveRestartStateFromSimulationFileA
#endif

void __stdcall C_SaveDataA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpDataFileName,
    int *lpStatus
);

void __stdcall C_SaveDataW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpDataFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveData C_SaveDataW
#else
#define C_SaveData C_SaveDataA
#endif

void __stdcall C_SaveDataMem(
    TOrcFxAPIHandle ModelHandle,
    int DataFileType,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveExternalProgramFileA(
    TOrcFxAPIHandle ObjectHandle,
    int FileType,
    void *lpParameters,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveExternalProgramFileW(
    TOrcFxAPIHandle ObjectHandle,
    int FileType,
    void *lpParameters,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveExternalProgramFile C_SaveExternalProgramFileW
#else
#define C_SaveExternalProgramFile C_SaveExternalProgramFileA
#endif

void __stdcall C_SaveSimulationA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpSimFileName,
    int *lpStatus
);

void __stdcall C_SaveSimulationW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpSimFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveSimulation C_SaveSimulationW
#else
#define C_SaveSimulation C_SaveSimulationA
#endif

void __stdcall C_SaveSimulationMem(
    TOrcFxAPIHandle ModelHandle,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveSpreadsheetA(
    TOrcFxAPIHandle ObjectHandle,
    int SpreadsheetType,
    void *lpParameters,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveSpreadsheetW(
    TOrcFxAPIHandle ObjectHandle,
    int SpreadsheetType,
    void *lpParameters,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveSpreadsheet C_SaveSpreadsheetW
#else
#define C_SaveSpreadsheet C_SaveSpreadsheetA
#endif

void __stdcall C_SaveSpreadsheetMem(
    TOrcFxAPIHandle ObjectHandle,
    int SpreadsheetType,
    int SpreadsheetFileType,
    void *lpParameters,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SetCallerLong(
    TOrcFxAPIHandle ObjectHandle,
    INT_PTR CallerLong,
    int *lpStatus
);

void __stdcall C_SetCorrectExternalFileReferencesHandler(
    TOrcFxAPIHandle ModelHandle,
    TCorrectExternalFileReferencesProc CorrectExternalFileReferencesProc,
    int *lpStatus
);

void __stdcall C_SetLibraryPolicyA(
    LPCSTR lpName,
    LPCSTR lpValue,
    int *lpStatus
);

void __stdcall C_SetLibraryPolicyW(
    LPCWSTR lpName,
    LPCWSTR lpValue,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetLibraryPolicy C_SetLibraryPolicyW
#else
#define C_SetLibraryPolicy C_SetLibraryPolicyA
#endif

void __stdcall C_SetModelThreadCount(
    TOrcFxAPIHandle ModelHandle,
    int ThreadCount,
    int *lpStatus
);

void __stdcall C_SetNamedValueA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpName,
    INT_PTR Value,
    int *lpStatus
);

void __stdcall C_SetNamedValueW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpName,
    INT_PTR Value,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetNamedValue C_SetNamedValueW
#else
#define C_SetNamedValue C_SetNamedValueA
#endif

void __stdcall C_SetProgressHandler(
    TOrcFxAPIHandle ModelHandle,
    TProgressHandlerProc ProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_UseVirtualLogging(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

double __stdcall OrcinaDefaultReal(
    void
);

double __stdcall OrcinaInfinity(
    void
);

double __stdcall OrcinaUndefinedReal(
    void
);

double __stdcall OrcinaNullReal(
    void
);

double __stdcall OrcinaDittoReal(
    void
);

/*=============== Functions: Data ===============*/

void __stdcall C_BeginDataChange(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_ClearTags(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_DataRequiresIndexA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    BOOL *lpDataRequiresIndex,
    int *lpStatus
);

void __stdcall C_DataRequiresIndexW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    BOOL *lpDataRequiresIndex,
    int *lpStatus
);

#ifdef UNICODE
#define C_DataRequiresIndex C_DataRequiresIndexW
#else
#define C_DataRequiresIndex C_DataRequiresIndexA
#endif

void __stdcall C_DeleteDataRowA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    int *lpStatus
);

void __stdcall C_DeleteDataRowW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    int *lpStatus
);

#ifdef UNICODE
#define C_DeleteDataRow C_DeleteDataRowW
#else
#define C_DeleteDataRow C_DeleteDataRowA
#endif

void __stdcall C_DeleteTagA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpName,
    int *lpStatus
);

void __stdcall C_DeleteTagW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpName,
    int *lpStatus
);

#ifdef UNICODE
#define C_DeleteTag C_DeleteTagW
#else
#define C_DeleteTag C_DeleteTagA
#endif

void __stdcall C_DestroyTagsA(
    const TObjectTagsA *lpTags,
    int *lpStatus
);

void __stdcall C_DestroyTagsW(
    const TObjectTagsW *lpTags,
    int *lpStatus
);

#ifdef UNICODE
#define C_DestroyTags C_DestroyTagsW
#else
#define C_DestroyTags C_DestroyTagsA
#endif

void __stdcall C_EndDataChange(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_GetDataDoubleA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    double *lpData,
    int *lpStatus
);

void __stdcall C_GetDataDoubleW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    double *lpData,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetDataDouble C_GetDataDoubleW
#else
#define C_GetDataDouble C_GetDataDoubleA
#endif

void __stdcall C_GetDataIntegerA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    int *lpData,
    int *lpStatus
);

void __stdcall C_GetDataIntegerW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    int *lpData,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetDataInteger C_GetDataIntegerW
#else
#define C_GetDataInteger C_GetDataIntegerA
#endif

void __stdcall C_GetDataRowCountA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int *lpRowCount,
    int *lpStatus
);

void __stdcall C_GetDataRowCountW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int *lpRowCount,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetDataRowCount C_GetDataRowCountW
#else
#define C_GetDataRowCount C_GetDataRowCountA
#endif

int __stdcall C_GetDataStringA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    LPSTR lpData,
    int *lpStatus
);

int __stdcall C_GetDataStringW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    LPWSTR lpData,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetDataString C_GetDataStringW
#else
#define C_GetDataString C_GetDataStringA
#endif

void __stdcall C_GetDataTypeA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int *lpDataType,
    int *lpStatus
);

void __stdcall C_GetDataTypeW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int *lpDataType,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetDataType C_GetDataTypeW
#else
#define C_GetDataType C_GetDataTypeA
#endif

int __stdcall C_GetTagA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpName,
    LPSTR lpValue,
    int *lpStatus
);

int __stdcall C_GetTagW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpName,
    LPWSTR lpValue,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetTag C_GetTagW
#else
#define C_GetTag C_GetTagA
#endif

int __stdcall C_GetTagCount(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_GetTagsA(
    TOrcFxAPIHandle ObjectHandle,
    TObjectTagsA *lpTags,
    int *lpStatus
);

void __stdcall C_GetTagsW(
    TOrcFxAPIHandle ObjectHandle,
    TObjectTagsW *lpTags,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetTags C_GetTagsW
#else
#define C_GetTags C_GetTagsA
#endif

void __stdcall C_GetVariableDataTypeA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    int *lpDataType,
    int *lpStatus
);

void __stdcall C_GetVariableDataTypeW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    int *lpDataType,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetVariableDataType C_GetVariableDataTypeW
#else
#define C_GetVariableDataType C_GetVariableDataTypeA
#endif

void __stdcall C_InsertDataRowA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    int *lpStatus
);

void __stdcall C_InsertDataRowW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    int *lpStatus
);

#ifdef UNICODE
#define C_InsertDataRow C_InsertDataRowW
#else
#define C_InsertDataRow C_InsertDataRowA
#endif

void __stdcall C_InvokeLineSetupWizardA(
    TOrcFxAPIHandle ModelHandle,
    TStaticsProgressHandlerProcA StaticsProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_InvokeLineSetupWizardW(
    TOrcFxAPIHandle ModelHandle,
    TStaticsProgressHandlerProcW StaticsProgressHandlerProc,
    int *lpStatus
);

#ifdef UNICODE
#define C_InvokeLineSetupWizard C_InvokeLineSetupWizardW
#else
#define C_InvokeLineSetupWizard C_InvokeLineSetupWizardA
#endif

void __stdcall C_InvokeWizard(
    TOrcFxAPIHandle ObjectHandle,
    int *lpStatus
);

void __stdcall C_PerformDataActionA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    int Action,
    void *lpValue,
    int *lpStatus
);

void __stdcall C_PerformDataActionW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    int Action,
    void *lpValue,
    int *lpStatus
);

#ifdef UNICODE
#define C_PerformDataAction C_PerformDataActionW
#else
#define C_PerformDataAction C_PerformDataActionA
#endif

void __stdcall C_SetDataDoubleA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    double Data,
    int *lpStatus
);

void __stdcall C_SetDataDoubleW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    double Data,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetDataDouble C_SetDataDoubleW
#else
#define C_SetDataDouble C_SetDataDoubleA
#endif

void __stdcall C_SetDataIntegerA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    int Data,
    int *lpStatus
);

void __stdcall C_SetDataIntegerW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    int Data,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetDataInteger C_SetDataIntegerW
#else
#define C_SetDataInteger C_SetDataIntegerA
#endif

void __stdcall C_SetDataRowCountA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int RowCount,
    int *lpStatus
);

void __stdcall C_SetDataRowCountW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int RowCount,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetDataRowCount C_SetDataRowCountW
#else
#define C_SetDataRowCount C_SetDataRowCountA
#endif

void __stdcall C_SetDataStringA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpDataName,
    int Index,
    LPCSTR lpData,
    int *lpStatus
);

void __stdcall C_SetDataStringW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpDataName,
    int Index,
    LPCWSTR lpData,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetDataString C_SetDataStringW
#else
#define C_SetDataString C_SetDataStringA
#endif

void __stdcall C_SetLineUserSpecifiedStartingShape(
    TOrcFxAPIHandle ObjectHandle,
    TVector *lpStartingShape,
    int *lpStatus
);

void __stdcall C_SetTagA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpName,
    LPCSTR lpValue,
    int *lpStatus
);

void __stdcall C_SetTagW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpName,
    LPCWSTR lpValue,
    int *lpStatus
);

#ifdef UNICODE
#define C_SetTag C_SetTagW
#else
#define C_SetTag C_SetTagA
#endif

/*=============== Functions: Drawing ===============*/

void __stdcall C_AVIFileAddBitmap(
    TOrcFxAPIHandle AVIFileHandle,
    HBITMAP Bitmap,
    int *lpStatus
);

void __stdcall C_AVIFileFinalise(
    TOrcFxAPIHandle AVIFileHandle,
    int *lpStatus
);

void __stdcall C_AVIFileInitialiseA(
    TOrcFxAPIHandle *lpAVIFileHandle,
    LPCSTR lpAVIFileName,
    const TAVIFileParameters *lpAVIFileParameters,
    int *lpStatus
);

void __stdcall C_AVIFileInitialiseW(
    TOrcFxAPIHandle *lpAVIFileHandle,
    LPCWSTR lpAVIFileName,
    const TAVIFileParameters *lpAVIFileParameters,
    int *lpStatus
);

#ifdef UNICODE
#define C_AVIFileInitialise C_AVIFileInitialiseW
#else
#define C_AVIFileInitialise C_AVIFileInitialiseA
#endif

void __stdcall C_CreateBitmapCanvas(
    int Width,
    int Height,
    TOrcFxAPIHandle *lpCanvasHandle,
    int *lpStatus
);

void __stdcall C_CreateModel3DViewBitmap(
    TOrcFxAPIHandle ModelHandle,
    const TViewParameters *lpViewParameters,
    HBITMAP *lpBitmap,
    int *lpStatus
);

void __stdcall C_DestroyBitmapCanvas(
    TOrcFxAPIHandle CanvasHandle,
    int *lpStatus
);

void __stdcall C_DrawModel3DViewToBitmapCanvas(
    TOrcFxAPIHandle CanvasHandle,
    TOrcFxAPIHandle ModelHandle,
    const TViewParameters *lpViewParameters,
    int *lpStatus
);

void __stdcall C_GetDefaultViewParameters(
    TOrcFxAPIHandle ModelHandle,
    TViewParameters *lpViewParameters,
    int *lpStatus
);

double __stdcall C_GetSimulationDrawTime(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_SaveBitmapCanvasMem(
    TOrcFxAPIHandle CanvasHandle,
    const TBitmapCanvasSaveFormat *lpSaveFormat,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveBitmapCanvasA(
    TOrcFxAPIHandle CanvasHandle,
    const TBitmapCanvasSaveFormat *lpSaveFormat,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveBitmapCanvasW(
    TOrcFxAPIHandle CanvasHandle,
    const TBitmapCanvasSaveFormat *lpSaveFormat,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveBitmapCanvas C_SaveBitmapCanvasW
#else
#define C_SaveBitmapCanvas C_SaveBitmapCanvasA
#endif

void __stdcall C_SaveModel3DViewBitmapMem(
    TOrcFxAPIHandle ModelHandle,
    const TViewParameters *lpViewParameters,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveModel3DViewBitmapToFileA(
    TOrcFxAPIHandle ModelHandle,
    const TViewParameters *lpViewParameters,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveModel3DViewBitmapToFileW(
    TOrcFxAPIHandle ModelHandle,
    const TViewParameters *lpViewParameters,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveModel3DViewBitmapToFile C_SaveModel3DViewBitmapToFileW
#else
#define C_SaveModel3DViewBitmapToFile C_SaveModel3DViewBitmapToFileA
#endif

void __stdcall C_SetSimulationDrawTime(
    TOrcFxAPIHandle ModelHandle,
    double SimulationDrawTime,
    int *lpStatus
);

/*=============== Functions: Calculation ===============*/

void __stdcall C_CalculateMooringStiffness(
    int VesselCount,
    const TOrcFxAPIHandle *lpVessels,
    double *lpStiffness,
    int *lpStatus
);

void __stdcall C_CalculateStaticsA(
    TOrcFxAPIHandle ModelHandle,
    TStaticsProgressHandlerProcA StaticsProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_CalculateStaticsW(
    TOrcFxAPIHandle ModelHandle,
    TStaticsProgressHandlerProcW StaticsProgressHandlerProc,
    int *lpStatus
);

#ifdef UNICODE
#define C_CalculateStatics C_CalculateStaticsW
#else
#define C_CalculateStatics C_CalculateStaticsA
#endif

void __stdcall C_CreateModes(
    TOrcFxAPIHandle ObjectHandle,
    const TModalAnalysisSpecification *lpSpecification,
    TOrcFxAPIHandle *lpModesHandle,
    int *lpDegreeOfFreedomCount,
    int *lpModeCount,
    int *lpStatus
);

void __stdcall C_DestroyModes(
    TOrcFxAPIHandle ModesHandle,
    int *lpStatus
);

void __stdcall C_ExtendSimulation(
    TOrcFxAPIHandle ModelHandle,
    double Time,
    int *lpStatus
);

void __stdcall C_GetDefaultSolveEquationParameters(
    TSolveEquationParameters *lpSolveEquationParameters,
    int *lpStatus
);

void __stdcall C_GetDefaultUseCalculatedPositionsForStaticsParameters(
    TUseCalculatedPositionsForStaticsParameters *lpUseCalculatedPositionsForStaticsParameters,
    int *lpStatus
);

void __stdcall C_GetModeDegreeOfFreedomDetails(
    TOrcFxAPIHandle ModesHandle,
    int *lpNodeNumbers,
    int *lpDOFs,
    int *lpStatus
);

void __stdcall C_GetModeDegreeOfFreedomOwners(
    TOrcFxAPIHandle ModesHandle,
    TOrcFxAPIHandle *lpOwners,
    int *lpStatus
);

void __stdcall C_GetModeDetails(
    TOrcFxAPIHandle ModesHandle,
    int Index,
    TModeDetails *lpDetails,
    int *lpStatus
);

void __stdcall C_GetModeLoad(
    TOrcFxAPIHandle ModesHandle,
    int Index,
    TModeLoad *lpLoad,
    int *lpStatus
    );

void __stdcall C_GetModeLoadOutputPoints(
    TOrcFxAPIHandle ModesHandle,
    int *lpOutputPointCount,
    TModeLoadOutputPoint *lpLoadOutputPoints,
    int *lpStatus
);

void __stdcall C_GetModelProperty(
    TOrcFxAPIHandle ObjectHandle,
    int PropertyId,
    void *lpValue,
    int *lpStatus
);

void __stdcall C_GetModelState(
    TOrcFxAPIHandle ModelHandle,
    int *lpModelState,
    int *lpStatus
);

void __stdcall C_GetModeSummary(
    TOrcFxAPIHandle ModesHandle,
    int *lpNumbers,
    double *lpPeriods,
    int *lpStatus
);

void __stdcall C_GetRecommendedTimeSteps(
    TOrcFxAPIHandle ModelHandle,
    TTimeSteps *lpTimeSteps,
    int *lpStatus
);

void __stdcall C_GetSimulationComplete(
    TOrcFxAPIHandle ModelHandle,
    BOOL *lpSimulationComplete,
    int *lpStatus
);

void __stdcall C_GetSimulationTimeStatus(
    TOrcFxAPIHandle ModelHandle,
    TSimulationTimeStatus *lpSimulationTimeStatus,
    int *lpStatus
);

double __stdcall C_GetSimulationTimeToGo(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_PauseSimulation(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_ProcessBatchScriptA(
    TOrcFxAPIHandle ModelHandle,
    LPCSTR lpBatchScriptFileName,
    TStringProgressHandlerProcA BatchScriptProgressHandlerProc,
    TStaticsProgressHandlerProcA StaticsProgressHandlerProc,
    TDynamicsProgressHandlerProc DynamicsProgressHandlerProc,
    const TRunSimulationParametersA *lpRunSimulationParameters,
    int *lpStatus
);

void __stdcall C_ProcessBatchScriptW(
    TOrcFxAPIHandle ModelHandle,
    LPCWSTR lpBatchScriptFileName,
    TStringProgressHandlerProcW BatchScriptProgressHandlerProc,
    TStaticsProgressHandlerProcW StaticsProgressHandlerProc,
    TDynamicsProgressHandlerProc DynamicsProgressHandlerProc,
    const TRunSimulationParametersW *lpRunSimulationParameters,
    int *lpStatus
);

#ifdef UNICODE
#define C_ProcessBatchScript C_ProcessBatchScriptW
#else
#define C_ProcessBatchScript C_ProcessBatchScriptA
#endif

void __stdcall C_ResetModel(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

void __stdcall C_RunSimulation(
    TOrcFxAPIHandle ModelHandle,
    TDynamicsProgressHandlerProc DynamicsProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_RunSimulation2A(
    TOrcFxAPIHandle ModelHandle,
    TDynamicsProgressHandlerProc DynamicsProgressHandlerProc,
    const TRunSimulationParametersA *lpRunSimulationParameters,
    int *lpStatus
);

void __stdcall C_RunSimulation2W(
    TOrcFxAPIHandle ModelHandle,
    TDynamicsProgressHandlerProc DynamicsProgressHandlerProc,
    const TRunSimulationParametersW *lpRunSimulationParameters,
    int *lpStatus
);

#ifdef UNICODE
#define C_RunSimulation2 C_RunSimulation2W
#else
#define C_RunSimulation2 C_RunSimulation2A
#endif

void __stdcall C_SolveEquation(
    INT_PTR Data,
    TSolveEquationCalcYProc SolveEquationCalcYProc,
    double *lpX,
    double TargetY,
    const TSolveEquationParameters *lpSolveEquationParameters,
    int *lpStatus
);

void __stdcall C_UseCalculatedPositionsForStatics(
    TOrcFxAPIHandle ModelHandle,
    const TUseCalculatedPositionsForStaticsParameters *lpUseCalculatedPositionsForStaticsParameters,
    int *lpStatus
);

void __stdcall C_UseStaticLineEndOrientations(
    TOrcFxAPIHandle ModelHandle,
    int *lpStatus
);

/*=============== Functions: Results ===============*/

void __stdcall C_AnalyseExtrema(
    double *lpValues,
    int Count,
    double *lpMaximum,
    double *lpMinimum,
    int *lpIndexOfMaximum,
    int *lpIndexOfMinimum,
    int *lpStatus
);

int __stdcall C_CalculateExtremeStatisticsExcessesOverThreshold(
    TOrcFxAPIHandle ExtremeStatisticsHandle,
    const TExtremeStatisticsSpecification *lpSpecification,
    double *lpExcesses,
    int *lpStatus
);

void __stdcall C_CalculateFatigueA(
    TOrcFxAPIHandle FatigueHandle,
    LPCSTR lpResultsFileName,
    TStringProgressHandlerProc FatigueProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_CalculateFatigueW(
    TOrcFxAPIHandle FatigueHandle,
    LPCWSTR lpResultsFileName,
    TStringProgressHandlerProc FatigueProgressHandlerProc,
    int *lpStatus
);

#ifdef UNICODE
#define C_CalculateFatigue C_CalculateFatigueW
#else
#define C_CalculateFatigue C_CalculateFatigueA
#endif

void __stdcall C_CalculateRratio(
    int CycleCount,
    const double *lpRange,
    const double *lpAssociatedMean,
    double *lpRratio,
    int *lpStatus
);

void __stdcall C_CalculateLinkedStatisticsTimeSeriesStatistics(
    TOrcFxAPIHandle StatisticsHandle,
    int VarID,
    TTimeSeriesStatistics *lpStatistics,
    int *lpStatus
);

void __stdcall C_CalculateTimeSeriesStatistics(
    double *lpValues,
    int Count,
    double SampleInterval,
    TTimeSeriesStatistics *lpStatistics,
    int *lpStatus
);

void __stdcall C_CloseExtremeStatistics(
    TOrcFxAPIHandle ExtremeStatisticsHandle,
    int *lpStatus
);

void __stdcall C_CloseLinkedStatistics(
    TOrcFxAPIHandle StatisticsHandle,
    int *lpStatus
);

void __stdcall C_CreateCollatedResultsAdmin(
    TOrcFxAPIHandle ModelHandle,
    int RestartModelCount,
    int *lpRestartModels,
    const TPeriod *lpPeriod,
    TOrcFxAPIHandle *lpCollatedResultsHandle,
    int *lpStatus
);

void __stdcall C_CreateCycleHistogramBins(
    int HalfCycleCount,
    double *lpHalfCycleRanges,
    double BinSize,
    int *lpBinCount,
    TCycleBin **lpBins,
    int *lpStatus
);

void __stdcall C_CreateFatigue(
    TOrcFxAPIHandle *lpFatigueHandle,
    int *lpStatus
);

void __stdcall C_CreateTimeHistorySummary(
    int TimeHistorySummaryType,
    int NumOfSamples,
    double *lpTimes,
    double *lpValues,
    TOrcFxAPIHandle *lpTimeHistorySummaryHandle,
    int *lpNumOfSummaryValues,
    int *lpStatus
);

void __stdcall C_CreateTimeHistorySummary2(
    int TimeHistorySummaryType,
    int NumOfSamples,
    const TTimeHistorySummarySpecification *lpSpecification,
    double *lpTimes,
    double *lpValues,
    TOrcFxAPIHandle *lpTimeHistorySummaryHandle,
    int *lpNumOfSummaryValues,
    int *lpStatus
);

void __stdcall C_CreateWaveScatter(
    TOrcFxAPIHandle *lpWaveScatterHandle,
    int *lpStatus
);

void __stdcall C_DestroyCollatedResultsAdmin(
    TOrcFxAPIHandle CollatedResultsHandle,
    int *lpStatus
);

void __stdcall C_DestroyCycleHistogramBins(
    TCycleBin *lpBins,
    int *lpStatus
);

void __stdcall C_DestroyFatigue(
    TOrcFxAPIHandle FatigueHandle,
    int *lpStatus
);

void __stdcall C_DestroyTimeHistorySummary(
    TOrcFxAPIHandle TimeHistorySummaryHandle,
    int *lpStatus
);

void __stdcall C_DestroyWaveScatter(
    TOrcFxAPIHandle WaveScatterHandle,
    int *lpStatus
);

void __stdcall C_EnumerateVarsA(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra *lpObjectExtra,
    int ResultType,
    TEnumerateVarsProcA EnumerateVarsProc,
    int *lpNumberOfVars,
    int *lpStatus
);

void __stdcall C_EnumerateVarsW(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra *lpObjectExtra,
    int ResultType,
    TEnumerateVarsProcW EnumerateVarsProc,
    int *lpNumberOfVars,
    int *lpStatus
);

#ifdef UNICODE
#define C_EnumerateVars C_EnumerateVarsW
#else
#define C_EnumerateVars C_EnumerateVarsA
#endif

void __stdcall C_EnumerateVars2A(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int ResultType,
    TEnumerateVarsProcA EnumerateVarsProc,
    int *lpNumberOfVars,
    int *lpStatus
);

void __stdcall C_EnumerateVars2W(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int ResultType,
    TEnumerateVarsProcW EnumerateVarsProc,
    int *lpNumberOfVars,
    int *lpStatus
);

#ifdef UNICODE
#define C_EnumerateVars2 C_EnumerateVars2W
#else
#define C_EnumerateVars2 C_EnumerateVars2A
#endif

void __stdcall C_FitExtremeStatistics(
    TOrcFxAPIHandle ExtremeStatisticsHandle,
    const TExtremeStatisticsSpecification *lpSpecification,
    int *lpStatus
);

void __stdcall C_GetFatigueOutput(
    TOrcFxAPIHandle FatigueAnalysisHandle,
    int OutputType,
    int *lpOutputSize,
    void *lpOutput,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainMPM(
    const double StormDuration,
    const double StdDev,
    const double Tz,
    double *lpValue,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainProcessComponents(
    TOrcFxAPIHandle ModelHandle,
    int *lpCount,
    TFrequencyDomainProcessComponent *lpFrequencyDomainProcessComponents,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainProcessComponents2(
    TOrcFxAPIHandle ModelHandle,
    int *lpCount,
    TFrequencyDomainProcessComponent2 *lpFrequencyDomainProcessComponents,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainResultsA(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    TFrequencyDomainResults *lpValue,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainResultsW(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    TFrequencyDomainResults *lpValue,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetFrequencyDomainResults C_GetFrequencyDomainResultsW
#else
#define C_GetFrequencyDomainResults C_GetFrequencyDomainResultsA
#endif

void __stdcall C_GetFrequencyDomainResultsProcessA(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    int *lpComponentCount,
    TComplex *lpProcess,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainResultsProcessW(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    int *lpComponentCount,
    TComplex *lpProcess,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetFrequencyDomainResultsProcess C_GetFrequencyDomainResultsProcessW
#else
#define C_GetFrequencyDomainResultsProcess C_GetFrequencyDomainResultsProcessA
#endif

void __stdcall C_GetFrequencyDomainSpectralDensityGraphA(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    int *lpNumOfGraphPoints,
    TGraphCurve *lpGraph,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainSpectralDensityGraphW(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    int *lpNumOfGraphPoints,
    TGraphCurve *lpGraph,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetFrequencyDomainSpectralDensityGraph C_GetFrequencyDomainSpectralDensityGraphW
#else
#define C_GetFrequencyDomainSpectralDensityGraph C_GetFrequencyDomainSpectralDensityGraphA
#endif

void __stdcall C_GetFrequencyDomainResultsFromProcess(
    TOrcFxAPIHandle ModelHandle,
    int ComponentCount,
    const TComplex *lpProcess,
    TFrequencyDomainResults *lpValue,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainSpectralDensityGraphFromProcess(
    TOrcFxAPIHandle ModelHandle,
    int ComponentCount,
    const TComplex *lpProcess,
    int *lpNumOfGraphPoints,
    TGraphCurve *lpGraph,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainSpectralResponseGraphFromProcess(
    TOrcFxAPIHandle ModelHandle,
    int ComponentCount,
    const TComplex *lpProcess,
    int *lpNumOfGraphPoints,
    TGraphCurve *lpGraph,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainTimeHistoryFromProcess(
    TOrcFxAPIHandle ModelHandle,
    int ComponentCount,
    const TComplex *lpProcess,
    double FromTime,
    double SampleInterval,
    int SampleCount,
    double *lpValues,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainTimeHistorySampleCount(
    double FromTime,
    double ToTime,
    double SampleInterval,
    int *lpSampleCount,
    int *lpStatus
);

void __stdcall C_GetFrequencyDomainTimeHistorySampleTimes(
    double FromTime,
    double SampleInterval,
    int SampleCount,
    double *lpTimes,
    int *lpStatus
);

void __stdcall C_GetLineResultPoints(
    TOrcFxAPIHandle ObjectHandle,
    int VarID,
    int *lpLineResultPoints,
    int *lpStatus
);

void __stdcall C_GetMultipleTimeHistoriesA(
    int Count,
    const TTimeHistorySpecificationA *lpSpecification,
    const TPeriod *lpPeriod,
    double *lpValues,
    int *lpStatus
);

void __stdcall C_GetMultipleTimeHistoriesW(
    int Count,
    const TTimeHistorySpecificationW *lpSpecification,
    const TPeriod *lpPeriod,
    double *lpValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetMultipleTimeHistories C_GetMultipleTimeHistoriesW
#else
#define C_GetMultipleTimeHistories C_GetMultipleTimeHistoriesA
#endif

void __stdcall C_GetMultipleTimeHistoriesCollatedA(
    TOrcFxAPIHandle CollatedResultsHandle,
    int Count,
    const TTimeHistorySpecificationA *lpSpecification,
    double *lpValues,
    int *lpStatus
);

void __stdcall C_GetMultipleTimeHistoriesCollatedW(
    TOrcFxAPIHandle CollatedResultsHandle,
    int Count,
    const TTimeHistorySpecificationW *lpSpecification,
    double *lpValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetMultipleTimeHistoriesCollated C_GetMultipleTimeHistoriesCollatedW
#else
#define C_GetMultipleTimeHistoriesCollated C_GetMultipleTimeHistoriesCollatedA
#endif

int __stdcall C_GetNumOfSamples(
    TOrcFxAPIHandle ModelHandle,
    const TPeriod *lpPeriod,
    int *lpStatus
);

int __stdcall C_GetNumOfSamplesCollated(
    TOrcFxAPIHandle CollatedResultsHandle,
    int *lpStatus
);

void __stdcall C_GetObjectExtraFieldRequired(
    TOrcFxAPIHandle ObjectHandle,
    int VarID,
    int Field,
    BOOL *lpRequired,
    int *lpStatus
);

void __stdcall C_GetRangeGraph(
    TOrcFxAPIHandle ObjectHandle,
    int VarID,
    const TPeriod *lpPeriod,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

void __stdcall C_GetRangeGraph2(
    TOrcFxAPIHandle ObjectHandle,
    int VarID,
    const TPeriod *lpPeriod,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

void __stdcall C_GetRangeGraph3A(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

void __stdcall C_GetRangeGraph3W(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRangeGraph3 C_GetRangeGraph3W
#else
#define C_GetRangeGraph3 C_GetRangeGraph3A
#endif

void __stdcall C_GetRangeGraph4A(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    const TPeriod *lpPeriod,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

void __stdcall C_GetRangeGraph4W(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    const TPeriod *lpPeriod,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRangeGraph4 C_GetRangeGraph4W
#else
#define C_GetRangeGraph4 C_GetRangeGraph4A
#endif

void __stdcall C_GetRangeGraphCollatedA(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

void __stdcall C_GetRangeGraphCollatedW(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    double *lpXValues,
    double *lpMinValues,
    double *lpMaxValues,
    double *lpMeanValues,
    double *lpStdDevValues,
    double *lpUpperValues,
    double *lpLowerValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRangeGraphCollated C_GetRangeGraphCollatedW
#else
#define C_GetRangeGraphCollated C_GetRangeGraphCollatedA
#endif

void __stdcall C_GetRangeGraphCurveNamesA(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    TRangeGraphCurveNamesA *lpCurveNames,
    int *lpStatus
);

void __stdcall C_GetRangeGraphCurveNamesW(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    TRangeGraphCurveNamesW *lpCurveNames,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRangeGraphCurveNames C_GetRangeGraphCurveNamesW
#else
#define C_GetRangeGraphCurveNames C_GetRangeGraphCurveNamesA
#endif

void __stdcall C_GetRangeGraphCurveNamesCollatedA(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    TRangeGraphCurveNamesA *lpCurveNames,
    int *lpStatus
);

void __stdcall C_GetRangeGraphCurveNamesCollatedW(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    TRangeGraphCurveNamesW *lpCurveNames,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetRangeGraphCurveNamesCollated C_GetRangeGraphCurveNamesCollatedW
#else
#define C_GetRangeGraphCurveNamesCollated C_GetRangeGraphCurveNamesCollatedA
#endif

int __stdcall C_GetRangeGraphNumOfPoints(
    TOrcFxAPIHandle ObjectHandle,
    int VarID,
    int *lpStatus
);

int __stdcall C_GetRangeGraphNumOfPoints2(
    TOrcFxAPIHandle ObjectHandle,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    int *lpStatus
);

int __stdcall C_GetRangeGraphNumOfPoints3(
    TOrcFxAPIHandle ObjectHandle,
    const TPeriod *lpPeriod,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    int *lpStatus
);

int __stdcall C_GetRangeGraphNumOfPointsCollated(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TArclengthRange *lpArclengthRange,
    int VarID,
    int *lpStatus
);

void __stdcall C_GetRequiredObjectExtraFields(
    TOrcFxAPIHandle ObjectHandle,
    int VarID,
    int *lpFields,
    int *lpStatus
);

void __stdcall C_GetSampleTimes(
    TOrcFxAPIHandle ModelHandle,
    const TPeriod *lpPeriod,
    double *lpTimes,
    int *lpStatus
);

void __stdcall C_GetSampleTimesCollated(
    TOrcFxAPIHandle CollatedResultsHandle,
    double *lpTimes,
    int *lpStatus
);

void __stdcall C_GetSpectralResponseGraphA(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    int *lpNumOfGraphPoints,
    TGraphCurve *lpGraph,
    int *lpStatus
);

void __stdcall C_GetSpectralResponseGraphW(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    int *lpNumOfGraphPoints,
    TGraphCurve *lpGraph,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetSpectralResponseGraph C_GetSpectralResponseGraphW
#else
#define C_GetSpectralResponseGraph C_GetSpectralResponseGraphA
#endif

void __stdcall C_GetStaticResult(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra *lpObjectExtra,
    int VarID,
    double *lpValue,
    int *lpStatus
);

void __stdcall C_GetStaticResult2A(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    double *lpValue,
    int *lpStatus
);

void __stdcall C_GetStaticResult2W(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    double *lpValue,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetStaticResult2 C_GetStaticResult2W
#else
#define C_GetStaticResult2 C_GetStaticResult2A
#endif

void __stdcall C_GetTimeHistory(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    double *lpValues,
    int *lpStatus
);

void __stdcall C_GetTimeHistory2A(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    double *lpValues,
    int *lpStatus
);

void __stdcall C_GetTimeHistory2W(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    const TPeriod *lpPeriod,
    int VarID,
    double *lpValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetTimeHistory2 C_GetTimeHistory2W
#else
#define C_GetTimeHistory2 C_GetTimeHistory2A
#endif

void __stdcall C_GetTimeHistoryCollatedA(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    int VarID,
    double *lpValues,
    int *lpStatus
);

void __stdcall C_GetTimeHistoryCollatedW(
    TOrcFxAPIHandle CollatedResultsHandle,
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    int VarID,
    double *lpValues,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetTimeHistoryCollated C_GetTimeHistoryCollatedW
#else
#define C_GetTimeHistoryCollated C_GetTimeHistoryCollatedA
#endif

void __stdcall C_GetTimeHistorySummaryValues(
    TOrcFxAPIHandle TimeHistorySummaryHandle,
    double *lpX,
    double *lpY,
    int *lpStatus
);

void __stdcall C_GetVarIDA(
    TOrcFxAPIHandle ObjectHandle,
    LPCSTR lpVarName,
    int *lpVarID,
    int *lpStatus
);

void __stdcall C_GetVarIDW(
    TOrcFxAPIHandle ObjectHandle,
    LPCWSTR lpVarName,
    int *lpVarID,
    int *lpStatus
);

#ifdef UNICODE
#define C_GetVarID C_GetVarIDW
#else
#define C_GetVarID C_GetVarIDA
#endif

void __stdcall C_GetWaveComponents(
    TOrcFxAPIHandle ModelHandle,
    int *lpCount,
    TWaveComponent *lpWaveComponents,
    int *lpStatus
);

void __stdcall C_GetWaveComponents2(
    TOrcFxAPIHandle ModelHandle,
    int *lpCount,
    TWaveComponent2 *lpWaveComponents,
    int *lpStatus
);

void __stdcall C_GetWaveScatterTable(
    TOrcFxAPIHandle WaveScatterHandle,
    TWaveScatterBin *lpTbins,
    TWaveScatterBin *lpHbins,
    double *lpOccurrences,
    double *lpTotalProbability,
    int *lpStatus
);

void __stdcall C_GetWindComponents(
    TOrcFxAPIHandle ModelHandle,
    int *lpCount,
    TWindComponent *lpWindComponents,
    int *lpStatus
);

void __stdcall C_LoadFatigueA(
    TOrcFxAPIHandle FatigueHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_LoadFatigueW(
    TOrcFxAPIHandle FatigueHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_LoadFatigue C_LoadFatigueW
#else
#define C_LoadFatigue C_LoadFatigueA
#endif

void __stdcall C_LoadFatigueMem(
    TOrcFxAPIHandle FatigueHandle,
    int DataFileType,
    const unsigned char *lpBuffer,
    int64_t BufferLen,
    int *lpStatus
);

void __stdcall C_LoadWaveScatterA(
    TOrcFxAPIHandle WaveScatterHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_LoadWaveScatterW(
    TOrcFxAPIHandle WaveScatterHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_LoadWaveScatter C_LoadWaveScatterW
#else
#define C_LoadWaveScatter C_LoadWaveScatterA
#endif

void __stdcall C_LoadWaveScatterMem(
    TOrcFxAPIHandle WaveScatterHandle,
    int DataFileType,
    const unsigned char *lpBuffer,
    int64_t BufferLen,
    int *lpStatus
);

void __stdcall C_OpenExtremeStatistics(
    int NumberOfValues,
    double *lpValues,
    double SampleInterval,
    TOrcFxAPIHandle *lpExtremeStatisticsHandle,
    int *lpStatus
);

void __stdcall C_OpenLinkedStatistics(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra *lpObjectExtra,
    const TPeriod *lpPeriod,
    int NumOfVars,
    int *lpVars,
    TOrcFxAPIHandle *lpStatisticsHandle,
    int *lpStatus
);

void __stdcall C_OpenLinkedStatistics2A(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2A *lpObjectExtra,
    const TPeriod *lpPeriod,
    int NumOfVars,
    int *lpVars,
    TOrcFxAPIHandle *lpStatisticsHandle,
    int *lpStatus
);

void __stdcall C_OpenLinkedStatistics2W(
    TOrcFxAPIHandle ObjectHandle,
    const TObjectExtra2W *lpObjectExtra,
    const TPeriod *lpPeriod,
    int NumOfVars,
    int *lpVars,
    TOrcFxAPIHandle *lpStatisticsHandle,
    int *lpStatus
);

#ifdef UNICODE
#define C_OpenLinkedStatistics2 C_OpenLinkedStatistics2W
#else
#define C_OpenLinkedStatistics2 C_OpenLinkedStatistics2A
#endif

void __stdcall C_QueryExtremeStatistics(
    TOrcFxAPIHandle ExtremeStatisticsHandle,
    const TExtremeStatisticsQuery *lpQuery,
    TExtremeStatisticsOutput *lpOutput,
    int *lpStatus
);

void __stdcall C_QueryLinkedStatistics(
    TOrcFxAPIHandle StatisticsHandle,
    int VarID,
    int LinkedVarID,
    TStatisticsQuery *lpStatisticsQuery,
    int *lpStatus
);

void __stdcall C_RegisterExternalFunctionResultA(
    TExtFnInfoA *lpExtFnInfo,
    TExtFnResultInfoA *lpResultInfo,
    int *lpStatus
);

void __stdcall C_RegisterExternalFunctionResultW(
    TExtFnInfoW *lpExtFnInfo,
    TExtFnResultInfoW *lpResultInfo,
    int *lpStatus
);

#ifdef UNICODE
#define C_RegisterExternalFunctionResult C_RegisterExternalFunctionResultW
#else
#define C_RegisterExternalFunctionResult C_RegisterExternalFunctionResultA
#endif

void __stdcall C_SaveFatigueA(
    TOrcFxAPIHandle FatigueHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveFatigueW(
    TOrcFxAPIHandle FatigueHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveFatigue C_SaveFatigueW
#else
#define C_SaveFatigue C_SaveFatigueA
#endif

void __stdcall C_SaveFatigueMem(
    TOrcFxAPIHandle FatigueHandle,
    int DataFileType,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveWaveScatterA(
    TOrcFxAPIHandle WaveScatterHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveWaveScatterW(
    TOrcFxAPIHandle WaveScatterHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveWaveScatter C_SaveWaveScatterW
#else
#define C_SaveWaveScatter C_SaveWaveScatterA
#endif

void __stdcall C_SaveWaveScatterMem(
    TOrcFxAPIHandle WaveScatterHandle,
    int DataFileType,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveWaveScatterAutomationFilesA(
    TOrcFxAPIHandle WaveScatterHandle,
    const TWaveScatterAutomationSpecificationA *lpSpecification,
    int *lpStatus
);

void __stdcall C_SaveWaveScatterAutomationFilesW(
    TOrcFxAPIHandle WaveScatterHandle,
    const TWaveScatterAutomationSpecificationW *lpSpecification,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveWaveScatterAutomationFiles C_SaveWaveScatterAutomationFilesW
#else
#define C_SaveWaveScatterAutomationFiles C_SaveWaveScatterAutomationFilesA
#endif

void __stdcall C_SimulateToleranceIntervals(
    TOrcFxAPIHandle ExtremeStatisticsHandle,
    int SimulatedDataSetCount,
    TInterval *lpToleranceIntervals,
    int *lpStatus
);

/*=============== Functions: Diffraction ===============*/

void __stdcall C_CalculateDiffractionA(
    TOrcFxAPIHandle DiffractionHandle,
    TStringProgressHandlerProcA DiffractionProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_CalculateDiffractionW(
    TOrcFxAPIHandle DiffractionHandle,
    TStringProgressHandlerProcW DiffractionProgressHandlerProc,
    int *lpStatus
);

#ifdef UNICODE
#define C_CalculateDiffraction C_CalculateDiffractionW
#else
#define C_CalculateDiffraction C_CalculateDiffractionA
#endif

void __stdcall C_ClearDiffraction(
    TOrcFxAPIHandle DiffractionHandle,
    int *lpStatus
);

void __stdcall C_CreateDiffraction(
    TOrcFxAPIHandle *lpDiffractionHandle,
    int *lpStatus
);

void __stdcall C_DestroyDiffraction(
    TOrcFxAPIHandle DiffractionHandle,
    int *lpStatus
);

void __stdcall C_GetDiffractionOutput(
    TOrcFxAPIHandle DiffractionHandle,
    int OutputType,
    int *lpOutputSize,
    void *lpOutput,
    int *lpStatus
);

void __stdcall C_GetDiffractionState(
    TOrcFxAPIHandle DiffractionHandle,
    int *lpDiffractionState,
    int *lpStatus
);

void __stdcall C_GetDiffractionWaveComponents(
    TOrcFxAPIHandle DiffractionHandle,
    int *lpCount,
    TDiffractionWaveComponent *lpWaveComponents,
    int *lpStatus
);

void __stdcall C_LoadDiffractionDataA(
    TOrcFxAPIHandle DiffractionHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_LoadDiffractionDataW(
    TOrcFxAPIHandle DiffractionHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_LoadDiffractionData C_LoadDiffractionDataW
#else
#define C_LoadDiffractionData C_LoadDiffractionDataA
#endif

void __stdcall C_LoadDiffractionDataMem(
    TOrcFxAPIHandle DiffractionHandle,
    int DataFileType,
    const unsigned char *lpBuffer,
    int64_t BufferLen,
    int *lpStatus
);

void __stdcall C_LoadDiffractionResultsA(
    TOrcFxAPIHandle DiffractionHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_LoadDiffractionResultsW(
    TOrcFxAPIHandle DiffractionHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_LoadDiffractionResults C_LoadDiffractionResultsW
#else
#define C_LoadDiffractionResults C_LoadDiffractionResultsA
#endif

void __stdcall C_LoadDiffractionResultsMem(
    TOrcFxAPIHandle DiffractionHandle,
    const unsigned char *lpBuffer,
    int64_t BufferLen,
    int *lpStatus
);

void __stdcall C_NewDiffractionA(
    TOrcFxAPIHandle DiffractionHandle,
    const TNewModelParamsA *lpParams,
    int *lpStatus
);

void __stdcall C_NewDiffractionW(
    TOrcFxAPIHandle DiffractionHandle,
    const TNewModelParamsW *lpParams,
    int *lpStatus
);

#ifdef UNICODE
#define C_NewDiffraction C_NewDiffractionW
#else
#define C_NewDiffraction C_NewDiffractionA
#endif

void __stdcall C_ResetDiffraction(
    TOrcFxAPIHandle DiffractionHandle,
    int *lpStatus
);

void __stdcall C_SaveDiffractionDataA(
    TOrcFxAPIHandle DiffractionHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveDiffractionDataW(
    TOrcFxAPIHandle DiffractionHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveDiffractionData C_SaveDiffractionDataW
#else
#define C_SaveDiffractionData C_SaveDiffractionDataA
#endif

void __stdcall C_SaveDiffractionDataMem(
    TOrcFxAPIHandle DiffractionHandle,
    int DataFileType,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SaveDiffractionMeshA(
    TOrcFxAPIHandle DiffractionHandle,
    int ExportedMeshType,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveDiffractionMeshW(
    TOrcFxAPIHandle DiffractionHandle,
    int ExportedMeshType,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveDiffractionMesh C_SaveDiffractionMeshW
#else
#define C_SaveDiffractionMesh C_SaveDiffractionMeshA
#endif

void __stdcall C_SaveDiffractionResultsA(
    TOrcFxAPIHandle DiffractionHandle,
    LPCSTR lpFileName,
    int *lpStatus
);

void __stdcall C_SaveDiffractionResultsW(
    TOrcFxAPIHandle DiffractionHandle,
    LPCWSTR lpFileName,
    int *lpStatus
);

#ifdef UNICODE
#define C_SaveDiffractionResults C_SaveDiffractionResultsW
#else
#define C_SaveDiffractionResults C_SaveDiffractionResultsA
#endif

void __stdcall C_SaveDiffractionResultsMem(
    TOrcFxAPIHandle DiffractionHandle,
    TOrcFxAPIHandle *lpBufferHandle,
    int64_t *lpBufferLen,
    int *lpStatus
);

void __stdcall C_SetDiffractionProgressHandler(
    TOrcFxAPIHandle DiffractionHandle,
    TProgressHandlerProc ProgressHandlerProc,
    int *lpStatus
);

void __stdcall C_TranslateDiffractionOutput(
    TOrcFxAPIHandle DiffractionHandle,
    int OutputType,
    int OutputSize,
    void *lpOutput,
    const TVector *lpReportingOrigins,
    int *lpStatus
);

// this is only implemented in OrcFxAPIExplicitLink.c; attempting to call this function
// when using load-time linking will lead to unresolved symbol linker errors
void __stdcall InitializeOrcFxAPI(
    HMODULE Module
);

#ifdef __cplusplus
}
}
#endif  /* __cplusplus */

#pragma pack(pop)

#endif /* !_orcfxapi_ */


