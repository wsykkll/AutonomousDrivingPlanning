#include "PerceptionLines.h"
LineData gLines;
LaneGrid gLaneGrids;
shared_mutex gLinesMutex;

CPerceptionLines::CPerceptionLines()
{
	m_bThreadRun = true;
}


CPerceptionLines::~CPerceptionLines()
{
}


bool CPerceptionLines::InitializeLCM()
{
	m_iLastRecvTime = timestamp_now();
	m_stLinedata.iLastTimeStamp = m_iLastRecvTime;

	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
	if (!m_pLCM->good())
	{
		return false;
	}
	return true;
}

void CPerceptionLines::LineProcess()
{
//local value for use
	int i = 0;
	int icounter = 0;
	double dDis = 0.0;
	double dTotalDis = 0.0;
	PointXY tmpPoint;
//line's length must long enough
	if (m_stLinedata.stLeft.bExist)
	{
		if (m_stLinedata.stLeft.vecLinePoints.size()<MIN_LINELENGTH + kBackInterestArrayLength)
		{
			m_stLinedata.stLeft.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stLeft.vecLinePoints);// m_stLinedata.stLeft.vecLinePoints.clear();
		}
	}
	if (m_stLinedata.stRight.bExist)
	{
		if (m_stLinedata.stRight.vecLinePoints.size() < MIN_LINELENGTH + kBackInterestArrayLength)
		{
			m_stLinedata.stRight.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stRight.vecLinePoints);//m_stLinedata.stRight.vecLinePoints.clear();
		}
	}
	if (m_stLinedata.stLeftLeft.bExist)
	{
		if (m_stLinedata.stLeftLeft.vecLinePoints.size() < MIN_LINELENGTH + kBackInterestArrayLength)
		{
			m_stLinedata.stLeftLeft.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stLeftLeft.vecLinePoints);//m_stLinedata.stLeftLeft.vecLinePoints.clear();
		}
	}
	if (m_stLinedata.stRightRight.bExist)
	{
		if (m_stLinedata.stRightRight.vecLinePoints.size() < MIN_LINELENGTH + kBackInterestArrayLength)
		{
			m_stLinedata.stRightRight.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stRightRight.vecLinePoints);//m_stLinedata.stRightRight.vecLinePoints.clear();
		}
	}
//lane middle line
	//host lane
	m_stLinedata.bMidLaneExist = false;
	if (m_stLinedata.stLeft.bExist && m_stLinedata.stRight.bExist)//both left and right line exist
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = fabs(m_stLinedata.stRight.vecLinePoints[i].x - m_stLinedata.stLeft.vecLinePoints[i].x);
			if (dDis > MAX_LANEWIDTH || dDis < MIN_LANEWIDTH)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.stLeft.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stLeft.vecLinePoints);//m_stLinedata.stLeft.vecLinePoints.clear();
			m_stLinedata.stRight.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stRight.vecLinePoints);//m_stLinedata.stRight.vecLinePoints.clear();
		}
		else
		{
			m_stLinedata.bMidLaneExist = true;
			m_stLinedata.stHostMiddle.bExist = true;
			icounter = (m_stLinedata.stRight.vecLinePoints.size() < m_stLinedata.stLeft.vecLinePoints.size()) ? 
				m_stLinedata.stRight.vecLinePoints.size() : m_stLinedata.stLeft.vecLinePoints.size();
			m_stLinedata.stHostMiddle.iArrayLength = icounter;
			for (i = 0; i < icounter; i++)
			{
				tmpPoint.x = (m_stLinedata.stLeft.vecLinePoints[i].x + m_stLinedata.stRight.vecLinePoints[i].x) / 2;
				tmpPoint.y = (m_stLinedata.stLeft.vecLinePoints[i].y + m_stLinedata.stRight.vecLinePoints[i].y) / 2;
				m_stLinedata.stHostMiddle.vecLinePoints.push_back(tmpPoint);
			}
		}
	}
	//left lane
	m_stLinedata.bLeftLaneExist = false;
	if (m_stLinedata.stLeft.bExist && m_stLinedata.stLeftLeft.bExist)//both left and leftleft line exist
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = fabs(m_stLinedata.stLeft.vecLinePoints[i].x - m_stLinedata.stLeftLeft.vecLinePoints[i].x);
			if (dDis > MAX_LANEWIDTH || dDis < MIN_LANEWIDTH)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.stLeftLeft.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stLeftLeft.vecLinePoints);//m_stLinedata.stLeftLeft.vecLinePoints.clear();
		}
		else
		{
			m_stLinedata.bLeftLaneExist = true;
			m_stLinedata.stLeftMiddle.bExist = true;
			icounter = (m_stLinedata.stLeftLeft.vecLinePoints.size() < m_stLinedata.stLeft.vecLinePoints.size()) ?
				m_stLinedata.stLeftLeft.vecLinePoints.size() : m_stLinedata.stLeft.vecLinePoints.size();
			m_stLinedata.stLeftMiddle.iArrayLength = icounter;
			for (i = 0; i < icounter; i++)
			{
				tmpPoint.x = (m_stLinedata.stLeft.vecLinePoints[i].x + m_stLinedata.stLeftLeft.vecLinePoints[i].x) / 2;
				tmpPoint.y = (m_stLinedata.stLeft.vecLinePoints[i].y + m_stLinedata.stLeftLeft.vecLinePoints[i].y) / 2;
				m_stLinedata.stLeftMiddle.vecLinePoints.push_back(tmpPoint);
			}
		}
	}
	//right lane
	m_stLinedata.bRightLaneExist = false;
	if (m_stLinedata.stRight.bExist && m_stLinedata.stRightRight.bExist)//both right and rightright line exist
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = fabs(m_stLinedata.stRightRight.vecLinePoints[i].x - m_stLinedata.stRight.vecLinePoints[i].x);
			if (dDis > MAX_LANEWIDTH || dDis < MIN_LANEWIDTH)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.stRightRight.bExist = false;
			vector<PointXY>().swap(m_stLinedata.stRightRight.vecLinePoints); //m_stLinedata.stRightRight.vecLinePoints.clear();
		}
		else
		{
			m_stLinedata.bRightLaneExist = true;
			m_stLinedata.stRightMiddle.bExist = true;
			icounter = (m_stLinedata.stRightRight.vecLinePoints.size() < m_stLinedata.stRight.vecLinePoints.size()) ?
				m_stLinedata.stRightRight.vecLinePoints.size() : m_stLinedata.stRight.vecLinePoints.size();
			m_stLinedata.stRightMiddle.iArrayLength = icounter;
			for (i = 0; i < icounter; i++)
			{
				tmpPoint.x = (m_stLinedata.stRight.vecLinePoints[i].x + m_stLinedata.stRightRight.vecLinePoints[i].x) / 2;
				tmpPoint.y = (m_stLinedata.stRight.vecLinePoints[i].y + m_stLinedata.stRightRight.vecLinePoints[i].y) / 2;
				m_stLinedata.stRightMiddle.vecLinePoints.push_back(tmpPoint);
			}
		}
	}
//Distance to left and right line
	//left line
	vector<float>().swap(m_vecDis2LeftLine);// m_vecDis2LeftLine.clear();
	if (m_stLinedata.stLeft.bExist)
	{
		dTotalDis = 0.0;
		int iLength = m_stLinedata.stLeft.vecLinePoints.size() - kBackInterestArrayLength;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + GetMin(iLength,AVERAGE_NUM); i++)
		{
			dTotalDis += fabs(m_stLinedata.stLeft.vecLinePoints[i].x);
		}
		m_stLinedata.fDis2LeftLine = dTotalDis / GetMin(iLength, AVERAGE_NUM);
		if (m_listDis2LeftLine.size() >= HISTORY_NUM)
		{
			m_listDis2LeftLine.pop_front();
		}
		m_listDis2LeftLine.push_back(m_stLinedata.fDis2LeftLine);
		m_vecDis2LeftLine = Filter(m_listDis2LeftLine, kDistance2LineThreshold);
		m_stLinedata.fDis2LeftLine = m_vecDis2LeftLine.back();
	}
	else
	{
		m_stLinedata.fDis2LeftLine = LANEWIDTH / 2;
	}
	if (m_stLinedata.fDis2LeftLine > LANEWIDTH)
	{
		m_stLinedata.fDis2LeftLine -= LANEWIDTH;
	}
	//right line
	vector<float>().swap(m_vecDis2RightLine);// m_vecDis2RightLine.clear();
	if (m_stLinedata.stRight.bExist)
	{
		dTotalDis = 0.0;
		int iLength = m_stLinedata.stRight.vecLinePoints.size() - kBackInterestArrayLength;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + GetMin(iLength, AVERAGE_NUM); i++)
		{
			dTotalDis += fabs(m_stLinedata.stRight.vecLinePoints[i].x);
		}
		m_stLinedata.fDis2RightLine = dTotalDis / GetMin(iLength, AVERAGE_NUM);
		if (m_listDis2RightLine.size() >= HISTORY_NUM)
		{
			m_listDis2RightLine.pop_front();
		}
		m_listDis2RightLine.push_back(m_stLinedata.fDis2RightLine);
		m_vecDis2RightLine = Filter(m_listDis2RightLine, kDistance2LineThreshold);
		m_stLinedata.fDis2RightLine = m_vecDis2RightLine.back();
	}
	else
	{
		m_stLinedata.fDis2RightLine = LANEWIDTH / 2;
	}
	if (m_stLinedata.fDis2RightLine > LANEWIDTH)
	{
		m_stLinedata.fDis2RightLine -= LANEWIDTH;
	}
}

void CPerceptionLines::LaneGridProcess()
{
	if (m_stLinedata.bMidLaneExist)
	{
		m_stLanegrid.stMidGrid.bExist = true;
		m_stLanegrid.stMidGrid.iGridAmount = round((m_stLinedata.stRight.vecLinePoints[kBackInterestArrayLength].x - 
			m_stLinedata.stLeft.vecLinePoints[kBackInterestArrayLength].x) / (2 * kGridLength));
		m_stLanegrid.stMidGrid.iBaseAmount = (m_stLinedata.stHostMiddle.vecLinePoints.size() < MAX_BASE_AMOUNT)
			? m_stLinedata.stHostMiddle.vecLinePoints.size() : MAX_BASE_AMOUNT;
		m_stLanegrid.stMidGrid.iBackBaseMaxAmount = kBackInterestArrayLength;
		m_stLanegrid.stMidGrid.iFrontBaseMaxAmount = m_stLanegrid.stMidGrid.iBaseAmount - kBackInterestArrayLength;
		for (unsigned int i = 0; i < m_stLanegrid.stMidGrid.iBaseAmount; i++)
		{
			m_stLanegrid.stMidGrid.stGridBase[i].iGridAmount = m_stLanegrid.stMidGrid.iGridAmount;
			m_stLanegrid.stMidGrid.stGridBase[i].dLeftX = m_stLinedata.stLeft.vecLinePoints[i].x;
			m_stLanegrid.stMidGrid.stGridBase[i].dRightX = m_stLinedata.stRight.vecLinePoints[i].x;
			m_stLanegrid.stMidGrid.stGridBase[i].dCenterX = (m_stLinedata.stLeft.vecLinePoints[i].x + m_stLinedata.stRight.vecLinePoints[i].x) / 2;
			m_stLanegrid.stMidGrid.stGridBase[i].dCenterY = (m_stLinedata.stLeft.vecLinePoints[i].y + m_stLinedata.stRight.vecLinePoints[i].y) / 2;
			m_stLanegrid.stMidGrid.stGridBase[i].dGridLength = fabs(m_stLinedata.stLeft.vecLinePoints[i].x - m_stLinedata.stRight.vecLinePoints[i].x) 
				/(2*m_stLanegrid.stMidGrid.iGridAmount);
		}
	}
	else
	{
		m_stLanegrid.stMidGrid.bExist = false;
	}
	if (m_stLinedata.bLeftLaneExist)
	{
		m_stLanegrid.stLeftGrid.bExist = true;
		m_stLanegrid.stLeftGrid.iGridAmount = round((m_stLinedata.stLeft.vecLinePoints[kBackInterestArrayLength].x -
			m_stLinedata.stLeftLeft.vecLinePoints[kBackInterestArrayLength].x) / (2 * kGridLength));
		m_stLanegrid.stLeftGrid.iBaseAmount = (m_stLinedata.stLeftMiddle.vecLinePoints.size() < MAX_BASE_AMOUNT)
			? m_stLinedata.stLeftMiddle.vecLinePoints.size() : MAX_BASE_AMOUNT;
		m_stLanegrid.stLeftGrid.iBackBaseMaxAmount = kBackInterestArrayLength;
		m_stLanegrid.stLeftGrid.iFrontBaseMaxAmount = m_stLanegrid.stLeftGrid.iBaseAmount - kBackInterestArrayLength;
		for (unsigned int i = 0; i < m_stLanegrid.stLeftGrid.iBaseAmount; i++)
		{
			m_stLanegrid.stLeftGrid.stGridBase[i].iGridAmount = m_stLanegrid.stLeftGrid.iGridAmount;
			m_stLanegrid.stLeftGrid.stGridBase[i].dLeftX = m_stLinedata.stLeftLeft.vecLinePoints[i].x;
			m_stLanegrid.stLeftGrid.stGridBase[i].dRightX = m_stLinedata.stLeft.vecLinePoints[i].x;
			m_stLanegrid.stLeftGrid.stGridBase[i].dCenterX = (m_stLinedata.stLeftLeft.vecLinePoints[i].x + m_stLinedata.stLeft.vecLinePoints[i].x) / 2;
			m_stLanegrid.stLeftGrid.stGridBase[i].dCenterY = (m_stLinedata.stLeftLeft.vecLinePoints[i].y + m_stLinedata.stLeft.vecLinePoints[i].y) / 2;
			m_stLanegrid.stLeftGrid.stGridBase[i].dGridLength = fabs(m_stLinedata.stLeft.vecLinePoints[i].x - m_stLinedata.stLeftLeft.vecLinePoints[i].x)
				/ (2 * m_stLanegrid.stLeftGrid.iGridAmount);
		}
	}
	else
	{
		m_stLanegrid.stLeftGrid.bExist = false;
	}
	if (m_stLinedata.bRightLaneExist)
	{
		m_stLanegrid.stRightGrid.bExist = true;
		m_stLanegrid.stRightGrid.iGridAmount = round((m_stLinedata.stRightRight.vecLinePoints[kBackInterestArrayLength].x -
			m_stLinedata.stRight.vecLinePoints[kBackInterestArrayLength].x) / (2 * kGridLength));
		m_stLanegrid.stRightGrid.iBaseAmount = (m_stLinedata.stRightMiddle.vecLinePoints.size() < MAX_BASE_AMOUNT)
			? m_stLinedata.stRightMiddle.vecLinePoints.size() : MAX_BASE_AMOUNT;
		m_stLanegrid.stRightGrid.iBackBaseMaxAmount = kBackInterestArrayLength;
		m_stLanegrid.stRightGrid.iFrontBaseMaxAmount = m_stLanegrid.stRightGrid.iBaseAmount - kBackInterestArrayLength;
		for (unsigned int i = 0; i < m_stLanegrid.stRightGrid.iBaseAmount; i++)
		{
			m_stLanegrid.stRightGrid.stGridBase[i].iGridAmount = m_stLanegrid.stRightGrid.iGridAmount;
			m_stLanegrid.stRightGrid.stGridBase[i].dLeftX = m_stLinedata.stRight.vecLinePoints[i].x;
			m_stLanegrid.stRightGrid.stGridBase[i].dRightX = m_stLinedata.stRightRight.vecLinePoints[i].x;
			m_stLanegrid.stRightGrid.stGridBase[i].dCenterX = (m_stLinedata.stRight.vecLinePoints[i].x + m_stLinedata.stRightRight.vecLinePoints[i].x) / 2;
			m_stLanegrid.stRightGrid.stGridBase[i].dCenterY = (m_stLinedata.stRight.vecLinePoints[i].y + m_stLinedata.stRightRight.vecLinePoints[i].y) / 2;
			m_stLanegrid.stRightGrid.stGridBase[i].dGridLength = fabs(m_stLinedata.stRightRight.vecLinePoints[i].x - m_stLinedata.stRight.vecLinePoints[i].x)
				/ (2 * m_stLanegrid.stRightGrid.iGridAmount);
		}
	}
	else
	{
		m_stLanegrid.stRightGrid.bExist = false;
	}
}

void CPerceptionLines::LaneChangeProcess()
{
//local value
	unsigned int i = 0;
	int icounter = 0;
	double dDis = 0.0;
	m_stLinedata.bLeftChange = false;
	m_stLinedata.bRightChange = false;

//left lane change
	if (m_stLinedata.stRight.bExist && m_stLinedata.stLastLeft.bExist)
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = fabs(m_stLinedata.stRight.vecLinePoints[i].x - m_stLinedata.stLastLeft.vecLinePoints[i].x);
			if (dDis < MIN_CHANGE_DISTANCE)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.bLeftChange = true;
		}
	}
	if (m_stLinedata.stLeft.bExist && m_stLinedata.stLastLeft.bExist)
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = m_stLinedata.stLastLeft.vecLinePoints[i].x - m_stLinedata.stLeft.vecLinePoints[i].x;
			if (dDis > MAX_CHANGE_DISTANCE)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.bLeftChange = true;
		}
	}
//right lane change
	if (m_stLinedata.stLeft.bExist && m_stLinedata.stLastRight.bExist)
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = fabs(m_stLinedata.stLeft.vecLinePoints[i].x - m_stLinedata.stLastRight.vecLinePoints[i].x);
			if (dDis < MIN_CHANGE_DISTANCE)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.bRightChange = true;
		}
	}
	if (m_stLinedata.stRight.bExist && m_stLinedata.stLastRight.bExist)
	{
		icounter = 0;
		for (i = kBackInterestArrayLength; i < kBackInterestArrayLength + MIN_LINELENGTH; i++)
		{
			dDis = m_stLinedata.stRight.vecLinePoints[i].x - m_stLinedata.stLastRight.vecLinePoints[i].x;
			if (dDis > MAX_CHANGE_DISTANCE)
			{
				icounter++;
			}
		}
		if (icounter > HALF_MIN_LINELENGTH)
		{
			m_stLinedata.bRightChange = true;
		}
	}
}

void CPerceptionLines::SetThreadState(bool state)
{
	m_bThreadRun = state;
}

void CPerceptionLines::LineThreadRun()
{
	while (m_bThreadRun)
	{
		m_stLinedata.iHandlerReturn = m_pLCM->handleTimeout(500);
		if (m_stLinedata.iHandlerReturn > 0)
		{
			//m_stLinedata.bMsgConnected = true;
			//writeLock lock(gLinesMutex);
			//gLines = m_stLinedata;
			//gLaneGrids = m_stLanegrid;
			//lock.unlock();
		}
		else if (m_stLinedata.iHandlerReturn == 0)
		{
			m_stLinedata.bMsgConnected = false;
			m_stLinedata.bMsgLost = true;
			m_stLinedata.iMsgLostNum = MESSAGELOST_COUNTER * MESSAGELOST_RATIO;
			writeLock lock(gLinesMutex);
			gLines = m_stLinedata;
			gLaneGrids = m_stLanegrid;
			lock.unlock();
		}
		else
		{
			m_stLinedata.bMsgConnected = false;
			writeLock lock(gLinesMutex);
			gLines = m_stLinedata;
			gLaneGrids = m_stLanegrid;
			lock.unlock();
			break;
		}
	}
}

/************************************************************************/
/* 
process the lines data
*/
/************************************************************************/
void CPerceptionLines::LCMHandler(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const PERCEPTION_LINES* msg)
{
	unsigned int i = 0;
	PointXY tmpPoint;
	m_stLinedata.iLastCounter = m_stLinedata.iCounter;
	m_stLinedata.iLastTimeStamp = m_stLinedata.iTimeStamp;

	m_stLinedata.iTimeStamp = msg->header.nTimeStamp;
	m_stLinedata.iCounter = msg->header.nCounter;

	m_stLinedata.stLeftLeft.bExist = msg->bLeftLeftLine;
	m_stLinedata.stLeft.bExist = msg->bLeftLine;
	m_stLinedata.stRight.bExist = msg->bRightLine;
	m_stLinedata.stRightRight.bExist = msg->bRightRightLine;

	m_stLinedata.bMidLaneExist = false;
	m_stLinedata.stHostMiddle.bExist = false;
	m_stLinedata.bLeftLaneExist = false;
	m_stLinedata.stLeftMiddle.bExist = false;
	m_stLinedata.bRightLaneExist = false;
	m_stLinedata.stRightMiddle.bExist = false;

	vector<PointXY>().swap(m_stLinedata.stLeft.vecLinePoints);//m_stLinedata.stLeft.vecLinePoints.clear();
	vector<PointXY>().swap(m_stLinedata.stLeftMiddle.vecLinePoints); //m_stLinedata.stLeftMiddle.vecLinePoints.clear();
	vector<PointXY>().swap(m_stLinedata.stLeftLeft.vecLinePoints);//m_stLinedata.stLeftLeft.vecLinePoints.clear();
	vector<PointXY>().swap(m_stLinedata.stHostMiddle.vecLinePoints);// m_stLinedata.stHostMiddle.vecLinePoints.clear();
	vector<PointXY>().swap(m_stLinedata.stRight.vecLinePoints); //m_stLinedata.stRight.vecLinePoints.clear();
	vector<PointXY>().swap(m_stLinedata.stRightMiddle.vecLinePoints); //m_stLinedata.stRightMiddle.vecLinePoints.clear();
	vector<PointXY>().swap(m_stLinedata.stRightRight.vecLinePoints); //m_stLinedata.stRightRight.vecLinePoints.clear();

	int iArrayStartID = kBackArrayLength - kBackInterestArrayLength;

	m_stLinedata.iLeftLaneProperty = msg->gnLaneProperty[0];
	m_stLinedata.iRightLaneProperty = msg->gnLaneProperty[2];

	if (m_stLinedata.stLeftLeft.bExist)
	{
		for (i = iArrayStartID; i < (msg->nLeftLeftArrayLength + kBackArrayLength);i++)
		{
			//tmpPoint.x = -msg->gfLeftLeftLineY[i];
			//tmpPoint.y = msg->gfLeftLeftLineX[i];
			tmpPoint.x = msg->gfLeftLeftLineX[i];
			tmpPoint.y = msg->gfLeftLeftLineY[i];
			m_stLinedata.stLeftLeft.vecLinePoints.push_back(tmpPoint);
			m_stLinedata.stLeftLeft.iArrayLength = msg->nLeftLeftArrayLength;
		}
	}
	if (m_stLinedata.stLeft.bExist)
	{
		for (i = iArrayStartID; i < (msg->nLeftArrayLength + kBackArrayLength); i++)
		{
			//tmpPoint.x = -msg->gfLeftLineY[i];
			//tmpPoint.y = msg->gfLeftLineX[i];
			tmpPoint.x = msg->gfLeftLineX[i];
			tmpPoint.y = msg->gfLeftLineY[i];
			m_stLinedata.stLeft.vecLinePoints.push_back(tmpPoint);
			m_stLinedata.stLeft.iArrayLength = msg->nLeftArrayLength;
		}
	}
	if (m_stLinedata.stRight.bExist)
	{
		for (i = iArrayStartID; i < (msg->nRightArrayLength + kBackArrayLength); i++)
		{
			tmpPoint.x = msg->gfRightLineX[i];
			tmpPoint.y = msg->gfRightLineY[i];
			//tmpPoint.x = -msg->gfRightLineY[i];
			//tmpPoint.y = msg->gfRightLineX[i];
			m_stLinedata.stRight.vecLinePoints.push_back(tmpPoint);
			m_stLinedata.stRight.iArrayLength = msg->nRightArrayLength;
		}
	}
	if (m_stLinedata.stRightRight.bExist)
	{
		for (i = iArrayStartID; i < (msg->nRightRightArrayLength + kBackArrayLength); i++)
		{
			//tmpPoint.x = -msg->gfRightRightLineY[i];
			//tmpPoint.y = msg->gfRightRightLineX[i];
			tmpPoint.x = msg->gfRightRightLineX[i];
			tmpPoint.y = msg->gfRightRightLineY[i];
			m_stLinedata.stRightRight.vecLinePoints.push_back(tmpPoint);
			m_stLinedata.stRightRight.iArrayLength = msg->nRightRightArrayLength;
		}
	}
//message lost
	if ((m_stLinedata.iCounter - m_stLinedata.iLastCounter) != 1 && (m_stLinedata.iCounter - m_stLinedata.iLastCounter) != -65534)
	{
		m_stLinedata.iMsgLostNum++;
		if (m_stLinedata.iMsgLostNum > MESSAGELOST_COUNTER)
		{
			m_stLinedata.iMsgLostNum = MESSAGELOST_COUNTER;
		}
	}
	else
	{
		m_stLinedata.iMsgLostNum--;
		if (m_stLinedata.iMsgLostNum < 0)
		{
			m_stLinedata.iMsgLostNum = 0;
		}
	}

	if (m_stLinedata.iMsgLostNum >= MESSAGELOST_COUNTER*MESSAGELOST_RATIO)
	{
		m_stLinedata.bMsgLost = true;
	}
	if (m_stLinedata.iMsgLostNum == 0)
	{
		m_stLinedata.bMsgLost = false;
	}

	LineProcess();
	LaneChangeProcess();
	LaneGridProcess();

	m_stLinedata.stLastLeftLeft = m_stLinedata.stLeftLeft;
	m_stLinedata.stLastLeft = m_stLinedata.stLeft;
	m_stLinedata.stLastRight = m_stLinedata.stRight;
	m_stLinedata.stLastRightRight = m_stLinedata.stRightRight;

	writeLock lock(gLinesMutex);
	if (!m_stLinedata.bLeftChange)
	{
		m_stLinedata.bLeftChange = gLines.bLeftChange;
	}
	if (!m_stLinedata.bRightChange)
	{
		m_stLinedata.bRightChange = gLines.bRightChange;
	}
	gLines = m_stLinedata;
	gLaneGrids = m_stLanegrid;
	lock.unlock();
}