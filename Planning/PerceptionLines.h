#pragma once
#include "CoordinateTrans.h"
#include <global.hpp>
#include "Notation.h"
#include <PERCEPTION_LINES.hpp>

using namespace std;

#define AVERAGE_NUM 4
#define HISTORY_NUM 30

#define MAX_LANEWIDTH 6
#define MIN_LANEWIDTH 2.6

#define MIN_CHANGE_DISTANCE 1
#define MAX_CHANGE_DISTANCE 3

#define MIN_LINELENGTH 16
#define HALF_MIN_LINELENGTH 2



#define LANEWIDTH 3.4

#define MAX_BASE_AMOUNT 300
const double kGridLength = 0.2;
const float kDistance2LineThreshold = 0.2;
const int kBackArrayLength = 100;
const int kBackInterestArrayLength = 30;
const int kSelfIdinLine = kBackInterestArrayLength;
#define INVALIDVALUE	10000.0

/* 
lane line
middle line
point set and point num
*/
struct Line
{
	bool bExist;
	int16_t iArrayLength;
	vector<PointXY> vecLinePoints;
	Line()
	{
		bExist = false;
		iArrayLength = 0;
	}
};

struct LineData
{
	bool bMsgConnected;//whether receive the perception line data
	bool bMsgLost;//whether drop frame
	int16_t iCounter;
	int16_t iLastCounter;
	int64_t iTimeStamp;
	int64_t iLastTimeStamp;
	int16_t iMsgLostNum;//the num of drop frame
//lane exist and it's property
	bool bLeftLaneExist;
	bool bRightLaneExist;
	bool bMidLaneExist;
	int8_t iLeftLaneProperty;
	int8_t iRightLaneProperty;
	int8_t iMidLaneProperty;

	bool bLeftChange;
	bool bRightChange;
	float fDis2LeftLine;
	float fDis2RightLine;
//lane side line
	Line stLeftLeft;
	Line stLeft;
	Line stRight;
	Line stRightRight;
//lane center line
	Line stLeftMiddle;
	Line stHostMiddle;
	Line stRightMiddle;
//last line msg
	Line stLastLeftLeft;
	Line stLastLeft;
	Line stLastRight;
	Line stLastRightRight;
	Line stLastLeftMiddle;
	Line stLastHostMiddle;
	Line stLastRightMiddle;

	int iHandlerReturn;

	LineData()
	{
		bMsgConnected = true;
		bMsgLost = false;

		iCounter = 0;
		iLastCounter = 0;
		iTimeStamp = 0;
		iLastTimeStamp = 0;
		iMsgLostNum = 0;

		bLeftLaneExist = false;
		bRightLaneExist = false;
		bMidLaneExist = false;

		iLeftLaneProperty = 0;
		iRightLaneProperty = 0;
		iMidLaneProperty = 0;

		bLeftChange = false;
		bRightChange = false;

		fDis2LeftLine = 0.0f;
		fDis2RightLine = 0.0f;

		iHandlerReturn = 0;
	}
};

//
struct Base
{
	double dCenterX;
	double dCenterY;
	double dLeftX;
	double dRightX;
	double dGridLength;
	int iGridAmount;
	Base()
	{
		dCenterX = 0.0;
		dCenterY = 0.0;
		dLeftX = 0.0;
		dRightX = 0.0;
		dGridLength = 0.0;
		iGridAmount = 0;
	}
};
//
struct Grid
{
	bool bExist;
	int16_t iGridAmount;
	int16_t iBaseAmount;
	int16_t iBackBaseMaxAmount;
	int16_t iFrontBaseMaxAmount;
	Base stGridBase[MAX_BASE_AMOUNT];
	Grid()
	{
		bExist = false;
		iGridAmount = 0;
		iBaseAmount = 0;
		iBackBaseMaxAmount = 0;
		iFrontBaseMaxAmount = 0;
	}
};

struct LaneGrid
{
	Grid stLeftGrid;
	Grid stMidGrid;
	Grid stRightGrid;
};

extern LineData gLines;
extern LaneGrid gLaneGrids;
extern shared_mutex gLinesMutex;

class CPerceptionLines
{
public:
	explicit CPerceptionLines();
	~CPerceptionLines();

	LineData m_stLinedata;
	LaneGrid m_stLanegrid;
	list<float> m_listDis2LeftLine;
	list<float> m_listDis2RightLine;
	vector<float> m_vecDis2LeftLine;
	vector<float> m_vecDis2RightLine;

	int64_t m_iLastRecvTime;
	int64_t m_iCurrentRecvTime;

	lcm::LCM* m_pLCM;
	void LCMHandler(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const PERCEPTION_LINES* msg);
	bool InitializeLCM();

	void SetThreadState(bool);
	void LineThreadRun();

private:
	bool m_bThreadRun;
	int m_iSelfID;
	int m_iBackwardArraysize;
	int m_iBackwardLength;

	void LineProcess();
	void LaneGridProcess();
	void LaneChangeProcess();
};

