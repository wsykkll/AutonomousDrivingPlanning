#pragma once
#include "PerceptionLines.h"
#include "PERCEPTION_OBSTACLE.hpp"
#include "PERCEPTION_OBSTACLES.hpp"

const float kDefaultMaxExpandWidth = 0.8;
const float kMaxExpandTime = 15;
const float kDangerMeetTimeThreshold = 20;
const float kMaxTimeLocation = 100;

const float kDefaultCarWidth = 1.8;
const float kDefaultCarHeight = 4;
const float kDefaultHumanWidth = 0.5;
const float kDefaultHumanHeight = 2;
const float kDefaultTruckWidth = 2.5;
const float kDefaultTruckHeight = 6;

const float kDefaultMinSafetyDistance = 1.0;
const float kDefaultBrakeTimeDelay = 1.0;
const float kDefaultMaxBrakeDeceleration = 8.0;
const float kDefaultMaxSafetyValue = 100.0;
const float kDefaultRearFactor = 2.0;

const int kMaxNextLaneObsNum = 10;
const int kMaxHostLaneObsNum = 2;
const int kMaxOutLaneObsNum = 40;

const float kDefaultTrajectoryNum = 200;
const float kDefaultDeltaTime = 0.1;

enum ObsLocalization
{
	UNKNOWN,
	HOST_BACK,
	HOST_FRONT,
	LEFT_BACK,
	LEFT_FRONT,
	RIGHT_BACK,
	RIGHT_FRONT,
	OUT_LANES
};

struct Obstacle
{
	bool bExist;
	bool bMoving;
	bool bDangerous;
	int16_t iBackBaseID;
	int16_t iFrontBaseID;
	float fHeading;
	float fOrientation;

	int8_t iType;
	float fWidth;
	float fHeight;
	float fAbsSpeed;
	float fAbsSpeedX;
	float fAbsSpeedY;
	float fRelatSpeed;
	float fRelatSpeedX;
	float fRelatSpeedY;

	float fDistance;
	float fExpWidth;
	float fExpHeight;
	float fSafetyValue;
	float fExpFactor;
	float fSafetyDistance;

	int8_t iTrend;
	ObsLocalization enLocalization;

	PointXY stCenterPoint;
	PointXY stRearCenterPoint;
	PointXY stLeftFrontCorner;
	PointXY stRightFrontCorner;
	PointXY stLeftBackCorner;
	PointXY stRightBackCorner;

	vector<PointXY> vecTrajectory;
	Obstacle()
	{
		bExist = false;
		bMoving = false;
		bDangerous = false;
		iBackBaseID = 0;
		iFrontBaseID = 0;
		fHeading = 0.0f;
		fOrientation = 0.0f;

		iType = -1;
		fWidth = 0.0f;
		fHeight = 0.0f;
		fAbsSpeed = 0.0f;
		fAbsSpeedX = 0.0f;
		fAbsSpeedY = 0.0f;
		fRelatSpeed = 0.0f;
		fRelatSpeedX = 0.0f;
		fRelatSpeedY = 0.0f;

		fDistance = 0.0f;
		fExpWidth = 0.0f;
		fExpHeight = 0.0f;
		fExpFactor = 0.0f;
		
		iTrend = -1;
		enLocalization = UNKNOWN;
	}
};

struct LaneObstacle
{
	bool bBackObsExist;
	bool bFrontObsExist;

	float fBackAverageSpeed;
	float fBackAverageDis;
	float fFrontAverageSpeed;
	float fFrontAverageDis;

	int16_t iBackNearestID;
	int16_t iFrontNeraestID;

	int16_t iFrontObsNum;
	int16_t iBackObsNum;
	int16_t iTotalObsNum;

	vector<Obstacle> vecObstacles;
	LaneObstacle()
	{
		bBackObsExist = false;
		bFrontObsExist = false;
		fFrontAverageDis = 0.0f;
		fBackAverageDis = 0.0f;
		fFrontAverageSpeed = 0.0f;
		fBackAverageSpeed = 0.0f;
		iBackNearestID = -1;
		iFrontNeraestID = -1;
		iFrontObsNum = 0;
		iBackObsNum = 0;
		iTotalObsNum = 0;
	}
};

struct OutLaneObstacle
{
	bool bExist;
	vector<Obstacle> vecOutLaneObstacles;
	OutLaneObstacle()
	{
		bExist = false;
	}
};

struct ObstacleData
{
	bool bMsgConnected;
	bool bMsgLost;
	int16_t iCounter;
	int16_t iLastCounter;
	int64_t iTimeStamp;
	int64_t iLastTimeStamp;
	int16_t iMsgLostNum;

	LaneObstacle stLeftLaneObstacle;
	LaneObstacle stHostLaneObstacle;
	LaneObstacle stRightLaneObstacle;
	OutLaneObstacle stOutLaneObstacle;
	float fVehSpeed;
	int iHandlerReturn;

	ObstacleData()
	{
		bMsgConnected = false;
		bMsgLost = false;

		iCounter = 0;
		iLastCounter = 0;
		iTimeStamp = 0;
		iLastTimeStamp = 0;
		iMsgLostNum = 0;
		fVehSpeed = 0.0f;
		iHandlerReturn = 0;
	}
};

extern ObstacleData gObstacles;
extern shared_mutex gObstaclesMutex;

class CPerceptionObstacles
{
public:
	CPerceptionObstacles();
	~CPerceptionObstacles();
	
	ObstacleData m_stObstacleData;
	int64_t m_iLastRecvTime;
	int64_t m_iCurrentRecvTime;

	lcm::LCM* m_pLCM;
	void LCMHandler(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, PERCEPTION_OBSTACLES* msg);
	bool InitializeLCM();
	void ObstacleProcess();

	void SetThreadState(bool state);
	void ObstacleThreadRun();
private:
	bool m_bThreadRun;
	float m_fMaxExpFactor;

	LineData m_stLines;
	LaneGrid m_stLaneGrids;
	PERCEPTION_OBSTACLES* m_pmsgPerceptionObstacle;

	Obstacle CopySignleObs(const PERCEPTION_OBSTACLE obs);
	void CalculateSafetyValue(Obstacle* obs);
	void CalculateSafetyDistance(Obstacle* obs);
	void CalculateExpansionFactor(Obstacle* obs);
	void CalculateObstacleCorner(Obstacle* obs);
	int CalculateObstacleBaseID(PointXY cornerPoint, Grid grid);
	void CalculateObstacleInLane(LaneObstacle* laneobs);
	void Expansion();
	void CopyRawData();
	void SafetyJudge();
	void RenewObstacles();
	void LaneObstaclesProcess();
};

