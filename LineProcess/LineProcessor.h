#pragma once
#include "global.hpp"
#include "CoordinateTrans.h"
#include "VehiclePosture.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "tinyxml2.h"
#include "MAP.h"
#include "MapGraph.h"
#include "PERCEPTION_LINES.hpp"
using namespace tinyxml2;

//#define COUTCALTIME
#define BEZIERNUM 50

struct MAPPOS
{
	bool bOnRoad;
	int iInterSectionID;
	int iRoadID;
	int iSectionID;
	MAPPOS()
	{
		bOnRoad = false;
		iInterSectionID = -1;
		iRoadID = -1;
		iSectionID = -1;
	}
};

class CLineProcessor
{
public:
	CLineProcessor();
	~CLineProcessor();
	MAPPOS m_stMapPos;

	void DecodeVehiclePosture(const lcm::ReceiveBuffer* recvBuf);
	void LoadMap();
	void ReadDestination();
	void CreateGraph();
	const bool IsLCMInitialized();
private:
	const bool InitializeLCM();
	lcm::LCM* m_pLCMPublishLines;
	bool m_bIsLCMInitialized;
	PERCEPTION_LINES m_msgMapLines;
	void PublishLineMessage(int LeftID);
	void ResetMessage();
	void InterpolateLine(int vectorIndex, int index);
	void ProcessMap();
	METIntersection* GetInterSection(int ID);
	METRoad* GetRoad(int ID1, int ID2);//get the pointer to the road connect two intersections
	void GetNextStatus();
	CONNECT_TYPE m_enDesireDirection;

	bool m_bPostureReceived;
	double m_dLastHeading;
	int64_t m_iLastRecvPosTime;
	mutex m_mtxVehPosture;
	VehiclePosture m_msgVehPosture;

	bool m_bIsMapLoaded;
	bool m_bIsDestinationLoaded;
	bool m_bIsCurrentPosGet;
	PointXY m_stDestinationPoint;
	int SearchRoadID(PointXY point);
	void SearchRoadSectionID(PointXY point);
	int SearchSectionID(PointXY point, METRoad road);
	int SearchInterSectionID(PointXY point);
	int GetLocateNodeID(PointXY point, bool bSign);//bSign true:Endpoint
	void GetMapPos(PointXY point);
	double DistanceVeh2Line(METLine* line, PointXY point);
	vector<METRoadPoint> ConnectLine(int vectorIndex);
	void LaneSplitProcess();
	POI_TYPE m_enPOIType;
	MET_POI m_stPOI;

	METMAP m_stMap;

	CMapGraph m_stMapGraph;
	int m_iDestinationNodeID;
	int m_iStartNodeID;
	int m_iCurrentPathIndex;

	METRoad* m_pCurrentRoad;
	METRoad* m_pNextRoad;
	METSection* m_pCurrentSection;
	METIntersection* m_pNextInterSection;

	METVirtualLine* m_pLeftVirtualLine;
	METVirtualLine* m_pRightVirtualLine;
	//METSection* m_pLastSection;
	//METSection* m_pNextSection;
};

