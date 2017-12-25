#include "NavigationPathPlanner.h"


CNavigationPathPlanner::CNavigationPathPlanner()
{
}


CNavigationPathPlanner::~CNavigationPathPlanner()
{
}

void CNavigationPathPlanner::GenerateNavigationPath()
{
	PointXY tmpPoint;
	float fShiftGridNum = float(m_iSelectedGridID);
	vector<PointXY>().swap(m_vecNavigationPath);//m_vecNavigationPath.clear();
	if (m_bIsRightShiftHalfgrid)
	{
		fShiftGridNum += 0.5;
	}
	switch (m_enGridInLane)
	{
	case LEFT_LANE:
		if (m_stLaneGrid.stLeftGrid.bExist)
		{
			for (size_t i = kSelfIdinLine; i < m_stLaneGrid.stLeftGrid.iBaseAmount; i++)
			{
				tmpPoint.x = m_stLaneGrid.stLeftGrid.stGridBase[i].dCenterX + m_stLaneGrid.stLeftGrid.stGridBase[i].dGridLength*fShiftGridNum;
				tmpPoint.y = m_stLaneGrid.stLeftGrid.stGridBase[i].dCenterY;
				m_vecNavigationPath.push_back(tmpPoint);
			}
		}
		break;
	case HOST_LANE:
		if (m_stLaneGrid.stMidGrid.bExist)
		{
			for (size_t i = kSelfIdinLine; i < m_stLaneGrid.stMidGrid.iBaseAmount; i++)
			{
				tmpPoint.x = m_stLaneGrid.stMidGrid.stGridBase[i].dCenterX + m_stLaneGrid.stMidGrid.stGridBase[i].dGridLength*fShiftGridNum;
				tmpPoint.y = m_stLaneGrid.stMidGrid.stGridBase[i].dCenterY;
				m_vecNavigationPath.push_back(tmpPoint);
			}
		}
		break;
	case RIGHT_LANE:
		if (m_stLaneGrid.stRightGrid.bExist)
		{
			for (size_t i = kSelfIdinLine; i < m_stLaneGrid.stRightGrid.iBaseAmount; i++)
			{
				tmpPoint.x = m_stLaneGrid.stRightGrid.stGridBase[i].dCenterX + m_stLaneGrid.stRightGrid.stGridBase[i].dGridLength*fShiftGridNum;
				tmpPoint.y = m_stLaneGrid.stRightGrid.stGridBase[i].dCenterY;
				m_vecNavigationPath.push_back(tmpPoint);
			}
		}
		break;
	default:
		break;
	}
}

vector<PointXY> CNavigationPathPlanner::GetNavigationPath()
{
	return m_vecNavigationPath;
}

void CNavigationPathPlanner::IDLaneKeep()
{
	int iGridID = 0;
	int iDeltaID = 0;
	int iTmpID = 0;
	int iLeftSelectID = -m_stLaneGrid.stMidGrid.iGridAmount;
	int iRightSelectID = m_stLaneGrid.stMidGrid.iGridAmount;
	m_bIsRightShiftHalfgrid = false;
	m_bIsAdjustedBackObs = true;
	m_bIsAdjustedFrontObs = true;
//get ID based on Obstacles
	if (!m_vecObstacles.empty())
	{
		for (vector<Obstacle>::iterator it = m_vecObstacles.begin(); it != m_vecObstacles.end();it++)
		{
			if (it->enLocalization == LEFT_FRONT)
			{
				iTmpID = IDLeftSide(*(it));
				if (iTmpID > iLeftSelectID)
				{
					iLeftSelectID = iTmpID;
				}
			}
			else if (it->enLocalization == RIGHT_FRONT)
			{
				iTmpID = IDRightSide(*(it));
				if (iTmpID < iRightSelectID)
				{
					iRightSelectID = iTmpID;
				}
			}
		}
	}
	if (iRightSelectID <= m_iRightForbiddenID)
	{
		iRightSelectID = m_stLaneGrid.stMidGrid.iGridAmount;
	}
	if (iLeftSelectID >= m_iLeftForbiddenID)
	{
		iLeftSelectID = -m_stLaneGrid.stMidGrid.iGridAmount;
	}
	//can not pass through,move the Obs in the next lane to Host Lane
	if (iRightSelectID-iLeftSelectID <= m_iVehicleOccupyGrid)
	{
		iRightSelectID = m_stLaneGrid.stMidGrid.iGridAmount;
		iLeftSelectID = -m_stLaneGrid.stMidGrid.iGridAmount;
	}
	//Obs in the next lane don't cross lane
	if (iRightSelectID == m_stLaneGrid.stMidGrid.iGridAmount && iLeftSelectID == -m_stLaneGrid.stMidGrid.iGridAmount)
	{
		m_bIsAdjustedFrontObs = false;
	}
	//calculate the center grid ID
	if ((iLeftSelectID + iRightSelectID) % 2 != 0)
	{
		m_bIsRightShiftHalfgrid = true;
		iGridID = (iLeftSelectID + iRightSelectID - 1) / 2;
	}
	else
	{
		iGridID = (iLeftSelectID + iRightSelectID) / 2;
	}
//lane change steady
	iDeltaID = iGridID - m_iVehicleCurrentGridID;
	if (!m_bIsAdjustedFrontObs && !m_bIsAdjustedBackObs)
	{
		if (iDeltaID > m_iGridShiftNumLaneChange)
		{
			iGridID = m_iVehicleCurrentGridID + m_iGridShiftNumLaneChange;
		}
		else if (iDeltaID < -m_iGridShiftNumLaneChange)
		{
			iGridID = m_iVehicleCurrentGridID - m_iGridShiftNumLaneChange;
		}
	}
//vehicle safety
	iDeltaID = iGridID - m_iVehicleCurrentGridID;
	if (iDeltaID > m_iGridShiftLimit)
	{
		iGridID = m_iVehicleCurrentGridID + m_iGridShiftLimit;
	}
	else if (iDeltaID < -m_iGridShiftLimit)
	{
		iGridID = m_iVehicleCurrentGridID - m_iGridShiftLimit;
	}
//grid ID limit for lane keep
	if (!m_bIsAdjustedBackObs)
	{
		if (iGridID >= m_iRightMaxIDLaneKeep)
		{
			iGridID = m_iRightMaxIDLaneKeep;
			m_bIsRightShiftHalfgrid = false;
		}
		if (iGridID < m_iLeftMaxIDLaneKeep)
		{
			iGridID = m_iLeftMaxIDLaneKeep;
			m_bIsRightShiftHalfgrid = false;
		}
	}
	else
	{
		if (iGridID >= m_iRightMaxIDDangerous)
		{
			iGridID = m_iRightMaxIDDangerous;
			m_bIsRightShiftHalfgrid = false;
		}
		if (iGridID < m_iLeftMaxIDDangerous)
		{
			iGridID = m_iLeftMaxIDDangerous;
			m_bIsRightShiftHalfgrid = false;
		}
	}
	m_enGridInLane = HOST_LANE;
	m_iSelectedGridID = iGridID;
}

void CNavigationPathPlanner::IDLaneLeftChange()
{
	int iGridID = m_iVehicleCurrentGridID - m_iGridShiftNumLaneChange;
	m_enGridInLane = HOST_LANE;
	if (iGridID < -m_stLaneGrid.stMidGrid.iGridAmount)
	{
		iGridID += (m_stLaneGrid.stMidGrid.iGridAmount + m_stLaneGrid.stLeftGrid.iGridAmount);
		if (iGridID < 0)
		{
			iGridID = 0;
		}
		m_enGridInLane = LEFT_LANE;
	}
	m_bIsRightShiftHalfgrid = false;
	m_iSelectedGridID = iGridID;
}

void CNavigationPathPlanner::IDLaneRightChange()
{
	int iGridID = m_iVehicleCurrentGridID + m_iGridShiftNumLaneChange;
	m_enGridInLane = HOST_LANE;
	if (iGridID > m_stLaneGrid.stMidGrid.iGridAmount)
	{
		iGridID -= (m_stLaneGrid.stMidGrid.iGridAmount + m_stLaneGrid.stRightGrid.iGridAmount);
		if (iGridID > 0)
		{
			iGridID = 0;
		}
		m_enGridInLane = RIGHT_LANE;
	}
	m_bIsRightShiftHalfgrid = false;
	m_iSelectedGridID = iGridID;
}

//Get the left grid ID in the mid lane of the Vehicle in the LeftLane
int CNavigationPathPlanner::IDLeftSide(Obstacle obs)
{
	int iGridID = -m_stLaneGrid.stMidGrid.iGridAmount;
	int iTmpGridID = 0;
	int iBaseID = 0;
	Base tmp_base;

	//Right front corner
	iBaseID = obs.iFrontBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stMidGrid.iBaseAmount)
	{
		tmp_base = m_stLaneGrid.stMidGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stRightFrontCorner.x, tmp_base);
		if (iTmpGridID < iGridID)
		{
			iGridID = iTmpGridID;
		}
	}

	//Right back corner
	iBaseID = obs.iBackBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stMidGrid.iBaseAmount)
	{
		tmp_base = m_stLaneGrid.stMidGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stRightBackCorner.x, tmp_base);
		if (iTmpGridID < iGridID)
		{
			iGridID = iTmpGridID;
		}
	}
	return iGridID;
}

//Get the right grid ID in the mid lane of the Vehicle in the RightLane
int CNavigationPathPlanner::IDRightSide(Obstacle obs)
{
	int iGridID = m_stLaneGrid.stMidGrid.iGridAmount;
	int iTmpGridID = 0;
	int iBaseID = 0;
	Base tmp_base;

	//Left front corner
	iBaseID = obs.iFrontBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stMidGrid.iBaseAmount)
	{
		tmp_base = m_stLaneGrid.stMidGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stLeftFrontCorner.x, tmp_base);
		if (iTmpGridID < iGridID)
		{
			iGridID = iTmpGridID;
		}
	}

	//Left back corner
	iBaseID = obs.iBackBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stMidGrid.iBaseAmount)
	{
		tmp_base = m_stLaneGrid.stMidGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stLeftBackCorner.x, tmp_base);
		if (iTmpGridID < iGridID)
		{
			iGridID = iTmpGridID;
		}
	}
	return iGridID;
}

//match the x to the grid ID
int CNavigationPathPlanner::MatchXInGrid(float x, Base base)
{
	int iGridID = 0;
	if (x >= base.dRightX || x <= base.dLeftX)
	{
		iGridID = base.iGridAmount;
		if (x <= base.dLeftX)
		{
			iGridID = -base.iGridAmount;
		}
	}
	else
	{
		iGridID = (int)round((x - base.dCenterX) / base.dGridLength);
	}
	return iGridID;
}

//get the vehicle grid ID in the host lane
void CNavigationPathPlanner::GenerateVehicleGridID()
{
	if (m_stLaneGrid.stMidGrid.bExist)
	{
		m_iVehicleCurrentGridID = MatchXInGrid(0, m_stLaneGrid.stMidGrid.stGridBase[kBackInterestArrayLength]);
	}
	else
	{
		m_iVehicleCurrentGridID = 0;
	}
}

void CNavigationPathPlanner::GenerateMaxIDLaneKeep()
{
	float kVehicleWidth = 1.8f;
	if (m_stLaneGrid.stMidGrid.bExist)
	{
		int tmpGrid = (int)round(kVehicleWidth / 2 / m_stLaneGrid.stMidGrid.stGridBase[kBackInterestArrayLength].dGridLength);
		m_iVehicleOccupyGrid = tmpGrid * 2;
		m_iRightMaxIDLaneKeep = m_stLaneGrid.stMidGrid.iGridAmount - tmpGrid;
		if (m_iRightMaxIDLaneKeep < 0)
		{
			m_iRightMaxIDLaneKeep = 0;
		}
		m_iLeftMaxIDLaneKeep = -m_iRightMaxIDLaneKeep;
		m_iRightForbiddenID = 2 * tmpGrid - m_stLaneGrid.stMidGrid.iGridAmount;
		if (m_iRightMaxIDLaneKeep > m_stLaneGrid.stMidGrid.iGridAmount)
		{
			m_iRightMaxIDLaneKeep = m_stLaneGrid.stMidGrid.iGridAmount;
		}
		m_iLeftForbiddenID = -m_iRightForbiddenID;
	}
	else
	{
		m_iLeftMaxIDLaneKeep = 0;
		m_iRightMaxIDLaneKeep = 0;
	}
}

void CNavigationPathPlanner::GenerateMaxIDDangerous()
{
	int iLeftExpandGrid = 0;
	int iRightExpandGrid = 0;
	float fLeftLaneFreespace = GetLeftLaneFreespace();
	float fRightLaneFreespace = GetRightLaneFreespace();
	iLeftExpandGrid = (int)floor(fLeftLaneFreespace / m_stLaneGrid.stMidGrid.stGridBase[kSelfIdinLine].dGridLength);
	m_iLeftMaxIDDangerous = m_iLeftMaxIDLaneKeep - iLeftExpandGrid;
	if (m_iLeftMaxIDDangerous < -m_stLaneGrid.stMidGrid.iGridAmount)
	{
		m_iLeftMaxIDDangerous = -m_stLaneGrid.stMidGrid.iGridAmount;
	}
	iRightExpandGrid = (int)floor(fRightLaneFreespace / m_stLaneGrid.stMidGrid.stGridBase[kSelfIdinLine].dGridLength);
	m_iRightMaxIDDangerous = m_iRightMaxIDLaneKeep + iRightExpandGrid;
	if (m_iRightMaxIDDangerous > m_stLaneGrid.stMidGrid.iGridAmount)
	{
		m_iRightMaxIDDangerous = m_stLaneGrid.stMidGrid.iGridAmount;
	}
}

//Get the Left lane Freespace width based on GRID
float CNavigationPathPlanner::GetLeftLaneFreespace()
{
	float fFreeLength = 0.0f;
	int iTmpID = 0;
	int iRightID = -m_stLaneGrid.stLeftGrid.iGridAmount;
	int iMaxID = m_stLaneGrid.stLeftGrid.iGridAmount;
	if (m_stLaneGrid.stLeftGrid.bExist)
	{
		if (!m_vecObstacles.empty())
		{
			for (vector<Obstacle>::iterator it = m_vecObstacles.begin(); it != m_vecObstacles.end(); it++)
			{
				if (it->enLocalization == LEFT_FRONT || it->enLocalization == LEFT_BACK)
				{
					iTmpID = RightIDLeftLane(*(it));
					if (iTmpID > iRightID)
					{
						iRightID = iTmpID;
					}
				}
			}
		}
		fFreeLength = (iMaxID - iRightID)*m_stLaneGrid.stLeftGrid.stGridBase[kSelfIdinLine].dGridLength;
	}
	return fFreeLength;
}

//Get the Right Lane Freespace width based on GRID
float CNavigationPathPlanner::GetRightLaneFreespace()
{
	float fFreeLength = 0.0f;
	int iTmpID = 0;
	int iLeftID = m_stLaneGrid.stRightGrid.iGridAmount;
	int iMinID = -m_stLaneGrid.stRightGrid.iGridAmount;
	if (m_stLaneGrid.stRightGrid.bExist)
	{
		if (!m_vecObstacles.empty())
		{
			for (vector<Obstacle>::iterator it = m_vecObstacles.begin(); it != m_vecObstacles.end(); it++)
			{
				if (it->enLocalization == RIGHT_FRONT || it->enLocalization == RIGHT_BACK)
				{
					iTmpID = LeftIDRightLane(*(it));
					if (iTmpID > iLeftID)
					{
						iLeftID = iTmpID;
					}
				}
			}
		}
		fFreeLength = (iLeftID - iMinID)*m_stLaneGrid.stLeftGrid.stGridBase[kSelfIdinLine].dGridLength;
	}
	return fFreeLength;
}

//Get the Max grid ID of the Obstacle in the Right Lanes
int CNavigationPathPlanner::LeftIDRightLane(Obstacle obs)
{
	int iGridID = m_stLaneGrid.stRightGrid.iGridAmount;
	int iTmpGridID = 0;
	int iBaseID = 0;
	Base tmp_base;

	//left front corner
	iBaseID = obs.iFrontBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stRightGrid.iBaseAmount)
	{
		tmp_base = m_stLaneGrid.stRightGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stLeftFrontCorner.x, tmp_base);
		if (iTmpGridID < iGridID)
		{
			iGridID = iTmpGridID;
		}
	}

	//left back corner
	iBaseID = obs.iBackBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stRightGrid.iBaseAmount)
	{
		tmp_base = m_stLaneGrid.stRightGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stLeftBackCorner.x, tmp_base);
		if (iTmpGridID < iGridID)
		{
			iGridID = iTmpGridID;
		}
	}
	return iGridID;
}

//Get the Max grid ID of the Obstacle in the Left Lanes
int CNavigationPathPlanner::RightIDLeftLane(Obstacle obs)
{
	int iGridID = -m_stLaneGrid.stLeftGrid.iGridAmount;
	int iTmpGridID = 0;
//Right Front Corner Matched ID
	int iBaseID = obs.iFrontBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stLeftGrid.iBaseAmount)
	{
		Base tmpBase = m_stLaneGrid.stLeftGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stRightFrontCorner.x, tmpBase);
		if (iTmpGridID > iGridID)
		{
			iGridID = iTmpGridID;
		}
	}
//Right Back Corner Matched ID
	iBaseID = obs.iBackBaseID;
	if (iBaseID >= 0 && iBaseID <= m_stLaneGrid.stLeftGrid.iBaseAmount)
	{
		Base tmpBase = m_stLaneGrid.stLeftGrid.stGridBase[iBaseID];
		iTmpGridID = MatchXInGrid(obs.stRightBackCorner.x, tmpBase);
		if (iTmpGridID > iGridID)
		{
			iGridID = iTmpGridID;
		}
	}
	return iGridID;
}

//the grid change has the limit relate to the vehicle speed 
//For Vehicle Safety
void CNavigationPathPlanner::GenerateGridShiftLimit()
{
	int iSpeedLevel = (int)floor(fabs(m_fVehicleSpeed / 10));
	if (iSpeedLevel >= 12)
	{
		m_iGridShiftLimit = 4;
	}
	else
	{
		m_iGridShiftLimit = 16 - iSpeedLevel;
	}
}

//the grid change has the limit relate to the vehicle speed
//For Lane Change
void CNavigationPathPlanner::GenerateGridShiftNumLaneChange()
{
	int iSpeedLevel = (int)floor(fabs(m_fVehicleSpeed / 10));
	if (iSpeedLevel >= 12)
	{
		m_iGridShiftNumLaneChange = 2;
	}
	else
	{
		m_iGridShiftNumLaneChange = (int)((iSpeedLevel - 12)*(iSpeedLevel - 12) / 12 + 2);
	}
}

void CNavigationPathPlanner::GetLaneGrid(LaneGrid lanegrid)
{
	m_stLaneGrid = lanegrid;
	GenerateVehicleGridID();//get current grid ID
}

void CNavigationPathPlanner::GetObstacles(vector<Obstacle> obstacles)
{
	vector<Obstacle>().swap(m_vecObstacles);// m_vecObstacles.clear();
	m_vecObstacles = obstacles;
	GenerateMaxIDLaneKeep();//
	GenerateMaxIDDangerous();
}

void CNavigationPathPlanner::GetVehicleSpeed(float vehSpeed)
{
	m_fVehicleSpeed = vehSpeed;
	GenerateGridShiftLimit();
	GenerateGridShiftNumLaneChange();
}

vector<PointXY> CNavigationPathPlanner::PathInterpolate(vector<PointXY> PathData)
{
	vector<PointXY> vecResult;
	float g[4][4], g_1[4][4], g_2[4][4];
	for (size_t j = 0; j < 4; j++)
	{
		float t = j / 4.0f;
		g[0][j] = (-t*t*t + 3 * t*t - 3 * t + 1) / 6;
		g[1][j] = (3 * t*t*t - 6 * t*t + 4) / 6;
		g[2][j] = (-3 * t*t*t + 3 * t*t + 3 * t + 1) / 6;
		g[3][j] = t*t*t / 6;

		g_1[0][j] = (-t*t + 2 * t - 1) / 2;
		g_1[1][j] = (3 * t*t - 4 * t) / 2;
		g_1[2][j] = (-3 * t*t + 2 * t + 1) / 2;
		g_1[3][j] = t*t / 2;

		g_2[0][j] = -t + 1;
		g_2[1][j] = 3 * t - 2;
		g_2[2][j] = -3 * t + 1;
		g_2[3][j] = t;
	}
	PointXY tmpPoint;
	for (size_t j = 0; j < 4; j++)
	{
		tmpPoint.x = g[0][j] * PathData[0].x + g[1][j] * PathData[0].x + g[2][j] * PathData[0].x + g[3][j] * PathData[1].x;
		tmpPoint.y = g[0][j] * PathData[0].y + g[1][j] * PathData[0].y + g[2][j] * PathData[0].y + g[3][j] * PathData[1].y;
		vecResult.push_back(tmpPoint);
	}
	for (size_t j = 0; j < 4; j++)
	{
		tmpPoint.x = g[0][j] * PathData[0].x + g[1][j] * PathData[0].x + g[2][j] * PathData[1].x + g[3][j] * PathData[2].x;
		tmpPoint.y = g[0][j] * PathData[0].y + g[1][j] * PathData[0].y + g[2][j] * PathData[1].y + g[3][j] * PathData[2].y;
		vecResult.push_back(tmpPoint);
	}
	for (size_t i = 0; i < (PathData.size() - 3); i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			tmpPoint.x = g[0][j] * PathData[i].x + g[1][j] * PathData[(i + 1)].x + g[2][j] * PathData[(i + 2)].x + g[3][j] * PathData[(i + 3)].x;
			tmpPoint.y = g[0][j] * PathData[i].y + g[1][j] * PathData[(i + 1)].y + g[2][j] * PathData[(i + 2)].y + g[3][j] * PathData[(i + 3)].y;
			vecResult.push_back(tmpPoint);
		}
	}
	int iEndNum = PathData.size();
	for (size_t j = 0; j < 4; j++)
	{
		tmpPoint.x = g[0][j] * PathData[iEndNum - 3].x + g[1][j] * PathData[iEndNum - 2].x + g[2][j] * PathData[iEndNum - 1].x + g[3][j] * PathData[iEndNum - 1].x;
		tmpPoint.y = g[0][j] * PathData[iEndNum - 3].y + g[1][j] * PathData[iEndNum - 2].y + g[2][j] * PathData[iEndNum - 1].y + g[3][j] * PathData[iEndNum - 1].y;
		vecResult.push_back(tmpPoint);
	}
	for (size_t j = 0; j < 4; j++)
	{
		tmpPoint.x = g[0][j] * PathData[iEndNum - 2].x + g[1][j] * PathData[iEndNum - 1].x + g[2][j] * PathData[iEndNum - 1].x + g[3][j] * PathData[iEndNum - 1].x;
		tmpPoint.y = g[0][j] * PathData[iEndNum - 2].y + g[1][j] * PathData[iEndNum - 1].y + g[2][j] * PathData[iEndNum - 1].y + g[3][j] * PathData[iEndNum - 1].y;
		vecResult.push_back(tmpPoint);
	}
	return vecResult;
}

double CNavigationPathPlanner::PursuitByDeltaX(double deltax, double dis)
{
	if (deltax > dis)
	{
		deltax = dis;
	}
	else if (deltax < -dis)
	{
		deltax = -dis;
	}
	return (atan2(2 * WHEELBASE*deltax, dis*dis)*RADIAN_TO_DEGREE);
}

vector<PointXY> CNavigationPathPlanner::LocalPathPlan(vector<PointXY> PathData, int PreviewDis)
{
	vector<PointXY> vecResultLocalPath;
	PointXY VehPoint;
	PointXY ProjectPoint;
	PointXY CenterPoint;
	PointXY PreviewPoint;
	size_t iMinIndex = 0;

	double dMinDis = 10000000.0;
	double dtmpDis = 10000000.0;
	double dFrontWheelAngle = 0.0;
	double dRadius = 0.0;

	size_t i = 0;
//start point
	VehPoint.x = 0; VehPoint.y = 0; VehPoint.theta = 0.0;
	vecResultLocalPath.push_back(VehPoint);
	while (vecResultLocalPath.size() < 50)
	{
		//find the project point
		double dMinDis = 10000000.0;
		for (i = iMinIndex; i < GetMin(iMinIndex+5,(size_t)(PathData.size())); i++)
		{
			double dTmpDis = Distance(VehPoint, PathData[i]);
			if (dTmpDis < dMinDis)
			{
				dMinDis = dTmpDis;
				iMinIndex = i;
			}
		}
		ProjectPoint = PathData[iMinIndex];
		if (iMinIndex >= PathData.size() - 1)
		{
			break;
		}
		//find the preview point
		double dSumDis = 0.0;
		for (i = iMinIndex; i < (PathData.size() - 1); i++)
		{
			dSumDis += Distance(PathData[i], PathData[i + 1]);
			if (dSumDis >= PreviewDis)
			{
				PreviewPoint = PathData[i + 1];
				break;
			}
		}
		if (i == (PathData.size()-1))
		{
			PreviewPoint = PathData[i];
		}
		//the front wheel angle
		PreviewPoint = Global2Local(PreviewPoint, VehPoint);
		double dDis = Distance(PreviewPoint.x, PreviewPoint.y);
		if (dDis > PreviewDis)
		{
			PreviewPoint.x = PreviewPoint.x*PreviewDis / dDis;
			PreviewPoint.y = PreviewPoint.y*PreviewDis / dDis;
			dDis = PreviewDis;
		}
		if (PreviewPoint.y < 0)
		{
			if (PreviewPoint.x > 0)
			{
				dFrontWheelAngle = FRONTWHEELANGLELIMIT;
			}
			else
			{
				dFrontWheelAngle = -FRONTWHEELANGLELIMIT;
			}
		}
		else
		{
			dFrontWheelAngle = PursuitByDeltaX(PreviewPoint.x, dDis);
		}

		if (dFrontWheelAngle > FRONTWHEELANGLELIMIT)
		{
			dFrontWheelAngle = FRONTWHEELANGLELIMIT;
		}
		else if (dFrontWheelAngle < -FRONTWHEELANGLELIMIT)
		{
			dFrontWheelAngle = -FRONTWHEELANGLELIMIT;
		}

		if (fabs(dFrontWheelAngle)>0.03)
		{
			dRadius = WHEELBASE / tan(dFrontWheelAngle*DEGREE_TO_RADIAN);
			CenterPoint.x = VehPoint.x + dRadius*cos(VehPoint.theta);
			CenterPoint.y = VehPoint.y - dRadius*sin(VehPoint.theta);
			VehPoint.theta += 1.0 / dRadius;
			VehPoint.x = CenterPoint.x - dRadius*cos(VehPoint.theta);
			VehPoint.y = CenterPoint.y + dRadius*sin(VehPoint.theta);
		}
		else
		{
			VehPoint.x = VehPoint.x + sin(VehPoint.theta);
			VehPoint.y = VehPoint.y + cos(VehPoint.theta);
		}
		vecResultLocalPath.push_back(VehPoint);
	}


	return vecResultLocalPath;
}