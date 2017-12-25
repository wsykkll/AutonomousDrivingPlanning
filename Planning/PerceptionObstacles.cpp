#include "PerceptionObstacles.h"

ObstacleData gObstacles;
shared_mutex gObstaclesMutex;

CPerceptionObstacles::CPerceptionObstacles():
m_bThreadRun(true),
m_fMaxExpFactor(3.0f)
{
	m_pmsgPerceptionObstacle = new PERCEPTION_OBSTACLES;
}


CPerceptionObstacles::~CPerceptionObstacles()
{
	delete[] m_pmsgPerceptionObstacle;
}

bool CPerceptionObstacles::InitializeLCM()
{
	m_iLastRecvTime = timestamp_now();
	m_stObstacleData.iLastTimeStamp = m_iLastRecvTime;
	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
	if (!m_pLCM->good())
	{
		return false;
	}
	return true;
}

void CPerceptionObstacles::SetThreadState(bool state)
{
	m_bThreadRun = state;
}

Obstacle CPerceptionObstacles::CopySignleObs(const PERCEPTION_OBSTACLE obs)
{
	Obstacle ReObs;
	if (obs.bValid == 1)
	{
		ReObs.bExist = true;
		ReObs.iType = obs.nType;
		if (ReObs.iType == 0)
		{
			ReObs.fWidth = kDefaultCarWidth;
			ReObs.fHeight = kDefaultCarHeight;
		}
		else
		{
			ReObs.fWidth = obs.fWidth;
			ReObs.fHeight = obs.fLength;
		}
		ReObs.fHeading = obs.fHeading;
		ReObs.fOrientation = obs.fOrient;
		ReObs.stCenterPoint.x = obs.fRelX;
		ReObs.stCenterPoint.y = obs.fRelY;
		ReObs.stRearCenterPoint.x = ReObs.stCenterPoint.x - cos(ReObs.fHeading)*ReObs.fHeight / 2;
		ReObs.stRearCenterPoint.y = ReObs.stCenterPoint.y - sin(ReObs.fHeading)*ReObs.fHeight / 2;
		if (ReObs.stCenterPoint.y > 0)
		{
			ReObs.fDistance = obs.fDistance - ReObs.fHeight / 2 - 4.0f;
		}
		else
		{
			ReObs.fDistance = obs.fDistance - ReObs.fHeight / 2 - 1.0f;
		}
		if (ReObs.fDistance < 0.0f)
		{
			ReObs.fDistance = 0.0f;
		}
		ReObs.fAbsSpeedX = obs.fAbsVelX;
		ReObs.fAbsSpeedY = obs.fAbsVelY;
		ReObs.fAbsSpeed = obs.fAbsSpeed;
		ReObs.fRelatSpeedX = obs.fRelVelX;
		ReObs.fRelatSpeedY = obs.fRelVelY;
		ReObs.fRelatSpeed = obs.fRelSpeed;
		if (obs.bObservedMoving == 1)
		{
			ReObs.bMoving = true;
		}
		else
		{
			ReObs.bMoving = true;
		}
		ReObs.iTrend = obs.nMotionTrend;
	}
	else
	{
		ReObs.bExist = false;
	}
	return ReObs;
}

void CPerceptionObstacles::CopyRawData()
{
	vector<Obstacle>().swap(m_stObstacleData.stLeftLaneObstacle.vecObstacles);
	vector<Obstacle>().swap(m_stObstacleData.stRightLaneObstacle.vecObstacles);
	vector<Obstacle>().swap(m_stObstacleData.stHostLaneObstacle.vecObstacles);
	vector<Obstacle>().swap(m_stObstacleData.stOutLaneObstacle.vecOutLaneObstacles);

	Obstacle tmpObs;
	for (size_t i = 0; i < kMaxNextLaneObsNum; i++)
	{
		tmpObs = CopySignleObs(m_pmsgPerceptionObstacle->gstLeftLaneObstacles[i]);
		if (tmpObs.bExist)
		{
			if (tmpObs.stCenterPoint.y > 0)
			{
				tmpObs.enLocalization = LEFT_FRONT;
			}
			else
			{
				tmpObs.enLocalization = LEFT_BACK;
			}
			m_stObstacleData.stLeftLaneObstacle.vecObstacles.push_back(tmpObs);
		}
	}
	for (size_t i = 0; i < kMaxNextLaneObsNum; i++)
	{
		tmpObs = CopySignleObs(m_pmsgPerceptionObstacle->gstRightLaneObstacles[i]);
		if (tmpObs.bExist)
		{
			if (tmpObs.stCenterPoint.y > 0)
			{
				tmpObs.enLocalization = RIGHT_FRONT;
			}
			else
			{
				tmpObs.enLocalization = RIGHT_BACK;
			}
			m_stObstacleData.stRightLaneObstacle.vecObstacles.push_back(tmpObs);
		}
	}
	for (size_t i = 0; i < kMaxHostLaneObsNum; i++)
	{
		tmpObs = CopySignleObs(m_pmsgPerceptionObstacle->gstMiddleLaneObstacles[i]);
		if (tmpObs.bExist)
		{
			if (tmpObs.stCenterPoint.y > 0)
			{
				tmpObs.enLocalization = HOST_FRONT;
			}
			else
			{
				tmpObs.enLocalization = HOST_BACK;
			}
			m_stObstacleData.stHostLaneObstacle.vecObstacles.push_back(tmpObs);
		}
	}
	for (size_t i = 0; i < kMaxOutLaneObsNum; i++)
	{
		tmpObs = CopySignleObs(m_pmsgPerceptionObstacle->gstOutLaneObstacles[i]);
		if (tmpObs.bExist)
		{
			tmpObs.enLocalization = OUT_LANES;
			m_stObstacleData.stOutLaneObstacle.vecOutLaneObstacles.push_back(tmpObs);
		}
	}
	if (m_stObstacleData.stOutLaneObstacle.vecOutLaneObstacles.size()>0)
	{
		m_stObstacleData.stOutLaneObstacle.bExist = true;
	}
	else
	{
		m_stObstacleData.stOutLaneObstacle.bExist = false;
	}
}

void CPerceptionObstacles::CalculateSafetyDistance(Obstacle* obs)
{
	shared_lock<shared_mutex> speed_lock(gObstaclesMutex);
	m_stObstacleData.fVehSpeed = gObstacles.fVehSpeed;
	speed_lock.unlock();
	if (obs->bExist)
	{
		if (obs->stCenterPoint.y > 0)
		{
			obs->fSafetyDistance = m_stObstacleData.fVehSpeed*kDefaultBrakeTimeDelay + 
				(m_stObstacleData.fVehSpeed*m_stObstacleData.fVehSpeed - obs->fAbsSpeed*obs->fAbsSpeed) / 2 / kDefaultMaxBrakeDeceleration;
		}
		else
		{
			obs->fSafetyDistance = obs->fAbsSpeed*kDefaultBrakeTimeDelay + 
				(obs->fAbsSpeed*obs->fAbsSpeed - m_stObstacleData.fVehSpeed*m_stObstacleData.fVehSpeed) / 2 / kDefaultMaxBrakeDeceleration;
		}
		if (obs->fSafetyDistance <= kDefaultMinSafetyDistance)
		{
			obs->fSafetyDistance = kDefaultMinSafetyDistance;
		}
	}
}

void CPerceptionObstacles::CalculateSafetyValue(Obstacle* obs)
{
	if (obs->bExist)
	{
		CalculateSafetyDistance(obs);
		obs->fSafetyValue = obs->fDistance / obs->fSafetyDistance;
		if (obs->stCenterPoint.y <= 0)
		{
			obs->fSafetyValue *= kDefaultRearFactor;
		}
		if (obs->fSafetyValue >= kDefaultMaxSafetyValue)
		{
			obs->fSafetyValue = kDefaultMaxSafetyValue;
		}
	}
}

void CPerceptionObstacles::SafetyJudge()
{
	for (size_t i = 0; i < m_stObstacleData.stLeftLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateSafetyValue(&m_stObstacleData.stLeftLaneObstacle.vecObstacles[i]);
	}
	for (size_t i = 0; i < m_stObstacleData.stHostLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateSafetyValue(&m_stObstacleData.stHostLaneObstacle.vecObstacles[i]);
	}
	for (size_t i = 0; i < m_stObstacleData.stRightLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateSafetyValue(&m_stObstacleData.stRightLaneObstacle.vecObstacles[i]);
	}
}

void CPerceptionObstacles::CalculateExpansionFactor(Obstacle* obs)
{
	if (obs->bExist)
	{
		obs->fExpFactor = 1 - (obs->fSafetyValue) / kDefaultMaxSafetyValue;
		obs->fExpWidth = obs->fExpFactor*(obs->fWidth + kDefaultMaxExpandWidth);
		obs->fExpHeight = obs->fHeight;
	}
}

void CPerceptionObstacles::Expansion()
{
	for (size_t i = 0; i < m_stObstacleData.stLeftLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateExpansionFactor(&m_stObstacleData.stLeftLaneObstacle.vecObstacles[i]);
	}
	for (size_t i = 0; i < m_stObstacleData.stHostLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateExpansionFactor(&m_stObstacleData.stHostLaneObstacle.vecObstacles[i]);
	}
	for (size_t i = 0; i < m_stObstacleData.stRightLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateExpansionFactor(&m_stObstacleData.stRightLaneObstacle.vecObstacles[i]);
	}
}

int CPerceptionObstacles::CalculateObstacleBaseID(PointXY cornerPoint, Grid grid)
{
	PointXY tmpPoint;
	double dMinDis = 1000000.0;
	double dTmpDis = 0.0;
	int iMinIndex = 0;
	for (int i = 0; i < grid.iBaseAmount; i++)
	{
		tmpPoint.x = grid.stGridBase[i].dCenterX;
		tmpPoint.y = grid.stGridBase[i].dCenterY;
		dTmpDis = Distance(cornerPoint, tmpPoint);
		if (dTmpDis < dMinDis)
		{
			dMinDis = dTmpDis;
			iMinIndex = i;
		}
	}
	if (cornerPoint.y <= grid.stGridBase[0].dCenterY)
	{
		return -1;
	}
	return iMinIndex;
}

void CPerceptionObstacles::CalculateObstacleCorner(Obstacle* obs)
{
	obs->stLeftFrontCorner.x = obs->stRearCenterPoint.x - obs->fExpHeight*sin(obs->fHeading) - obs->fExpWidth*cos(obs->fHeading) / 2;
	obs->stLeftFrontCorner.y = obs->stRearCenterPoint.y + obs->fExpHeight*cos(obs->fHeading) - obs->fExpWidth*sin(obs->fHeading) / 2;
	obs->stLeftBackCorner.x = obs->stRearCenterPoint.x - obs->fExpWidth*cos(obs->fHeading) / 2;
	obs->stLeftBackCorner.y = obs->stRearCenterPoint.y - obs->fExpWidth*sin(obs->fHeading) / 2;
	obs->stRightFrontCorner.x = obs->stRearCenterPoint.x - obs->fExpHeight*sin(obs->fHeading) + obs->fExpWidth*cos(obs->fHeading) / 2;
	obs->stRightFrontCorner.y = obs->stRearCenterPoint.y + obs->fExpHeight*cos(obs->fHeading) + obs->fExpWidth*sin(obs->fHeading) / 2;
	obs->stRightBackCorner.x = obs->stRearCenterPoint.x + obs->fExpWidth*cos(obs->fHeading) / 2;
	obs->stRightBackCorner.y = obs->stRearCenterPoint.y + obs->fExpWidth*sin(obs->fHeading) / 2;
	if (obs->enLocalization == LEFT_FRONT || obs->enLocalization == LEFT_BACK)
	{
		obs->iFrontBaseID = CalculateObstacleBaseID(obs->stRightFrontCorner, m_stLaneGrids.stLeftGrid);
		obs->iBackBaseID = CalculateObstacleBaseID(obs->stRightBackCorner, m_stLaneGrids.stLeftGrid);
	}
	if (obs->enLocalization==RIGHT_FRONT || obs->enLocalization == RIGHT_BACK)
	{
		obs->iFrontBaseID = CalculateObstacleBaseID(obs->stLeftFrontCorner, m_stLaneGrids.stRightGrid);
		obs->iBackBaseID = CalculateObstacleBaseID(obs->stLeftBackCorner, m_stLaneGrids.stRightGrid);
	}
}


void CPerceptionObstacles::RenewObstacles()
{
	for (size_t i = 0; i < m_stObstacleData.stLeftLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateObstacleCorner(&m_stObstacleData.stLeftLaneObstacle.vecObstacles[i]);
	}
	for (size_t i = 0; i < m_stObstacleData.stHostLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateObstacleCorner(&m_stObstacleData.stHostLaneObstacle.vecObstacles[i]);
	}
	for (size_t i = 0; i < m_stObstacleData.stRightLaneObstacle.vecObstacles.size(); i++)
	{
		CalculateObstacleCorner(&m_stObstacleData.stRightLaneObstacle.vecObstacles[i]);
	}
}

void CPerceptionObstacles::CalculateObstacleInLane(LaneObstacle* laneobs)
{
	laneobs->bFrontObsExist = false;
	laneobs->bBackObsExist = false;
	laneobs->iFrontObsNum = 0;
	laneobs->iBackObsNum = 0;
	laneobs->iTotalObsNum = 0;
	laneobs->fFrontAverageSpeed = 100000.0;
	laneobs->fFrontAverageDis = 100000.0;
	laneobs->fBackAverageSpeed = 0.0;
	laneobs->fBackAverageDis = 100000.0;

	float fFrontNearestDis = 100000.0;
	float fBackNearesrDis = 100000.0;
	float fBackTotalSpeed = 0.0;
	float fBackTotalDis = 0.0;
	float fFrontTotalSpeed = 0.0;
	float fFrontTotalDis = 0.0;

	for (int i = 0; i < laneobs->vecObstacles.size(); i++)
	{
		laneobs->iTotalObsNum++;
		if (laneobs->vecObstacles[i].enLocalization == HOST_FRONT || laneobs->vecObstacles[i].enLocalization == LEFT_FRONT
			|| laneobs->vecObstacles[i].enLocalization == RIGHT_FRONT)
		{
			laneobs->iFrontObsNum++;
			fFrontTotalSpeed += laneobs->vecObstacles[i].fAbsSpeed;
			fFrontTotalDis += laneobs->vecObstacles[i].fDistance;
			if (laneobs->vecObstacles[i].fDistance < fFrontNearestDis)
			{
				fFrontNearestDis = laneobs->vecObstacles[i].fDistance;
				laneobs->iFrontNeraestID = i;
			}
		}
		else
		{
			laneobs->iBackObsNum++;
			fBackTotalSpeed += laneobs->vecObstacles[i].fAbsSpeed;
			fBackTotalDis += laneobs->vecObstacles[i].fDistance;
			if (laneobs->vecObstacles[i].fDistance < fBackNearesrDis)
			{
				fBackNearesrDis = laneobs->vecObstacles[i].fDistance;
				laneobs->iBackNearestID = i;
			}
		}
	}

	if (laneobs->iFrontObsNum > 0)
	{
		laneobs->bFrontObsExist = true;
		laneobs->fFrontAverageSpeed = fFrontTotalSpeed / laneobs->iFrontObsNum;
		laneobs->fFrontAverageDis = fFrontTotalDis / laneobs->iFrontObsNum;
	}
	if (laneobs->iBackObsNum > 0)
	{
		laneobs->bBackObsExist = true;
		laneobs->fBackAverageDis = fBackTotalDis / laneobs->iBackObsNum;
		laneobs->fBackAverageSpeed = fBackTotalSpeed / laneobs->iBackObsNum;
	}
}

void CPerceptionObstacles::LaneObstaclesProcess()
{
	CalculateObstacleInLane(&m_stObstacleData.stLeftLaneObstacle);
	CalculateObstacleInLane(&m_stObstacleData.stHostLaneObstacle);
	CalculateObstacleInLane(&m_stObstacleData.stRightLaneObstacle);
}

void CPerceptionObstacles::ObstacleProcess()
{
	// get the Veh real speed for later calculation
	shared_lock<shared_mutex> VehSpeedLock(gObstaclesMutex);
	m_stObstacleData.fVehSpeed = gObstacles.fVehSpeed;
	VehSpeedLock.unlock();

	m_stObstacleData.iLastCounter = m_stObstacleData.iCounter;
	m_stObstacleData.iLastTimeStamp = m_stObstacleData.iTimeStamp;
	m_stObstacleData.iTimeStamp = m_pmsgPerceptionObstacle->header.nTimeStamp;
	m_stObstacleData.iCounter = m_pmsgPerceptionObstacle->header.nCounter;

	CopyRawData();
	SafetyJudge();
	Expansion();
	RenewObstacles();
	LaneObstaclesProcess();

	if ((m_stObstacleData.iCounter - m_stObstacleData.iLastCounter) != 1 && (m_stObstacleData.iCounter - m_stObstacleData.iLastCounter) != -65534)
	{
		m_stObstacleData.iMsgLostNum++;
		if (m_stObstacleData.iMsgLostNum > MESSAGELOST_COUNTER)
		{
			m_stObstacleData.iMsgLostNum = MESSAGELOST_COUNTER;
		}
	}
	else
	{
		m_stObstacleData.iMsgLostNum--;
		if (m_stObstacleData.iMsgLostNum < 0)
		{
			m_stObstacleData.iMsgLostNum = 0;
		}
	}
	if (m_stObstacleData.iMsgLostNum >= 3)
	{
		m_stObstacleData.bMsgLost = true;
	}
	if (m_stObstacleData.iMsgLostNum == 0)
	{
		m_stObstacleData.bMsgLost = false;
	}
}


void CPerceptionObstacles::LCMHandler(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, PERCEPTION_OBSTACLES* msg)
{
	shared_lock<shared_mutex> LinesLock(gLinesMutex);
	m_stLines = gLines;
	m_stLaneGrids = gLaneGrids;
	LinesLock.unlock();

	memcpy(m_pmsgPerceptionObstacle, msg, sizeof(PERCEPTION_OBSTACLES));
	ObstacleProcess();
	unique_lock<shared_mutex> ObsLock(gObstaclesMutex);
	gObstacles = m_stObstacleData;
	ObsLock.unlock();
}

void CPerceptionObstacles::ObstacleThreadRun()
{
	while (m_bThreadRun)
	{
		m_stObstacleData.iHandlerReturn = m_pLCM->handleTimeout(500);
		if (m_stObstacleData.iHandlerReturn > 0)
		{
			m_stObstacleData.bMsgConnected = true;
			unique_lock<shared_mutex> lock(gObstaclesMutex);
			gObstacles = m_stObstacleData;
			lock.unlock();
		}
		else if (m_stObstacleData.iHandlerReturn == 0)
		{
			m_stObstacleData.bMsgConnected = false;
			m_stObstacleData.bMsgLost = true;
			m_stObstacleData.iMsgLostNum = MESSAGELOST_COUNTER*MESSAGELOST_RATIO;
			unique_lock<shared_mutex> lock(gObstaclesMutex);
			gObstacles = m_stObstacleData;
			lock.unlock();
		}
		else
		{
			m_stObstacleData.bMsgConnected = false;
			unique_lock<shared_mutex> lock(gObstaclesMutex);
			gObstacles = m_stObstacleData;
			lock.unlock();
			break;
		}
	}
}
