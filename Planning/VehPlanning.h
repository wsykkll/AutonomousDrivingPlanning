#pragma once
#include "qobject.h"
#include "PerceptionLines.h"
#include "PerceptionObstacles.h"
#include "NavigationPathPlanner.h"
#include "RTKInfo.h"
#include "VehicleInfo.h"
#include "VehControl.h"
#include "SceneSpeedPlanner.h"

#define OVERTAKINGINTENT_THRESHOLD 5
#define LANECHANGEABLE_THRESHOLD 5

#define MIN_GLOBALLOCALPATH_LENGTH 10
#define MIN_PREVIEWDISTANCE 4
#define BASE_PREVIEWDISTANCE 10
#define MAX_PREVIEWDISTANCE 50
#define NVIGATIONSPACE 1
#define NAVANGLEDIS 10
#define LINESHAPELENGTH 50
#define LINENAVGATIONLENGTH 80

#define MAX_STEERINGANGLE 540

#define ROUTE_PATH "../data/RNDF/route.txt"
#define WAYPOINT_PATH "../data/RNDF/waypoint.txt"
#define CONTROLTDATA_PATH "../data/RNDF/control.txt"
#define RECORDROUTE_PATH "../data/RNDF/recordRoute.txt"
#define RECORDPATH_PATH "../data/RNDF/recordPath.txt"
#define RECORDTRACKPATH_PATH "../data/RNDF/recordTrackPath.txt"
#define TRACKPATHIMAGE_PATH "../data/RNDF/trackPath.png"
#define LANECHANGEIMAGE_PATH "../data/RNDF/laneChange.png"

#define MAX_SPEED 120
#define DEACC_FOR_INTERSECTION 3
#define REACTION_TIME_INTERSECTION 1.5

// behavior plan
const int kLaneSafeNumberThreshold = 3;
const float kObstacleSafeValueThreshold = 1.0;

const float kDefaultTotalFrameNumber = 25;
const float kDefaultLeftLaneBetterFrameThreshold = 0.9;
const float kDefaultRightLaneBetterFrameThreshold = 0.9;
const float kDefaultMiddleFrameWorseThreshold = 0.9;

const float kDefaultFrontVelocityLowerThreshlod = 0.8;
const float kDefaultSelfVelocityLowerThreshold = 0.8;
const float kMinVelocityGapThreshold = 5.0 * MS_KMH;
const float kTargetLaneVelocityThreshold = kMinVelocityGapThreshold * (1 - kDefaultSelfVelocityLowerThreshold);

const int kJudgingTime = 5;//Decision time 5seconds
const float kPlanCycleTime = 0.1;
const int kLaneChangeTime = 5;

const int kDefaultBackMinTHW = 1;
const int kDefaultFrontMinTHW = 2;
const int kDefaultBackMinVehicleDistance = 6;
const int kDefaultFrontMinVehicleDistance = 10;
const int kDefaultOverTakingLimitTime = 3;
const int kDefaultHalfOverTakingKeepFrameThreshold = 100;


const float kDefaultTransmissionRatio = 16;
const float kDefaultVehicleWidth = 2.25;
const float kDefaultVehicleAxleDistance = 4.0;

const float kDefaultTimeGap = 9999;

enum BehaviorStatus
{
	KEEP_LANE,
	CHANGE_LEFT,
	CHANGE_RIGHT,
	OVER_LEFT,
	OVER_RIGHT,
	HALF_OVER_LEFT,
	HALF_OVER_RIGHT,
	STOP_IN_DISTANCE
};

enum SocialBehavior
{
	NORMAL,
	INTERSECTION_WITH_TRAFFIC_LIGHT,
	INTERSECTION_WITHOUT_TRAFFIC_LIGHT,
	FINISH_TASK
};

enum OperateStatus
{
	AUTOMATIC,
	SEMI_AUTOMATIC,
	MANUAL
};

struct VehicleDevice
{
	int8_t iLeftTurnLight;
	int8_t iRightTurnLight;
	int8_t iWiper;

	VehicleDevice()
	{
		iLeftTurnLight = 0;
		iRightTurnLight = 0;
		iWiper = 0;
	}
};

// the data from UI
struct GUIData
{
	OperateStatus enOperateStatus;
	BehaviorStatus enBehaviorStatus;
	bool bSaveRouteStateChanged;
	bool bSaveRouteStateChecked;
	bool bSaveDataStateChanged;
	bool bSaveDataStateChecked;
	bool bGPSNavigationChanged;
	bool bGPSNavigationChecked;
	bool bResetSemiAutoBehaviorStatus;
	int iSpeed;
	GUIData()
	{
		enOperateStatus = MANUAL;
		enBehaviorStatus = KEEP_LANE;
		bSaveRouteStateChanged = false;
		bSaveRouteStateChecked = false;
		bSaveDataStateChanged = false;
		bSaveDataStateChecked = false;
		bGPSNavigationChanged = false;
		bGPSNavigationChecked = false;
		bResetSemiAutoBehaviorStatus = false;
		iSpeed = 5;
	}
};


struct VehStatusData
{
	float fRealSpeed;
	float fGUISpeed;
	BehaviorStatus enCurrentBehavior;
	BehaviorStatus enLastBehavior;
	BehaviorStatus enNextBehavior;
	SocialBehavior enSocialBehavior;
	OperateStatus enOperateStatus;
	VehicleDevice stVehDevData;

	VehStatusData()
	{
		fRealSpeed = 0.0f;
		fGUISpeed = 0.0f;
		enCurrentBehavior = KEEP_LANE;
		enLastBehavior = KEEP_LANE;
		enNextBehavior = KEEP_LANE;
		enSocialBehavior = NORMAL;
		enOperateStatus = MANUAL;
	}
};

struct BehaviorPlanData
{
	bool bLeftlaneSafe;
	bool bLeftlaneBetter;
	bool bRightlaneSafe;
	bool bRightlaneBetter;
	bool bOvertakeIntention;

	int16_t iHostlaneCalTimes;
	int16_t iLeftlaneSafeCalTimes;
	int16_t iLeftlaneBetterCalTimes;
	int16_t iRightlaneSafeCalTimes;
	int16_t iRightlaneBetterCalTimes;

	int16_t iHostlaneWorseNum;
	int16_t iLeftlaneSafeNum;
	int16_t iLeftlaneBetterNum;
	int16_t iRightlaneSafeNum;
	int16_t iRightlaneBetterNum;

	int16_t iHalfOvertakeNum;
	BehaviorPlanData()
	{
		bLeftlaneSafe = false;
		bLeftlaneBetter = false;
		bRightlaneSafe = false;
		bRightlaneBetter = false;
		bOvertakeIntention = false;

		iHostlaneCalTimes = 0;
		iLeftlaneSafeCalTimes = 0;
		iLeftlaneBetterCalTimes = 0;
		iRightlaneSafeCalTimes = 0;
		iRightlaneBetterCalTimes = 0;

		iHostlaneWorseNum = 0;
		iLeftlaneSafeNum = 0;
		iLeftlaneBetterNum = 0;
		iRightlaneSafeNum = 0;
		iRightlaneBetterNum = 0;

		iHalfOvertakeNum = 0;
	}
};

struct NavigationData
{
	bool bPath;
	bool bHistoryRoute;
	bool bAdjustGPS;
	bool bKeepHistoryRoute;
	bool bKeepHistoryLane;
	bool bOverLeft;
	bool bOverRight;
	int iWaypointNum;
	int iRouteStartNum;
	int iRouteEndNum;
	float fSpeed;
	float fStopDis;
	int iPreviewDis;
	float fLimitSpeed;
	PointGps stVehPose;

	NavigationData()
	{
		bPath = false;
		bHistoryRoute = false;
		bAdjustGPS = true;
		bKeepHistoryRoute = false;
		bKeepHistoryLane = false;
		bOverLeft = true;
		bOverRight = true;
		iWaypointNum = -1;
		iRouteStartNum = -1;
		iRouteEndNum = -1;
		fSpeed = 0.0f;
		fStopDis = 0.0f;
		iPreviewDis = 5;
		fLimitSpeed = 0.0f;
	}
};

struct SteerControlFactor
{
	int iPredictNum;
	float fAngle;
	float fAngleFactor;
	float fMaxDeltaAngle;
	float fMaxAngle;
	SteerControlFactor()
	{
		iPredictNum = 8;
		fAngle = 0.0f;
		fAngleFactor = 0.0f;
		fMaxDeltaAngle = 0.0f;
		fMaxAngle = 0.0f;
	}
};

//the data display in UI
struct DisplayData
{
	RTKData DisplayRTKInfo;
	LineData DisplayLine;
	ObstacleData DisplayObs;
	VehicleInfoData DisplayVehInfo;

	GUIData DisplayGUI;
	OperateStatus DisplayOperationStatus;
	BehaviorStatus DisplayBehaviorStatus;
	VehicleDevice DisplayVehDevice;

	NavigationData DisplayNavigation;
	BehaviorPlanData DisplayBehaviorData;

	DesignSpeed DisplayDesignSpeed;
	DesignSteer DisplayDesignSteer;
	SteerControlFactor DisplaySteerCtrlFactor;

	vector<PointXY> DisplayVehTrajectory;
};


extern GUIData gGUIData;
extern shared_mutex gGUIMutex;

class CVehPlanning :
	public QObject
{
	Q_OBJECT
public:
	explicit CVehPlanning(QObject* parent = 0);
	~CVehPlanning();

	void Init();
	void SetThreadState(bool state);

	lcm::LCM* m_pLCM;
	bool InitilizeLCM();

	void PlanningThreadRun();
	void UpdateSourceData();
	void UpdateGUIData();
	void UpdatePerceptionData();
	void UpdateControlData();
	void UpdateDisplayData();

signals:
	void DisplayVehData(DisplayData);
	void DisplayNaviPath(vector<PointXY>);
	void DisplayLocalPath(vector<PointXY>);
	void DisplayGlobalLocalPath(vector<PointXY>);
	void DisplayGlobalPath(vector<PointXY>);
	void DisplayGlobalCurrentPath(PointXY);

private:
	bool m_bThreadRun;
	//Vehicle Status Data
	VehStatusData m_stVehStatusData;
	PointGps m_stRecordLastPoint;
	PointGps m_stRecordCurrentPoint;

	//GUI Data
	GUIData m_stGUIData;//the information from UI
	ofstream m_fileOutRecordRoute;
	ofstream m_fileOutRecordData;
	ofstream m_fileOutRecordTrackPath;

	//Perception Info Data
	RTKData m_stRTKInfoData;
	VehicleInfoData m_stVehInfoData;//from vehicle OBD
	LineData m_stPerceptionLineData;
	LaneGrid m_stPerceptionLaneGrid;
	ObstacleData m_stPerceptionObstalceData;
	//Display Data
	DisplayData m_stDisplayData;

	//Mission plan data and Function
	vector<PointXY> m_vecGlobalPath;
	vector<PointGps> m_vecRNDFRoute;

	//behavior plan data 
	BehaviorPlanData m_stBehaviorPlanData;
	list<int> m_listLeftBetter;
	list<int> m_listRightBetter;
	list<int> m_listHostWorse;
	void BehaviorPlan();
	void EvaluateLeftLane();
	void EvaluateRightLane();
	bool LaneCompare(LaneObstacle HostLane,LaneObstacle TargetLane);
	void InitialEvaluateLaneData();
	void BehaviorPlanManual();
	void BehaviorPlanSemiAuto();
	void BehaviorPlanSemiAutoLaneChange();
	void BehaviorPlanAutomatic();
	void ResetBehaviorOperateSemiAuto();
	//motion plan
	NavigationData m_stNavigationData;
	vector<PointXY> m_vecLineNaviPath;
	vector<PointXY> m_vecLocalPath;
	vector<PointXY> m_vecNavigationPath;
	CNavigationPathPlanner m_stNavigationPathPlanner;
	void MotionPlan();
	void PathPlan();
	void LineNavigate();
	void NavigationPathPlan();
	void SocialBehaviorPlan();
	//motion control
	void SpeedPlan();
	void SteerPlan();
	float PathSpeed();
	float SceneSpeed();
	float SocialBehaviorSpeed();
	void SteeringFactor();
	float GetPredictAngle(int);
	//Display
	vector<PointXY> m_vecTrajectory;

	//Control
	vector<PointXY> m_vecRealPathXY;
	RealSpeed m_stRealSpeed;
	RealSteer m_stRealSteer;
	DesignSpeed m_stDesignSpeed;
	DesignSteer m_stDesignSteer;
	SteerControlFactor m_stSteerCtrlFactor;
};

