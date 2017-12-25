#include "VehPlanning.h"
//#include "stdio.h"
GUIData gGUIData;
shared_mutex gGUIMutex;

CVehPlanning::CVehPlanning(QObject* parent) :QObject(parent)
{
	m_bThreadRun = true;
}


CVehPlanning::~CVehPlanning()
{

}

bool CVehPlanning::InitilizeLCM()
{
	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
	if (!m_pLCM->good())
	{
		//PrintErrorInfo("Cannot initilize the LCM,Please check the network communication!", __FILE__, __FUNCTION__, __LINE__);
		return false;
	}
	return true;
}

void CVehPlanning::Init()
{
	InitilizeLCM();
	m_fileOutRecordTrackPath.open(RECORDTRACKPATH_PATH);
}

void CVehPlanning::SetThreadState(bool state)
{
	m_bThreadRun = state;
}


void CVehPlanning::UpdateDisplayData()
{
	unique_lock<shared_mutex> DisplayLock(gGUIMutex);
	gGUIData = m_stGUIData;
	DisplayLock.unlock();

	m_stDisplayData.DisplayOperationStatus = m_stVehStatusData.enOperateStatus;
	m_stDisplayData.DisplayBehaviorStatus = m_stVehStatusData.enCurrentBehavior;

	m_stDisplayData.DisplayVehInfo = m_stVehInfoData;
	m_stDisplayData.DisplayRTKInfo = m_stRTKInfoData;
	m_stDisplayData.DisplayLine = m_stPerceptionLineData;
	m_stDisplayData.DisplayObs = m_stPerceptionObstalceData;
	m_stDisplayData.DisplayGUI = m_stGUIData;
	m_stDisplayData.DisplayNavigation = m_stNavigationData;
	m_stDisplayData.DisplayBehaviorData = m_stBehaviorPlanData;

	m_stDisplayData.DisplayDesignSpeed = m_stDesignSpeed;
	m_stDisplayData.DisplayDesignSteer = m_stDesignSteer;

	m_stDisplayData.DisplayVehTrajectory = m_vecTrajectory;
	emit(DisplayVehData(m_stDisplayData));
}

void CVehPlanning::UpdatePerceptionData()
{
	readLock RTKLock(gRTKMutex);
	m_stRTKInfoData = g_RTKData;
	RTKLock.unlock();

	readLock VehLock(gVehicleInfoMutex);
	m_stVehInfoData = gVehcleInfo;
	VehLock.unlock();
	if (m_stVehInfoData.bMessageReveive)
	{
		m_stVehStatusData.fRealSpeed = m_stVehInfoData.fSpeed / 3.6f;
		m_stRealSteer.iPosition = int(m_stVehInfoData.fSteeringWheelAngle);
	}

	readLock PerceptionLineLock(gLinesMutex);
	m_stPerceptionLineData = gLines;
	m_stPerceptionLaneGrid = gLaneGrids;
	PerceptionLineLock.unlock();

	readLock PerceptionObsLock(gObstaclesMutex);
	m_stPerceptionObstalceData = gObstacles;
	gObstaclesMutex.unlock();
}

void CVehPlanning::UpdateControlData()
{
	shared_lock<shared_mutex> steerLock(gSteerMutex);
	m_stRealSteer = gRealSteer;
	steerLock.unlock();
	shared_lock<shared_mutex> speedLock(gSpeedMutex);
	m_stRealSpeed = gRealSpeed;
	speedLock.unlock();

	m_stVehStatusData.fRealSpeed = m_stRealSpeed.fSpeed;
}

void CVehPlanning::UpdateGUIData()
{
	shared_lock<shared_mutex> GUILock(gGUIMutex);
	m_stGUIData = gGUIData;
	GUILock.unlock();
	m_stVehStatusData.enOperateStatus = m_stGUIData.enOperateStatus;//change the operation status
	m_stVehStatusData.fGUISpeed = m_stGUIData.iSpeed * KMH_MS;//get the Set speed from UI

//current global path
	//PointXY stCurrentGlobalPath;
}

void CVehPlanning::UpdateSourceData()
{
	UpdateGUIData();//update the data from the UI
	UpdatePerceptionData();//update the Perception Information
}

void CVehPlanning::EvaluateLeftLane()
{
//left lane safety
	m_stBehaviorPlanData.bLeftlaneSafe = false;
	if (m_stPerceptionLineData.bLeftLaneExist)
	{
		if (m_stPerceptionObstalceData.stLeftLaneObstacle.bFrontObsExist && m_stPerceptionObstalceData.stLeftLaneObstacle.bBackObsExist)
		{
			if ((m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iFrontNeraestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iFrontNeraestID).fDistance
				> (m_stVehStatusData.fRealSpeed * kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance))
				&& (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iBackNearestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iBackNearestID).fDistance
				> (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iBackNearestID).fAbsSpeed*kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance)))
			{
				m_stBehaviorPlanData.iLeftlaneSafeNum++;
			}
			else
			{
				m_stBehaviorPlanData.iLeftlaneSafeNum = 0;
			}
		}
		else if (m_stPerceptionObstalceData.stLeftLaneObstacle.bFrontObsExist && !m_stPerceptionObstalceData.stLeftLaneObstacle.bBackObsExist)
		{
			if ((m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iFrontNeraestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iFrontNeraestID).fDistance
				> (m_stVehStatusData.fRealSpeed * kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance)))
			{
				m_stBehaviorPlanData.iLeftlaneSafeNum++;
			}
			else
			{
				m_stBehaviorPlanData.iLeftlaneSafeNum = 0;
			}
		}
		else if (!m_stPerceptionObstalceData.stLeftLaneObstacle.bFrontObsExist && m_stPerceptionObstalceData.stLeftLaneObstacle.bBackObsExist)
		{
			if ((m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iBackNearestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iBackNearestID).fDistance
				> (m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stLeftLaneObstacle.iBackNearestID).fAbsSpeed*kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance)))
			{
				m_stBehaviorPlanData.iLeftlaneSafeNum++;
			}
			else
			{
				m_stBehaviorPlanData.iLeftlaneSafeNum = 0;
			}
		}
		else
		{
			m_stBehaviorPlanData.iLeftlaneSafeNum++;
		}
	}
	else
	{
		m_stBehaviorPlanData.iLeftlaneSafeNum = 0;
	}
	if (m_stBehaviorPlanData.iLeftlaneSafeNum > kLaneSafeNumberThreshold)
	{
		m_stBehaviorPlanData.bLeftlaneSafe = true;
	}
	else
	{
		m_stBehaviorPlanData.bLeftlaneSafe = false;
	}
//left lane priority
	m_stBehaviorPlanData.bLeftlaneBetter = false;
	int iLaneBetter;
	if (m_stPerceptionLineData.bLeftLaneExist)
	{
		if (m_stBehaviorPlanData.iLeftlaneBetterCalTimes < kDefaultTotalFrameNumber)
		{
			m_stBehaviorPlanData.iLeftlaneBetterCalTimes++;
			if (!m_stPerceptionObstalceData.stLeftLaneObstacle.bFrontObsExist)
			{
				iLaneBetter = 1;
			}
			else
			{
				if (LaneCompare(m_stPerceptionObstalceData.stHostLaneObstacle,m_stPerceptionObstalceData.stLeftLaneObstacle))
				{
					iLaneBetter = 1;
				}
			}
			m_listLeftBetter.push_back(iLaneBetter);
			m_stBehaviorPlanData.iLeftlaneBetterNum += m_listLeftBetter.back();
		}
		else
		{
			if (m_stPerceptionObstalceData.stLeftLaneObstacle.bFrontObsExist)
			{
				if (LaneCompare(m_stPerceptionObstalceData.stHostLaneObstacle,m_stPerceptionObstalceData.stLeftLaneObstacle))
				{
					iLaneBetter = 1;
				}
			}
			m_listLeftBetter.push_back(iLaneBetter);
			m_stBehaviorPlanData.iLeftlaneBetterNum += m_listLeftBetter.back();
			m_stBehaviorPlanData.iLeftlaneBetterNum -= m_listLeftBetter.front();
			m_listLeftBetter.pop_front();
			if (m_stBehaviorPlanData.iLeftlaneBetterNum >= kDefaultTotalFrameNumber*kDefaultLeftLaneBetterFrameThreshold)
			{
				m_stBehaviorPlanData.bLeftlaneBetter = true;
			}
		}
		if (!m_stPerceptionObstalceData.stLeftLaneObstacle.bFrontObsExist)
		{
			m_stBehaviorPlanData.bLeftlaneBetter = true;
		}
	}
	else
	{
		m_stBehaviorPlanData.bLeftlaneBetter = false;
	}
}

void CVehPlanning::EvaluateRightLane()
{
//right lane safety
	m_stBehaviorPlanData.bRightlaneSafe = false;
	if (m_stPerceptionLineData.bRightLaneExist)
	{
		if (m_stPerceptionObstalceData.stRightLaneObstacle.bFrontObsExist && m_stPerceptionObstalceData.stRightLaneObstacle.bBackObsExist)
		{
			if ((m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iFrontNeraestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iFrontNeraestID).fDistance
		> (m_stVehStatusData.fRealSpeed * kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance))
		&& (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iBackNearestID).fSafetyValue
		>= kObstacleSafeValueThreshold)
		&& (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iBackNearestID).fDistance
				> (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iBackNearestID).fAbsSpeed*kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance)))
			{
				m_stBehaviorPlanData.iRightlaneSafeNum++;
			}
			else
			{
				m_stBehaviorPlanData.iRightlaneSafeNum = 0;
			}
		}
		else if (m_stPerceptionObstalceData.stRightLaneObstacle.bFrontObsExist && !m_stPerceptionObstalceData.stRightLaneObstacle.bBackObsExist)
		{
			if ((m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iFrontNeraestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iFrontNeraestID).fDistance
				> (m_stVehStatusData.fRealSpeed * kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance)))
			{
				m_stBehaviorPlanData.iRightlaneSafeNum++;
			}
			else
			{
				m_stBehaviorPlanData.iRightlaneSafeNum = 0;
			}
		}
		else if (!m_stPerceptionObstalceData.stRightLaneObstacle.bFrontObsExist && m_stPerceptionObstalceData.stRightLaneObstacle.bBackObsExist)
		{
			if ((m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iBackNearestID).fSafetyValue
				>= kObstacleSafeValueThreshold)
				&& (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iBackNearestID).fDistance
				> (m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.at(m_stPerceptionObstalceData.stRightLaneObstacle.iBackNearestID).fAbsSpeed*kDefaultFrontMinTHW + kDefaultFrontMinVehicleDistance)))
			{
				m_stBehaviorPlanData.iRightlaneSafeNum++;
			}
			else
			{
				m_stBehaviorPlanData.iRightlaneSafeNum = 0;
			}
		}
		else
		{
			m_stBehaviorPlanData.iRightlaneSafeNum++;
		}
	}
	else
	{
		m_stBehaviorPlanData.iRightlaneSafeNum = 0;
	}
	if (m_stBehaviorPlanData.iRightlaneSafeNum > kLaneSafeNumberThreshold)
	{
		m_stBehaviorPlanData.bRightlaneSafe = true;
	}
	else
	{
		m_stBehaviorPlanData.bRightlaneSafe = false;
	}
//left lane priority
	m_stBehaviorPlanData.bRightlaneBetter = false;
	int iLaneBetter;
	if (m_stPerceptionLineData.bRightLaneExist)
	{
		if (m_stBehaviorPlanData.iRightlaneBetterCalTimes < kDefaultTotalFrameNumber)
		{
			m_stBehaviorPlanData.iRightlaneBetterCalTimes++;
			if (!m_stPerceptionObstalceData.stRightLaneObstacle.bFrontObsExist)
			{
				iLaneBetter = 1;
			}
			else
			{
				if (LaneCompare(m_stPerceptionObstalceData.stHostLaneObstacle, m_stPerceptionObstalceData.stRightLaneObstacle))
				{
					iLaneBetter = 1;
				}
			}
			m_listRightBetter.push_back(iLaneBetter);
			m_stBehaviorPlanData.iRightlaneBetterNum += m_listRightBetter.back();
		}
		else
		{
			if (m_stPerceptionObstalceData.stRightLaneObstacle.bFrontObsExist)
			{
				if (LaneCompare(m_stPerceptionObstalceData.stHostLaneObstacle, m_stPerceptionObstalceData.stRightLaneObstacle))
				{
					iLaneBetter = 1;
				}
			}
			m_listRightBetter.push_back(iLaneBetter);
			m_stBehaviorPlanData.iRightlaneBetterNum += m_listRightBetter.back();
			m_stBehaviorPlanData.iRightlaneBetterNum -= m_listRightBetter.front();
			m_listRightBetter.pop_front();
			if (m_stBehaviorPlanData.iRightlaneBetterNum >= kDefaultTotalFrameNumber*kDefaultRightLaneBetterFrameThreshold)
			{
				m_stBehaviorPlanData.bRightlaneBetter = true;
			}
		}
		if (!m_stPerceptionObstalceData.stRightLaneObstacle.bFrontObsExist)
		{
			m_stBehaviorPlanData.bRightlaneBetter = true;
		}
	}
	else
	{
		m_stBehaviorPlanData.bRightlaneBetter = false;
	}
}

void CVehPlanning::InitialEvaluateLaneData()
{
	m_stBehaviorPlanData.bOvertakeIntention = false;
	m_stBehaviorPlanData.iHostlaneCalTimes = 0;
	m_stBehaviorPlanData.iHostlaneWorseNum = 0;
	m_listHostWorse.clear();

	m_stBehaviorPlanData.bLeftlaneSafe = false;
	m_stBehaviorPlanData.bRightlaneSafe = false;
	m_stBehaviorPlanData.iLeftlaneSafeCalTimes = 0;
	m_stBehaviorPlanData.iLeftlaneSafeNum = 0;
	m_stBehaviorPlanData.iRightlaneSafeCalTimes = 0;
	m_stBehaviorPlanData.iRightlaneSafeNum = 0;

	m_stBehaviorPlanData.bLeftlaneBetter = false;
	m_stBehaviorPlanData.bRightlaneBetter = false;
	m_stBehaviorPlanData.iLeftlaneBetterCalTimes = 0;
	m_stBehaviorPlanData.iLeftlaneBetterNum = 0;
	m_stBehaviorPlanData.iRightlaneBetterCalTimes = 0;
	m_stBehaviorPlanData.iRightlaneBetterNum = 0;
	m_listLeftBetter.clear();
	m_listRightBetter.clear();
}

void CVehPlanning::BehaviorPlanManual()
{
	m_stVehStatusData.enNextBehavior = KEEP_LANE;
	m_stPerceptionLineData.bLeftChange = false;
	m_stPerceptionLineData.bRightChange = false;
	InitialEvaluateLaneData();
}

void CVehPlanning::BehaviorPlanSemiAutoLaneChange()
{
	if (!m_stPerceptionLineData.bLeftChange)
	{
		if (m_stVehStatusData.enCurrentBehavior == CHANGE_LEFT)
		{
			if (!m_stBehaviorPlanData.bLeftlaneSafe)
			{
				m_stVehStatusData.enNextBehavior = m_stVehStatusData.enLastBehavior;
			}
		}
	}
	else
	{
		if (m_stVehStatusData.enCurrentBehavior == CHANGE_LEFT)
		{
			m_stVehStatusData.enNextBehavior = KEEP_LANE;
		}
		InitialEvaluateLaneData();
		m_stPerceptionLineData.bLeftChange = false;
	}

	if (!m_stPerceptionLineData.bRightChange)
	{
		if (m_stVehStatusData.enCurrentBehavior == CHANGE_RIGHT)
		{
			if (!m_stBehaviorPlanData.bRightlaneSafe)
			{
				m_stVehStatusData.enNextBehavior = m_stVehStatusData.enLastBehavior;
			}
		}
	}
	else
	{
		if (m_stVehStatusData.enCurrentBehavior == CHANGE_RIGHT)
		{
			m_stVehStatusData.enNextBehavior = KEEP_LANE;
		}
		InitialEvaluateLaneData();
		m_stPerceptionLineData.bRightChange = false;
	}
}

void CVehPlanning::BehaviorPlanSemiAuto()
{
	if (m_stVehStatusData.enCurrentBehavior == CHANGE_LEFT || m_stVehStatusData.enCurrentBehavior == CHANGE_RIGHT)
	{
		BehaviorPlanSemiAutoLaneChange();
	}
	else if (m_stVehStatusData.enCurrentBehavior == KEEP_LANE)
	{
		m_stVehStatusData.enNextBehavior = m_stGUIData.enBehaviorStatus;
	}
}

void CVehPlanning::BehaviorPlanAutomatic()
{
	m_stVehStatusData.enNextBehavior = m_stVehStatusData.enCurrentBehavior;
	//if (m_stPerceptionLineData.iLeftLaneProperty <= 1)
	//{
	//	m_stBehaviorPlanData.bLeftlaneSafe = false;
	//	m_stBehaviorPlanData.bLeftlaneBetter = false;
	//}
	//if (m_stPerceptionLineData.iRightLaneProperty <= 1)
	//{
	//	m_stBehaviorPlanData.bRightlaneSafe = false;
	//	m_stBehaviorPlanData.bRightlaneBetter = false;
	//}

	//behavior from MAP
	if (m_stPerceptionLineData.iLeftLaneProperty == 1)
	{
		m_stVehStatusData.enNextBehavior = CHANGE_LEFT;
	}
	else if (m_stPerceptionLineData.iRightLaneProperty == 1)
	{
		m_stVehStatusData.enNextBehavior = CHANGE_RIGHT;
	}
	else
	{
		m_stVehStatusData.enNextBehavior = KEEP_LANE;
	}
}

void CVehPlanning::ResetBehaviorOperateSemiAuto()
{
	if (m_stVehStatusData.enOperateStatus == SEMI_AUTOMATIC)
	{
		if (m_stVehStatusData.enCurrentBehavior == CHANGE_LEFT || m_stVehStatusData.enCurrentBehavior == CHANGE_RIGHT)
		{
			if (m_stGUIData.bResetSemiAutoBehaviorStatus)
			{
				m_stVehStatusData.enNextBehavior = KEEP_LANE;
				m_stGUIData.bResetSemiAutoBehaviorStatus = false;
			}
		}
	}
}

void CVehPlanning::BehaviorPlan()
{
	EvaluateLeftLane();
	EvaluateRightLane();
	switch (m_stVehStatusData.enOperateStatus)
	{
	case MANUAL:
		BehaviorPlanManual();
		break;
	case SEMI_AUTOMATIC:
		BehaviorPlanSemiAuto();
		break;
	case AUTOMATIC:
		BehaviorPlanAutomatic();
		break;
	default:
		break;
	}
//write lane change state into the global value;
	writeLock mtx_LinesLock(gLinesMutex);
	gLines.bLeftChange = m_stPerceptionLineData.bLeftChange;
	gLines.bRightChange = m_stPerceptionLineData.bRightChange;
	mtx_LinesLock.unlock();

	ResetBehaviorOperateSemiAuto();
	if (m_stVehStatusData.enCurrentBehavior != m_stVehStatusData.enNextBehavior)
	{
		m_stVehStatusData.enLastBehavior = m_stVehStatusData.enCurrentBehavior;
		m_stVehStatusData.enCurrentBehavior = m_stVehStatusData.enNextBehavior;
	}
	m_stGUIData.enBehaviorStatus = m_stVehStatusData.enCurrentBehavior;
}

void CVehPlanning::LineNavigate()
{
	vector<Obstacle> vecObstacles;
	vecObstacles.insert(vecObstacles.end(), m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.begin(), m_stPerceptionObstalceData.stLeftLaneObstacle.vecObstacles.end());
	vecObstacles.insert(vecObstacles.end(), m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.begin(), m_stPerceptionObstalceData.stRightLaneObstacle.vecObstacles.end());
	m_stNavigationPathPlanner.GetLaneGrid(m_stPerceptionLaneGrid);
	m_stNavigationPathPlanner.GetObstacles(vecObstacles);
	m_stNavigationPathPlanner.GetVehicleSpeed(m_stVehStatusData.fRealSpeed);
	if (m_stVehStatusData.enCurrentBehavior == CHANGE_LEFT || m_stVehStatusData.enCurrentBehavior == OVER_LEFT)
	{
		m_stNavigationPathPlanner.IDLaneLeftChange();
	}
	else if (m_stVehStatusData.enCurrentBehavior == CHANGE_RIGHT || m_stVehStatusData.enCurrentBehavior == OVER_RIGHT)
	{
		m_stNavigationPathPlanner.IDLaneRightChange();
	}
	else
	{
		m_stNavigationPathPlanner.IDLaneKeep();
	}
	m_stNavigationPathPlanner.GenerateNavigationPath();
	m_vecLineNaviPath = m_stNavigationPathPlanner.GetNavigationPath();
}

void CVehPlanning::NavigationPathPlan()
{
	LineNavigate();
	vector<PointXY>().swap(m_vecNavigationPath);//m_vecNavigationPath.clear();
	m_stNavigationData.bPath = false;
	if (m_vecLineNaviPath.size() > MIN_GLOBALLOCALPATH_LENGTH)
	{
		m_vecNavigationPath = m_vecLineNaviPath;
		m_stNavigationData.bPath = true;
	}
	emit(DisplayGlobalLocalPath(m_vecNavigationPath));
}

void CVehPlanning::PathPlan()
{
	vector<PointXY>().swap(m_vecLocalPath);// m_vecLocalPath.clear();
	NavigationPathPlan();
	if (m_stNavigationData.bPath)
	{
		//interpolate the navigation path
		m_vecNavigationPath = m_stNavigationPathPlanner.PathInterpolate(m_vecNavigationPath);
		m_vecLocalPath = m_stNavigationPathPlanner.LocalPathPlan(m_vecNavigationPath, m_stNavigationData.iPreviewDis);
	}
	emit(DisplayLocalPath(m_vecLocalPath));
}

void CVehPlanning::SpeedPlan()
{
	float fPathSpeed = PathSpeed();
	float fSceneSpeed = SceneSpeed();
	float fSocialSpeed = SocialBehaviorSpeed();
	m_stDesignSpeed.fSpeed = GetMin(fPathSpeed, fSocialSpeed);
	m_stDesignSpeed.fSpeed = GetMin(m_stDesignSpeed.fSpeed, fSceneSpeed);

	//TFL speed

	if (m_stDesignSpeed.fSpeed >= MAX_SPEED)
	{
		m_stDesignSpeed.fSpeed = MAX_SPEED;
	}
	if (m_stDesignSpeed.fSpeed < 0)
	{
		m_stDesignSpeed.fSpeed = 0.0f;
	}
	m_stDesignSpeed.iModle = 0;
}

void CVehPlanning::SteeringFactor()
{
	if (m_stVehStatusData.fRealSpeed < 10.0f)
	{
		m_stDesignSteer.iSpeed = 40;
	}
	else
	{
		m_stDesignSteer.iSpeed = 0;
	}
	m_stSteerCtrlFactor.iPredictNum = m_stNavigationData.iPreviewDis;

	if (m_stVehStatusData.fRealSpeed < 5.0f)
	{
		m_stSteerCtrlFactor.fAngleFactor = 18.0f;
	}
	else if (m_stVehStatusData.fRealSpeed >= 5.0f && m_stVehStatusData.fRealSpeed < 20.0f)
	{
		m_stSteerCtrlFactor.fAngleFactor = 20.0f;
	}
	else if (m_stVehStatusData.fRealSpeed >= 20.0f && m_stVehStatusData.fRealSpeed < 30.0f)
	{
		m_stSteerCtrlFactor.fAngleFactor = 20.0f;
	}
	else
	{
		m_stSteerCtrlFactor.fAngleFactor = 4.0f;
	}

	if (m_stVehStatusData.fRealSpeed < 5.0f)
	{
		m_stSteerCtrlFactor.fMaxDeltaAngle = 50.0f;
	}
	else if (m_stVehStatusData.fRealSpeed >= 5.0f && m_stVehStatusData.fRealSpeed < 20.0f)
	{
		m_stSteerCtrlFactor.fMaxDeltaAngle = 20.0f;
	}
	else if (m_stVehStatusData.fRealSpeed >= 20.0f && m_stVehStatusData.fRealSpeed < 30.0f)
	{
		m_stSteerCtrlFactor.fMaxDeltaAngle = 6.0f;
	}
	else
	{
		m_stSteerCtrlFactor.fMaxDeltaAngle = 2.0f;
	}

	if (m_stVehStatusData.fRealSpeed < 5.0f)
	{
		m_stSteerCtrlFactor.fMaxAngle = 550.0f;
	}
	else if (m_stVehStatusData.fRealSpeed >= 5.0f && m_stVehStatusData.fRealSpeed < 35.0f)
	{
		m_stSteerCtrlFactor.fMaxAngle = ceil(0.6*(35.0f - m_stVehStatusData.fRealSpeed)*(35.0f - m_stVehStatusData.fRealSpeed) + 10);
	}
	else
	{
		m_stSteerCtrlFactor.fMaxAngle = 10.0f;
	}
}

float CVehPlanning::GetPredictAngle(int num)
{
	float fAngle = 0.0f;
	if (m_vecLocalPath.empty() || m_vecLocalPath.size() <= num)
	{
		m_stNavigationData.bPath = false;
	}
	else
	{
		fAngle = GetAngleWithY(m_vecLocalPath.at(num - 1));
	}
	return fAngle;
}

void CVehPlanning::SteerPlan()
{
	SteeringFactor();
	m_stSteerCtrlFactor.fAngle = GetPredictAngle(m_stSteerCtrlFactor.iPredictNum);
	if (m_stSteerCtrlFactor.fAngle == 0.0f && !m_stNavigationData.bPath)
	{
		m_stDesignSteer.iPosition = m_stRealSteer.iPosition;
	}
	else
	{
		m_stDesignSteer.iPosition = (int)round(m_stSteerCtrlFactor.fAngle*m_stSteerCtrlFactor.fAngleFactor);
		if ((float)abs(m_stDesignSteer.iPosition - m_stRealSteer.iPosition) > m_stSteerCtrlFactor.fMaxDeltaAngle)
		{
			if (m_stDesignSteer.iPosition - m_stRealSteer.iPosition > 0)
			{
				m_stDesignSteer.iPosition = m_stRealSteer.iPosition + (int)m_stSteerCtrlFactor.fMaxDeltaAngle;
			}
			else
			{
				m_stDesignSteer.iPosition = m_stRealSteer.iPosition - (int)m_stSteerCtrlFactor.fMaxDeltaAngle;
			}
		}
		if ((float)abs(m_stDesignSteer.iPosition) > m_stSteerCtrlFactor.fMaxAngle)
		{
			if (m_stDesignSteer.iPosition > 0)
			{
				m_stDesignSteer.iPosition = m_stSteerCtrlFactor.fMaxAngle;
			}
			else
			{
				m_stDesignSteer.iPosition = -m_stSteerCtrlFactor.fMaxAngle;
			}
		}
		if (abs(m_stDesignSteer.iPosition) > MAXSTEERINGANGLE)
		{
			if (m_stDesignSteer.iPosition > 0)
			{
				m_stDesignSteer.iPosition = MAXSTEERINGANGLE;
			}
			else
			{
				m_stDesignSteer.iPosition = -MAXSTEERINGANGLE;
			}
		}
	}
	if (m_stVehStatusData.enOperateStatus == AUTOMATIC || m_stVehStatusData.enOperateStatus == SEMI_AUTOMATIC)
	{
	}
}

float CVehPlanning::PathSpeed()
{
	return m_stNavigationData.fSpeed;
}

float CVehPlanning::SceneSpeed()
{
	float fSceneSpeed;
	bool bTargetFlag = false;
	float fDis = 0.0;
	float fFrontObsSpeed = 0.0f;
	if (m_stPerceptionObstalceData.stHostLaneObstacle.vecObstacles.empty())
	{
		bTargetFlag = false;
	}
	else
	{
		if (m_stPerceptionObstalceData.stHostLaneObstacle.vecObstacles[0].stCenterPoint.y > 0.0)
		{
			bTargetFlag = true;
			fDis = m_stPerceptionObstalceData.stHostLaneObstacle.vecObstacles[0].fDistance;
			fFrontObsSpeed = m_stPerceptionObstalceData.stHostLaneObstacle.vecObstacles[0].fAbsSpeed;
		}
		else
		{
			bTargetFlag = false;
		}
	}

	float fSpeedLimit = m_stVehStatusData.fGUISpeed;
	float fSelfSpeed = m_stVehStatusData.fRealSpeed;
	//accelerate
	float fSelfAcc = m_stVehInfoData.fAcc;
	float fDeltaTime = 0.1;
	float fLaneChangePercentage = 0.0f;
	float fSpeedExpandFactor = 0.0f;
	fSceneSpeed = NextSpeed(bTargetFlag, fSpeedLimit, fDis, fSelfSpeed, fFrontObsSpeed, fSelfAcc, fDeltaTime);
	if (fSelfSpeed <= 3.0f)
	{
		if (m_stVehStatusData.enCurrentBehavior == CHANGE_LEFT || m_stVehStatusData.enCurrentBehavior == CHANGE_RIGHT ||
			m_stVehStatusData.enCurrentBehavior == OVER_LEFT || m_stVehStatusData.enCurrentBehavior == OVER_RIGHT)
		{
			fLaneChangePercentage = fabs((m_stPerceptionLineData.stLeft.vecLinePoints.at(kBackInterestArrayLength).x + m_stPerceptionLineData.stRight.vecLinePoints.at(kBackInterestArrayLength).x) / 2) /
				fabs((m_stPerceptionLineData.stLeft.vecLinePoints.at(kBackInterestArrayLength).x - m_stPerceptionLineData.stRight.vecLinePoints.at(kBackInterestArrayLength).x) / 2);
			fSpeedExpandFactor = (1 - (1.0f - fLaneChangePercentage)*(1.0f - fLaneChangePercentage)) / 10.f;
			if (bTargetFlag)
			{
				if (fDis > STOP_DISTANCE)
				{
					fSceneSpeed = fSceneSpeed*(1.0f + fSpeedExpandFactor);
				}
				else
				{
					fSceneSpeed = fSceneSpeed + 3 * (1.0f - exp(-(fDis - 7.0f) / 20.0f));
				}
			}
		}
	}
	return fSceneSpeed;
}

float CVehPlanning::SocialBehaviorSpeed()
{
	float fspeed = 35.0f;
	if (m_stVehStatusData.enSocialBehavior == NORMAL)
	{
		return fspeed;
	}
	else if (m_stVehStatusData.enSocialBehavior == INTERSECTION_WITH_TRAFFIC_LIGHT)
	{

	}
	else if (m_stVehStatusData.enSocialBehavior == INTERSECTION_WITHOUT_TRAFFIC_LIGHT)
	{
		return fspeed;
	}
	else if (m_stVehStatusData.enSocialBehavior == FINISH_TASK)
	{

	}
	else
	{
		return fspeed;
	}
}

void CVehPlanning::MotionPlan()
{
	PathPlan();
	SpeedPlan();
	SteerPlan();
}

void CVehPlanning::PlanningThreadRun()
{
	int64_t iCurrentTime;
	int64_t iLastTime;
	while (m_bThreadRun)
	{
		iLastTime = timestamp_now();
		UpdateSourceData();//update the perception data, changed data from UI and Vehicle Control data
		BehaviorPlan();
		MotionPlan();
		UpdateDisplayData();
		iCurrentTime = timestamp_now();
		double dDeltaTime = (double)(iCurrentTime - iLastTime) / 1000.0;
		this_thread::sleep(posix_time::milliseconds(100));//thread sleep 100 ms;
	}
}


bool CVehPlanning::LaneCompare(LaneObstacle HostLane, LaneObstacle TargetLane)
{
	float fTargetlaneSpeed = 0.0f;
	float fHostlaneSpeed = 0.0f;
	if (!HostLane.bFrontObsExist)
	{
		return false;
	}
	else
	{
		fTargetlaneSpeed = TargetLane.fFrontAverageSpeed;
		fHostlaneSpeed = HostLane.vecObstacles[HostLane.iFrontNeraestID].fAbsSpeed;
		if (fTargetlaneSpeed > kTargetLaneVelocityThreshold)
		{
			if (fTargetlaneSpeed*kDefaultSelfVelocityLowerThreshold > fHostlaneSpeed)
			{
				return true;
			}
		}
		else
		{
			if ((fTargetlaneSpeed-fHostlaneSpeed) >= kMinVelocityGapThreshold)
			{
				return true;
			}
		}
	}
	return false;
}