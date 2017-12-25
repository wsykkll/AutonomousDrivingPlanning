#include "LineProcessor.h"


CLineProcessor::CLineProcessor() :
m_bIsLCMInitialized(false),
m_bPostureReceived(false),
m_bIsDestinationLoaded(false),
m_bIsCurrentPosGet(false),
m_iDestinationNodeID(-1),
m_iStartNodeID(-1),
m_iCurrentPathIndex(-1),
m_enPOIType(UNKNOWN_TYPE),
m_enDesireDirection(GO_STRAIGHT),
m_bIsMapLoaded(false)
{
	for (int i = 0; i < 3; i++)
	{
		m_msgMapLines.gnLaneProperty[i] = 0;
	}
	m_pLeftVirtualLine = NULL;
	m_pRightVirtualLine = NULL;
	m_pNextInterSection = NULL;
	m_pNextRoad = NULL;
	m_bIsLCMInitialized = InitializeLCM();
	LoadMap();
	CreateGraph();
	ReadDestination();
}


CLineProcessor::~CLineProcessor()
{
	delete m_pLCMPublishLines;
}

const bool CLineProcessor::InitializeLCM()
{
	m_pLCMPublishLines = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
	if (!m_pLCMPublishLines->good())
	{
		printf("Initialize Communication Error, Check the Etherent Connection!\n");
		return false;
	}
	return true;
}

const bool CLineProcessor::IsLCMInitialized()
{
	return m_bIsLCMInitialized;
}

void CLineProcessor::LaneSplitProcess()
{
	if (m_pCurrentRoad->vec_POIs.size() > 0)
	{
		PointXY tmpPoint;
		double dMinDis = 10000000.0;
		for (vector<MET_POI>::iterator it = m_pCurrentRoad->vec_POIs.begin(); it != m_pCurrentRoad->vec_POIs.end(); it++)
		{
			tmpPoint = GCST2VEH(it->stPOIPos.dLatitude, it->stPOIPos.dLongitude, m_msgVehPosture.dLatitude, m_msgVehPosture.dLongitude,
				m_msgVehPosture.dHeading);
			if (tmpPoint.y > 0.0)
			{
				double dDis = Distance(tmpPoint);
				if (dDis < dMinDis)
				{
					dMinDis = dDis;
					m_enPOIType = it->enType;
					m_stPOI = *it;
				}
			}
		}
		if (dMinDis > 200)
		{
			m_enPOIType = UNKNOWN_TYPE;
		}
	}
	else
	{
		m_enPOIType = UNKNOWN_TYPE;
	}
}

void CLineProcessor::SearchRoadSectionID(PointXY point)
{
	PointXY RelativePos;
	vector<METRoad>::iterator R_it = m_stMap.vec_Roads.begin();
	for (; R_it != m_stMap.vec_Roads.end(); R_it++)
	{
		vector<PointXY> vecRoadBoxPoints;
		PointXY tmpPt;
		tmpPt.x = 0.0; tmpPt.y = 0.0;
		for (int i = 0; i < R_it->stRoadBox.iPointNum; i++)
		{
			RelativePos = GCS2CCS(point.x, point.y, R_it->stRoadBox.vec_EdgePoints[i].dLatitude,
				R_it->stRoadBox.vec_EdgePoints[i].dLongitude);
			vecRoadBoxPoints.push_back(RelativePos);
		}
		if (m_stMapGraph.IsInArea(tmpPt, vecRoadBoxPoints))
		{
			list<METSection>::iterator Sit = R_it->list_sections.begin();
			list<METSection>::iterator NextSit = Sit;
			list<METSection>::iterator LastSit = Sit;
			int IteratorIndex = 0;
			int iSectionNum = R_it->list_sections.size();
			for (; Sit != R_it->list_sections.end(); Sit++)
			{
				if (IteratorIndex < (iSectionNum - 1))
				{
					NextSit++;
				}
				if (IteratorIndex > 1)
				{
					LastSit++;
				}
				vector<PointXY> vecBoxPoints;
				for (int i = 0; i < Sit->stSectionBox.iPointNum; i++)
				{
					RelativePos = GCS2CCS(point.x, point.y, Sit->stSectionBox.vec_EdgePoints[i].dLatitude,
						Sit->stSectionBox.vec_EdgePoints[i].dLongitude);
					vecBoxPoints.push_back(RelativePos);
				}
				if (m_stMapGraph.IsInArea(tmpPt, vecBoxPoints))
				{
					m_stMapPos.bOnRoad = true;
					m_stMapPos.iRoadID = R_it->nRoadID;
					m_stMapPos.iSectionID = Sit->nSectionID;
					m_pCurrentRoad = &(*(R_it));
					//distance to Road POI
					LaneSplitProcess();
					m_pCurrentSection = &(*(Sit));
					//if (IteratorIndex < (iSectionNum - 1))
					//{
					//	m_pNextSection = &(*(NextSit));
					//}
					//else
					//{
					//	m_pNextSection = NULL;
					//}
					//
					//if (IteratorIndex == 0)
					//{
					//	m_pLastSection = NULL;
					//}
					//else if (IteratorIndex == 1)
					//{
					//	m_pLastSection = &(*(LastSit));
					//}
					//else
					//{
					//	m_pLastSection = &(*(LastSit));
					//}
					break;
				}
				IteratorIndex++;
			}
			break;
		}
	}
}

int CLineProcessor::SearchRoadID(PointXY point)
{
	int returnID = 0;
	PointXY RelativePos;
	vector<METRoad>::iterator R_it = m_stMap.vec_Roads.begin();
	for (; R_it != m_stMap.vec_Roads.end(); R_it++)
	{
		vector<PointXY> vecRoadBoxPoints;
		PointXY tmpPt;
		tmpPt.x = 0.0; tmpPt.y = 0.0;
		for (int i = 0; i < R_it->stRoadBox.iPointNum; i++)
		{
			RelativePos = GCS2CCS(point.x, point.y, R_it->stRoadBox.vec_EdgePoints[i].dLatitude,
				R_it->stRoadBox.vec_EdgePoints[i].dLongitude);
			vecRoadBoxPoints.push_back(RelativePos);
		}
		if (m_stMapGraph.IsInArea(tmpPt, vecRoadBoxPoints))
		{
			returnID = R_it->nRoadID;
			break;
		}
	}
	return returnID;
}

int CLineProcessor::SearchSectionID(PointXY point, METRoad road)
{
	int returnID = 0;
	PointXY RelativePos;
	list<METSection>::iterator Sit = road.list_sections.begin();
	for (; Sit != road.list_sections.end(); Sit++)
	{
		PointXY tmpPt;
		vector<PointXY> vecBoxPoints;
		tmpPt.x = 0.0; tmpPt.y = 0.0;
		for (int i = 0; i < Sit->stSectionBox.iPointNum; i++)
		{
			RelativePos = GCS2CCS(point.x, point.y, Sit->stSectionBox.vec_EdgePoints[i].dLatitude,
				Sit->stSectionBox.vec_EdgePoints[i].dLongitude);
			vecBoxPoints.push_back(RelativePos);
		}
		if (m_stMapGraph.IsInArea(tmpPt, vecBoxPoints))
		{
			returnID = Sit->nSectionID;
			break;
		}
	}
	return returnID;
}

int CLineProcessor::SearchInterSectionID(PointXY point)
{
	int returnID = 0;
	PointXY RelativePos;
	PointXY tmpPt;
	vector<METIntersection>::iterator it = m_stMap.vec_InterSections.begin();
	for (; it != m_stMap.vec_InterSections.end(); it++)
	{
		vector<PointXY> vecBoxPoints;
		tmpPt.x = 0.0; tmpPt.y = 0.0;
		for (int i = 0; i < it->stIntersectionBox.iPointNum; i++)
		{
			RelativePos = GCS2CCS(point.x, point.y, it->stIntersectionBox.vec_EdgePoints[i].dLatitude,
				it->stIntersectionBox.vec_EdgePoints[i].dLongitude);
			vecBoxPoints.push_back(RelativePos);
		}
		if (m_stMapGraph.IsInArea(tmpPt, vecBoxPoints))
		{
			m_stMapPos.bOnRoad = false;
			m_stMapPos.iInterSectionID = it->nIntersectionID;
			m_pCurrentRoad = NULL;
			m_pCurrentSection = NULL;
			//m_pLastSection = NULL;
			//m_pNextSection = NULL;
			returnID = it->nIntersectionID;
			break;
		}
	}
	return returnID;
}

double CLineProcessor::DistanceVeh2Line(METLine* line, PointXY point)
{
	PointXY RelativePoint_1, RelativePoint_2, InitPoint;
	InitPoint.x = 0.0;
	InitPoint.y = 0.0;
	list<METRoadPoint>::iterator it = line->list_points.begin();
	list<METRoadPoint>::iterator Nextit = line->list_points.begin();
	Nextit++;
	for (size_t i = 0; i < (line->list_points.size() - 1); i++)
	{
		RelativePoint_1 = GCS2CCS(point.x, point.y, it->stPoint.dLatitude, it->stPoint.dLongitude);
		it++;
		RelativePoint_2 = GCS2CCS(point.x, point.y, Nextit->stPoint.dLatitude, Nextit->stPoint.dLongitude);
		Nextit++;
		if ((m_stMapGraph.PointMulti(InitPoint, RelativePoint_2, RelativePoint_1) > 0)
			&& (m_stMapGraph.PointMulti(InitPoint, RelativePoint_1, RelativePoint_2) > 0))
		{
			if (m_stMapGraph.CrossMulti(RelativePoint_1, RelativePoint_2, InitPoint) > 0)
			{
				return 0.1;
			}
			else
			{
				return -0.1;
			}
		}
	}
	return 0.0;
}

void CLineProcessor::GetMapPos(PointXY point)
{
	if (m_stMapPos.bOnRoad)
	{
		vector<PointXY> vecCurrentBoxPoints;
		PointXY tmpPt, RelativePos;
		tmpPt.x = 0.0; tmpPt.y = 0.0;
		for (vector<METKeyPoint>::iterator key_it = m_pCurrentSection->stSectionBox.vec_EdgePoints.begin(); key_it != m_pCurrentSection->stSectionBox.vec_EdgePoints.end(); key_it++)
		{
			RelativePos = GCS2CCS(point.x, point.y, key_it->dLatitude, key_it->dLongitude);
			vecCurrentBoxPoints.push_back(RelativePos);
		}
		if (m_stMapGraph.IsInArea(tmpPt, vecCurrentBoxPoints))
		{
			LaneSplitProcess();
			return;
		}
		if (m_pCurrentSection->pNextSection)//if (m_pNextSection)
		{
			m_pCurrentSection = m_pCurrentSection->pNextSection; //m_pCurrentSection = m_pNextSection;
			LaneSplitProcess();
			return;
			//for (vector<METKeyPoint>::iterator key_it = m_pCurrentSection->pNextSection->stSectionBox.vec_EdgePoints.begin(); key_it != m_pCurrentSection->pNextSection->stSectionBox.vec_EdgePoints.end(); key_it++)
			//{
			//	RelativePos = GCS2CCS(point.x, point.y, key_it->dLatitude, key_it->dLongitude);
			//	vecCurrentBoxPoints.push_back(RelativePos);
			//}
			//if (m_stMapGraph.IsInArea(tmpPt, vecCurrentBoxPoints))
			//{
			//	//m_pLastSection = m_pCurrentSection;
			//	m_pCurrentSection = m_pCurrentSection->pNextSection; //m_pCurrentSection = m_pNextSection;
			//	return;
			//	//if (m_pNextSection->bConnected)
			//	//{
			//	//	m_pNextSection = NULL;
			//	//	return;
			//	//}
			//	//bool bGetCurrentSec = false;
			//	//for (list<METSection>::iterator sec_it = m_pCurrentRoad->list_sections.begin(); sec_it != m_pCurrentRoad->list_sections.end(); sec_it++)
			//	//{
			//	//	if (bGetCurrentSec)
			//	//	{
			//	//		m_pNextSection = &(*(sec_it));
			//	//		return;
			//	//	}
			//	//	if (sec_it->nSectionID == m_pCurrentSection->nSectionID)
			//	//	{
			//	//		bGetCurrentSec = true;
			//	//	}
			//	//}
			//}
		}
		int iID = SearchInterSectionID(point);
		if (iID > 0)//road to intersection
		{
			m_iCurrentPathIndex++;
			GetNextStatus();
		}
	}
	else
	{
		int iID = SearchInterSectionID(point);
		if (iID == 0)//intersection to road
		{
			SearchRoadSectionID(point);
			GetNextStatus();
		}
		//else
		//{
		//	m_iCurrentPathIndex++;
		//	GetNextStatus();
		//}
	}
}

int CLineProcessor::GetLocateNodeID(PointXY point, bool bSign)
{
	int returnID = SearchInterSectionID(point);
	if (returnID > 0)
	{
		return returnID;
	}
	else
	{
		SearchRoadSectionID(point);
		if (m_stMapPos.iSectionID > 0)
		{
			for (vector<METIntersection>::iterator iit = m_stMap.vec_InterSections.begin(); iit != m_stMap.vec_InterSections.end(); iit++)
			{
				if (!bSign)//start node
				{
					for (vector<ROAD_CONNECTION>::iterator IDit = iit->vec_RoadConnections.begin(); IDit != iit->vec_RoadConnections.end(); IDit++)
					{
						for (vector<ROAD_CONNECTION_OUT>::iterator out_it = IDit->vec_RoadOuts.begin();
							out_it != IDit->vec_RoadOuts.end(); out_it++)
						{
							if (out_it->iOutRoadID == m_stMapPos.iRoadID)
							{
								return iit->nIntersectionID;
							}
						}
					}
				}
				else
				{
					for (vector<ROAD_CONNECTION>::iterator IDit = iit->vec_RoadConnections.begin(); IDit != iit->vec_RoadConnections.end(); IDit++)
					{
						if (IDit->iInRoadID == m_stMapPos.iRoadID)
						{
							return iit->nIntersectionID;
						}
					}
				}
			}
		}
		//int roadID = SearchRoadID(point);
		//if (roadID > 0)
		//{
		//	for (vector<METRoad>::iterator it = m_stMap.vec_Roads.begin(); it != m_stMap.vec_Roads.end(); it++)
		//	{
		//		if (it->nRoadID == roadID)
		//		{
		//			int sectionID = SearchSectionID(point, *it);
		//			if (sectionID > 0)
		//			{
		//				for (vector<METIntersection>::iterator iit = m_stMap.vec_InterSections.begin(); iit != m_stMap.vec_InterSections.end(); iit++)
		//				{
		//					if (!bSign)
		//					{
		//						for (vector<int>::iterator IDit = iit->vec_OutRoadID.begin(); IDit != iit->vec_OutRoadID.end(); IDit++)
		//						{
		//							if (*IDit == roadID)
		//							{
		//								//m_iDestinationNodeID = iit->nIntersectionID;
		//								return iit->nIntersectionID;
		//							}
		//						}
		//					}
		//					else
		//					{
		//						for (vector<int>::iterator IDit = iit->vec_InRoadID.begin(); IDit != iit->vec_InRoadID.end(); IDit++)
		//						{
		//							if (*IDit == roadID)
		//							{
		//								//m_iDestinationNodeID = iit->nIntersectionID;
		//								return iit->nIntersectionID;
		//							}
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//}
	}
	return returnID;
}

void CLineProcessor::ReadDestination()
{
	tinyxml2::XMLDocument* pdoc = new tinyxml2::XMLDocument();
	XMLError errorID = pdoc->LoadFile("..\\data\\DestinationPos.xml");
	if (errorID != 0)
	{
		m_bIsDestinationLoaded = false;
		return;
	}
	m_bIsDestinationLoaded = true;
	XMLElement* pRootElem = pdoc->RootElement();
	pRootElem->QueryDoubleAttribute("Lat", &m_stDestinationPoint.x);
	pRootElem->QueryDoubleAttribute("Lon", &m_stDestinationPoint.y);
	delete pdoc;
	if (m_bIsMapLoaded)
	{
		//loacte the destination
		m_iDestinationNodeID = GetLocateNodeID(m_stDestinationPoint,true);
	}
	m_stMapPos.bOnRoad = false;
	m_stMapPos.iInterSectionID = -1;
	m_stMapPos.iRoadID = -1;
	m_stMapPos.iSectionID = -1;
	return;
}

void CLineProcessor::ProcessMap()
{
	for (vector<METRoad>::iterator Road_it = m_stMap.vec_Roads.begin(); Road_it != m_stMap.vec_Roads.end(); Road_it++)
	{
		list<METSection>::iterator Sit = Road_it->list_sections.begin();
		list<METSection>::iterator NextSit = Sit;
		list<METSection>::iterator LastSit = Sit;
		int IteratorIndex = 0;
		int iSectionNum = Road_it->list_sections.size();
		for (; Sit != Road_it->list_sections.end(); Sit++)
		{
			if (Sit->bConnected)
			{
				vector<METIntersection>::iterator intersec_it = m_stMap.vec_InterSections.begin();
				for (; intersec_it != m_stMap.vec_InterSections.end(); intersec_it++)
				{
					if (intersec_it->nIntersectionID == Sit->nConnectedID)
					{
						Sit->pConnectedInterSection = &(*intersec_it);
						break;
					}
				}
			}
			if (IteratorIndex < (iSectionNum - 1))
			{
				NextSit++;
			}
			if (IteratorIndex > 1)
			{
				LastSit++;
			}
			if (IteratorIndex < (iSectionNum - 1))
			{
				Sit->pNextSection = &(*(NextSit));
			}
			else
			{
				Sit->pNextSection = NULL;
			}
			if (IteratorIndex == 0)
			{
				Sit->pLastSection = NULL;
			}
			else if (IteratorIndex == 1)
			{
				Sit->pLastSection = &(*(LastSit));
			}
			else
			{
				Sit->pLastSection = &(*(LastSit));
			}
			IteratorIndex++;
		}
	}
}

void CLineProcessor::LoadMap()
{
	tinyxml2::XMLDocument* pdoc = new tinyxml2::XMLDocument();
	XMLError errorID = pdoc->LoadFile("..\\data\\METMap.xml");
	if (errorID != 0)
	{
		m_bIsMapLoaded = false;
		return;
	}
	m_bIsMapLoaded = true;
	XMLElement* pRootElem = pdoc->RootElement();
	int iRoadAmount = 0;
	pRootElem->QueryIntAttribute("RoadAmount", &iRoadAmount);
//Road
	XMLElement* pRoadElem = pRootElem->FirstChildElement("Road");
	for (pRoadElem; pRoadElem; pRoadElem = pRoadElem->NextSiblingElement("Road"))
	{
		METRoad tmpMETRoad;
		vector<cv::Point2f> vecRoadOutlinePoints;
		double dGlobalInitLat = 0.0;
		double dGlobalInitLon = 0.0;
		pRoadElem->QueryIntAttribute("Id", &(tmpMETRoad.nRoadID));
		int iSectionIndex = 0;
		int iLineIndex = 0;
		XMLElement* pRoadSectionElem = pRoadElem->FirstChildElement("Section");
		for (pRoadSectionElem; pRoadSectionElem; pRoadSectionElem = pRoadSectionElem->NextSiblingElement("Section"))
		{
			METSection tmpRoadSection;
			pRoadSectionElem->QueryBoolAttribute("Connected", &(tmpRoadSection.bConnected));
			pRoadSectionElem->QueryIntAttribute("Id", &(tmpRoadSection.nSectionID));
			pRoadSectionElem->QueryIntAttribute("ConnectInterSectionID", &(tmpRoadSection.nConnectedID));
			int iLaneAmount = 0;
			int iLineAmount = 0;
			pRoadSectionElem->QueryIntAttribute("LaneAmount", &iLaneAmount);
			pRoadSectionElem->QueryIntAttribute("LaneLineAmount", &iLineAmount);
			XMLElement* pPOIElem;
			pPOIElem = pRoadSectionElem->FirstChildElement("POI");
			for (pPOIElem; pPOIElem; pPOIElem = pPOIElem->NextSiblingElement("POI"))
			{
				MET_POI tmpPOI;
				pPOIElem->QueryBoolAttribute("Exist", &tmpPOI.bExist);
				pPOIElem->QueryDoubleAttribute("Lat", &tmpPOI.stPOIPos.dLatitude);
				pPOIElem->QueryDoubleAttribute("Lon", &tmpPOI.stPOIPos.dLongitude);
				pPOIElem->QueryIntAttribute("ConnectID", &tmpPOI.iConnectedID);
				int iPOIType = 0;
				pPOIElem->QueryIntAttribute("Type", &iPOIType);
				tmpPOI.enType = POI_TYPE(iPOIType);
				tmpRoadSection.vec_pois.push_back(tmpPOI);
				if (tmpPOI.bExist && (tmpPOI.enType == LANE_SPLIT_LEFT || tmpPOI.enType == LANE_SPLIT_RIGHT))
				{
					tmpMETRoad.vec_POIs.push_back(tmpPOI);
				}
			}
			XMLElement* pLineElem;
			pLineElem = pRoadSectionElem->FirstChildElement("Line");
			for (pLineElem; pLineElem; pLineElem = pLineElem->NextSiblingElement("Line"))
			{
				METLine tmpLine;
				pLineElem->QueryIntAttribute("RoadId", &(tmpLine.stKeyIndex.nRoadId));
				pLineElem->QueryIntAttribute("SectionId", &(tmpLine.stKeyIndex.nSectionSeq));
				pLineElem->QueryIntAttribute("EdgeId", &(tmpLine.stKeyIndex.nEdgeNum));
				pLineElem->QueryIntAttribute("UniqueId", &(tmpLine.nLineID));
				int iType, iColor;
				pLineElem->QueryIntAttribute("TypeLanLine", &(iType));
				pLineElem->QueryIntAttribute("Color", &(iColor));
				tmpLine.enColor = COLORTYPE(iColor);
				tmpLine.enType = LINEType(iType);

				XMLElement* pRoadPointElem = pLineElem->FirstChildElement("Point");
				for (pRoadPointElem; pRoadPointElem; pRoadPointElem = pRoadPointElem->NextSiblingElement("Point"))
				{
					METRoadPoint tmpRoadPoint;
					int iID = 0;
					pRoadPointElem->QueryIntAttribute("Id", &iID);
					pRoadPointElem->QueryFloatAttribute("Heading", &(tmpRoadPoint.fHeading));
					pRoadPointElem->QueryDoubleAttribute("Lon", &(tmpRoadPoint.stPoint.dLongitude));
					pRoadPointElem->QueryDoubleAttribute("Lat", &(tmpRoadPoint.stPoint.dLatitude));
					tmpLine.list_points.push_back(tmpRoadPoint);
					if (iSectionIndex == 0 && iLineIndex == 0)
					{
						dGlobalInitLat = tmpRoadPoint.stPoint.dLatitude;
						dGlobalInitLon = tmpRoadPoint.stPoint.dLongitude;
					}
				}
				//interpolate the points
				list<METRoadPoint>::iterator Fit = tmpLine.list_points.begin();
				list<METRoadPoint>::iterator Nit = tmpLine.list_points.begin();
				Nit++;
				for (size_t i = 0; i < (tmpLine.list_points.size()-1); i++)
				{
					METRoadPoint pta = *(Fit); Fit++;
					METRoadPoint ptb = *(Nit); Nit++;
					tmpLine.vec_points.push_back(pta);
					int iNum = int(floor(DistanceInGps(pta.stPoint.dLatitude, pta.stPoint.dLongitude, ptb.stPoint.dLatitude, ptb.stPoint.dLongitude)));
					double dDeltaLat = ptb.stPoint.dLatitude - pta.stPoint.dLatitude;
					double dDeltaLon = ptb.stPoint.dLongitude - pta.stPoint.dLongitude;
					double dStepLat = dDeltaLat / iNum;
					double dStepLon = dDeltaLon / iNum;
					METRoadPoint InterploatePoint;
					InterploatePoint.fHeading = pta.fHeading;
					for (int k = 1; k <= iNum; k++)
					{
						InterploatePoint.stPoint.dLatitude = pta.stPoint.dLatitude + k*dStepLat;
						InterploatePoint.stPoint.dLongitude = pta.stPoint.dLongitude + k*dStepLon;
						tmpLine.vec_points.push_back(InterploatePoint);
					}
				}
				iLineIndex++;
				tmpRoadSection.vec_lines.push_back(tmpLine);
			}
			//Section Box
			vector<cv::Point2f> vecOutlinePoints;
			vector<METLine>::iterator it = tmpRoadSection.vec_lines.begin();
			double dInitLat = it->list_points.front().stPoint.dLatitude;
			double dInitLon = it->list_points.front().stPoint.dLongitude;
			tmpRoadSection.stSectionBox.iPointNum = 4;
			for (; it != tmpRoadSection.vec_lines.end(); it++)
			{
				list<METRoadPoint>::iterator Pit = it->list_points.begin();
				for (; Pit != it->list_points.end(); Pit++)
				{
					PointXY tmpPt = GCS2CCS(dInitLat, dInitLon, Pit->stPoint.dLatitude, Pit->stPoint.dLongitude);
					cv::Point2f Pt;
					Pt.x = (float)(tmpPt.x); Pt.y = (float)(tmpPt.y);
					vecOutlinePoints.push_back(Pt);

					tmpPt = GCS2CCS(dGlobalInitLat, dGlobalInitLon, Pit->stPoint.dLatitude, Pit->stPoint.dLongitude);
					Pt.x = (float)(tmpPt.x); Pt.y = (float)(tmpPt.y);
					vecRoadOutlinePoints.push_back(Pt);
				}
			}
			//vecRoadOutlinePoints.insert(vecRoadOutlinePoints.end(), vecOutlinePoints.begin(), vecOutlinePoints.end());
			cv::Point2f OutlinePoints[4];
			cv::minAreaRect(cv::Mat(vecOutlinePoints)).points(OutlinePoints);
			for (size_t i = 0; i < 4; i++)
			{
				PointXY tmpPt = CCS2GCS(dInitLat, dInitLon, OutlinePoints[i].x, OutlinePoints[i].y);
				METKeyPoint PT;
				PT.dLatitude = tmpPt.y;
				PT.dLongitude = tmpPt.x;
				tmpRoadSection.stSectionBox.vec_EdgePoints.push_back(PT);
			}

			XMLElement* pLaneElem;
			pLaneElem = pRoadSectionElem->FirstChildElement("Lane");
			for (pLaneElem; pLaneElem; pLaneElem = pLaneElem->NextSiblingElement("Lane"))
			{
				METLane tmpMETLane;
				int iLaneDiversion;
				pLaneElem->QueryIntAttribute("Diversion", &iLaneDiversion);
				tmpMETLane.enLaneDiversion = LaneDiversion(iLaneDiversion);
				tmpRoadSection.vec_lanes.push_back(tmpMETLane);
			}
			iSectionIndex++;
			tmpMETRoad.list_sections.push_back(tmpRoadSection);
		}
		//Road box
		tmpMETRoad.stRoadBox.iPointNum = 4;
		cv::Point2f RoadOutlinePoints[4];
		cv::minAreaRect(cv::Mat(vecRoadOutlinePoints)).points(RoadOutlinePoints);
		for (size_t i = 0; i < 4; i++)
		{
			PointXY tmpPt = CCS2GCS(dGlobalInitLat, dGlobalInitLon, RoadOutlinePoints[i].x, RoadOutlinePoints[i].y);
			METKeyPoint PT;
			PT.dLatitude = tmpPt.y;
			PT.dLongitude = tmpPt.x;
			tmpMETRoad.stRoadBox.vec_EdgePoints.push_back(PT);
		}
		m_stMap.vec_Roads.push_back(tmpMETRoad);
	}
//InterSection
	XMLElement* pInterSectionElem = pRootElem->FirstChildElement("InterSection");
	for (pInterSectionElem; pInterSectionElem; pInterSectionElem = pInterSectionElem->NextSiblingElement("InterSection"))
	{
		METIntersection tmpInterSection;
		pInterSectionElem->QueryIntAttribute("Id", &(tmpInterSection.nIntersectionID));
		int iInRoadID = -1;
		int iOutRoadID = -1;
		
		XMLElement* pRoadConnectionElem = pInterSectionElem->FirstChildElement("RoadConnection");
		for (pRoadConnectionElem; pRoadConnectionElem; pRoadConnectionElem = pRoadConnectionElem->NextSiblingElement("RoadConnection"))
		{
			ROAD_CONNECTION tmpRoadConnection;
			pRoadConnectionElem->QueryIntAttribute("InRoadID", &tmpRoadConnection.iInRoadID);
			XMLElement* pRoadOutElem;
			pRoadOutElem = pRoadConnectionElem->FirstChildElement("RoadOut");
			for (pRoadOutElem; pRoadOutElem; pRoadOutElem = pRoadOutElem->NextSiblingElement("RoadOut"))
			{
				ROAD_CONNECTION_OUT tmpRoadOut;
				int iConnectionType;
				pRoadOutElem->QueryIntAttribute("ConnectionType", &iConnectionType);
				tmpRoadOut.enConnectType = CONNECT_TYPE(iConnectionType);
				pRoadOutElem->QueryIntAttribute("OutRoadID", &tmpRoadOut.iOutRoadID);
				tmpRoadConnection.vec_RoadOuts.push_back(tmpRoadOut);
			}
			tmpInterSection.vec_RoadConnections.push_back(tmpRoadConnection);
		}
		
		//XMLElement* pInRoadElem = pInterSectionElem->FirstChildElement("InRoad");
		//XMLElement* pInRoadIDElem = pInRoadElem->FirstChildElement("RoadId");
		//for (pInRoadIDElem; pInRoadIDElem; pInRoadIDElem = pInRoadIDElem->NextSiblingElement("RoadId"))
		//{
		//	pInRoadIDElem->QueryIntAttribute("RoadId", &iInRoadID);
		//	tmpInterSection.vec_InRoadID.push_back(iInRoadID);
		//}
		//XMLElement* pOutRoadElem = pInterSectionElem->FirstChildElement("OutRoad");
		//XMLElement* pOutRoadIDElem = pOutRoadElem->FirstChildElement("RoadId");
		//for (pOutRoadIDElem; pOutRoadIDElem; pOutRoadIDElem = pOutRoadIDElem->NextSiblingElement("RoadId"))
		//{
		//	pOutRoadIDElem->QueryIntAttribute("RoadId", &iOutRoadID);
		//	tmpInterSection.vec_OutRoadID.push_back(iOutRoadID);
		//}

		//intersection box outline
		XMLElement* pInterSectionBoxElem = pInterSectionElem->FirstChildElement("OutLine");
		XMLElement* pBoxLineElem = pInterSectionBoxElem->FirstChildElement("Line");
		pBoxLineElem->QueryIntAttribute("PointNum", &(tmpInterSection.stIntersectionBox.iPointNum));
		XMLElement* pBoxPointElem = pBoxLineElem->FirstChildElement("Point");
		for (pBoxPointElem; pBoxPointElem; pBoxPointElem = pBoxPointElem->NextSiblingElement("Point"))
		{
			METKeyPoint tmpPt;
			pBoxPointElem->QueryDoubleAttribute("Lon", &(tmpPt.dLongitude));
			pBoxPointElem->QueryDoubleAttribute("Lat", &(tmpPt.dLatitude));
			tmpInterSection.stIntersectionBox.vec_EdgePoints.push_back(tmpPt);
		}
		//Zebra line
		XMLElement* pZebraLineElem = pInterSectionElem->FirstChildElement("ZebraLine");
		XMLElement* pZebraLineDataElem = pZebraLineElem->FirstChildElement("Line");
		for (pZebraLineDataElem; pZebraLineDataElem; pZebraLineDataElem = pZebraLineDataElem->NextSiblingElement("Line"))
		{
			METZebraLine tmpZebraLine;
			pZebraLineDataElem->QueryIntAttribute("InRoadId", &(tmpZebraLine.nLinkedRoadID));
			pZebraLineDataElem->QueryIntAttribute("PointNum", &(tmpZebraLine.stZebralineBox.iPointNum));
			XMLElement* pZebraLineBoxElem = pZebraLineDataElem->FirstChildElement("Point");
			METKeyPoint tmpPt;
			for (pZebraLineBoxElem; pZebraLineBoxElem; pZebraLineBoxElem = pZebraLineBoxElem->NextSiblingElement("Point"))
			{
				pZebraLineBoxElem->QueryDoubleAttribute("Lon", &(tmpPt.dLongitude));
				pZebraLineBoxElem->QueryDoubleAttribute("Lat", &(tmpPt.dLatitude));
				tmpZebraLine.stZebralineBox.vec_EdgePoints.push_back(tmpPt);
			}
			tmpInterSection.vec_zebraline.push_back(tmpZebraLine);
		}
		//virtual lines
		XMLElement* pVirtualLanesElem = pInterSectionElem->FirstChildElement("VirtualLaneLine");
		XMLElement* pVirtualLaneLineElem = pVirtualLanesElem->FirstChildElement("Line");
		for (pVirtualLaneLineElem; pVirtualLaneLineElem; pVirtualLaneLineElem = pVirtualLaneLineElem->NextSiblingElement("Line"))
		{
			METVirtualLine tmpVirtualLine;
			pVirtualLaneLineElem->QueryIntAttribute("InRoadId", &(tmpVirtualLine.nWayInRoadID));
			pVirtualLaneLineElem->QueryIntAttribute("InSectionId", &(tmpVirtualLine.nWayInSectionID));
			pVirtualLaneLineElem->QueryIntAttribute("InLaneId", &(tmpVirtualLine.nWayInLaneID));
			pVirtualLaneLineElem->QueryIntAttribute("OutRoadId", &(tmpVirtualLine.nWayOutRoadID));
			pVirtualLaneLineElem->QueryIntAttribute("OutSectionId", &(tmpVirtualLine.nWayOutSectionID));
			pVirtualLaneLineElem->QueryIntAttribute("OutLaneId", &(tmpVirtualLine.nWayOutLaneID));
			pVirtualLaneLineElem->QueryIntAttribute("EdgeId", &(tmpVirtualLine.nLineID));

			//XMLElement* pVirtualLinePoint = pVirtualLaneLineElem->FirstChildElement("Point");
			//for (pVirtualLinePoint; pVirtualLinePoint; pVirtualLinePoint = pVirtualLinePoint->NextSiblingElement("Point"))
			//{
			//	METRoadPoint tmpRoadPt;
			//	pVirtualLinePoint->QueryDoubleAttribute("Lon", &(tmpRoadPt.stPoint.dLongitude));
			//	pVirtualLinePoint->QueryDoubleAttribute("Lat", &(tmpRoadPt.stPoint.dLatitude));
			//	tmpVirtualLine.list_points.push_back(tmpRoadPt);
			//}
			bool bLeft = false;
			if (tmpVirtualLine.nLineID % 2 == 1)
			{
				bLeft = true;
			}
			METRoadPoint StartPoint, EndPoint;
			bool bGetStart = false;
			bool bGetEnd = false;
			for (vector<METRoad>::iterator Road_it = m_stMap.vec_Roads.begin(); Road_it != m_stMap.vec_Roads.end(); Road_it++)
			{
				if (!bGetStart)
				{
					if (Road_it->nRoadID == tmpVirtualLine.nWayInRoadID)
					{
						if (bLeft)
						{
							StartPoint = Road_it->list_sections.back().vec_lines[tmpVirtualLine.nWayInLaneID - 1].list_points.back();
						}
						else
						{
							StartPoint = Road_it->list_sections.back().vec_lines[tmpVirtualLine.nWayInLaneID].list_points.back();
						}
						bGetStart = true;
					}
				}
				if (!bGetEnd)
				{
					if (Road_it->nRoadID == tmpVirtualLine.nWayOutRoadID)
					{
						if (bLeft)
						{
							EndPoint = Road_it->list_sections.front().vec_lines[tmpVirtualLine.nWayOutLaneID - 1].list_points.front();
						}
						else
						{
							EndPoint = Road_it->list_sections.front().vec_lines[tmpVirtualLine.nWayOutLaneID].list_points.front();
						}
						bGetEnd = true;
					}
				}
				if (bGetEnd && bGetStart)
				{
					break;
				}
			}
			tmpVirtualLine.list_points.push_back(StartPoint);
			PointXY local_sPoint, local_ePoint;
			local_sPoint.x = 0.0; local_sPoint.y = 0.0; local_sPoint.theta = (90.0 - StartPoint.fHeading);
			local_ePoint = GCS2CCS(StartPoint.stPoint.dLatitude, StartPoint.stPoint.dLongitude, EndPoint.stPoint.dLatitude, EndPoint.stPoint.dLongitude);
			local_ePoint.theta = (90.0 - EndPoint.fHeading);
			int PointNum = int(floor(Distance(local_ePoint)));
			vector<PointXY> local_VecPoints = m_stMapGraph.GenerateBezier(&local_sPoint, &local_ePoint, PointNum);
			vector<PointXY>::iterator lp_it = local_VecPoints.begin();
			lp_it++;
			for (; lp_it != local_VecPoints.end(); lp_it++)
			{
				PointXY Pt;
				Pt = CCS2GCS(StartPoint.stPoint.dLatitude, StartPoint.stPoint.dLongitude, double(lp_it->x), double(lp_it->y));
				METRoadPoint tmpPt;
				tmpPt.stPoint.dLatitude = Pt.y;
				tmpPt.stPoint.dLongitude = Pt.x;
				tmpVirtualLine.list_points.push_back(tmpPt);
			}
			tmpInterSection.vec_VirtualLaneLines.push_back(tmpVirtualLine);
		}
		//Stopline
		XMLElement* pStopLineElem = pInterSectionElem->FirstChildElement("StopLine");
		XMLElement* pStopLineDataElem = pStopLineElem->FirstChildElement("Line");
		for (pStopLineDataElem; pStopLineDataElem; pStopLineDataElem = pStopLineDataElem->NextSiblingElement("Line"))
		{
			METStopLine tmpStopLine;
			pStopLineDataElem->QueryIntAttribute("InRoadId", &(tmpStopLine.nLinkedRoadID));

			XMLElement* pStopLinePointElem = pStopLineDataElem->FirstChildElement("Point");
			for (pStopLinePointElem; pStopLinePointElem; pStopLinePointElem = pStopLinePointElem->NextSiblingElement("Point"))
			{
				int iID = 0;
				pStopLinePointElem->QueryIntAttribute("Id", &iID);
				if (iID == 1)
				{
					pStopLinePointElem->QueryDoubleAttribute("Lon", &(tmpStopLine.StartPoint.dLongitude));
					pStopLinePointElem->QueryDoubleAttribute("Lat", &(tmpStopLine.StartPoint.dLatitude));
				}
				if (iID == 4)
				{
					pStopLinePointElem->QueryDoubleAttribute("Lon", &(tmpStopLine.EndPoint.dLongitude));
					pStopLinePointElem->QueryDoubleAttribute("Lat", &(tmpStopLine.EndPoint.dLatitude));
				}
			}

			tmpInterSection.vec_stoplines.push_back(tmpStopLine);
		}
		m_stMap.vec_InterSections.push_back(tmpInterSection);
	}
	delete pdoc;
//Process the loaded map
	ProcessMap();
	return;
}

void CLineProcessor::CreateGraph()
{
	m_stMapGraph.InitMapGraph(m_stMap.vec_InterSections.size(), DG);
	vector<METIntersection>::iterator it = m_stMap.vec_InterSections.begin();
	int index = 1;//@todo
	for (; it != m_stMap.vec_InterSections.end(); it++)
	{
		m_stMapGraph.m_vecVerteices[index].cTypeData = "G";
		m_stMapGraph.m_vecVerteices[index].iNodeID = it->nIntersectionID;
		vector<METIntersection>::iterator s_it = it + 1;
		int NextIndex = index + 1;
		
		for (; s_it != m_stMap.vec_InterSections.end(); s_it++)
		{
			bool bConnected = false;
			vector<ROAD_CONNECTION>::iterator connection_it = it->vec_RoadConnections.begin();//vector<int>::iterator OutID_it = it->vec_OutRoadID.begin();
			for (; connection_it != it->vec_RoadConnections.end(); connection_it++)
			{
				if (bConnected)
				{
					break;
				}
				for (vector<ROAD_CONNECTION_OUT>::iterator o_it = connection_it->vec_RoadOuts.begin(); o_it != connection_it->vec_RoadOuts.end(); o_it++)
				{
					if (bConnected)
					{
						break;
					}
					vector<ROAD_CONNECTION>::iterator InID_it = s_it->vec_RoadConnections.begin();
					for (; InID_it != s_it->vec_RoadConnections.end(); InID_it++)
					{
						if (o_it->iOutRoadID == InID_it->iInRoadID)
						{
							m_stMapGraph.InsertArc(index, NextIndex, 0);
							bConnected = true;
							break;
						}
					}
				}
			}
			//for (; OutID_it != it->vec_OutRoadID.end(); OutID_it++)
			//{
			//	vector<int>::iterator InID_it = s_it->vec_InRoadID.begin();
			//	for (; InID_it != s_it->vec_InRoadID.end(); InID_it++)
			//	{
			//		if (*(OutID_it) == *(InID_it))
			//		{
			//			m_stMapGraph.InsertArc(index, NextIndex, 0);
			//			break;
			//		}
			//	}
			//}
			NextIndex++;
		}
		index++;
	}
	//@todo
	m_stMapGraph.InsertArc(0, 1, 0);
	return;
}

void CLineProcessor::DecodeVehiclePosture(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxVehPosture.lock();
	m_msgVehPosture.decode(recvBuf->data, 0, recvBuf->data_size);
	if (!m_bPostureReceived)
	{
		m_bPostureReceived = true;
		m_dLastHeading = m_msgVehPosture.dHeading;
		m_iLastRecvPosTime = m_msgVehPosture.stheader.nTimeStamp;
	}
	else
	{
		if (abs(m_msgVehPosture.stheader.nTimeStamp - m_iLastRecvPosTime) > 1000000)
		{
			m_bPostureReceived = false;
		}
		else
		{
			double dDeltaTheta = abs(m_msgVehPosture.dHeading - m_dLastHeading);
			if (dDeltaTheta > 180)
			{
				dDeltaTheta = 360 - dDeltaTheta;
			}
			if (dDeltaTheta > 10)
			{
				m_msgVehPosture.dHeading = m_dLastHeading;
			}
			else
			{
				m_dLastHeading = m_msgVehPosture.dHeading;
			}
		}
	}
#ifdef COUTCALTIME
	int64_t start_t, end_t;
	start_t = timestamp_now();
#endif // COUTCALTIME
	PointXY currentPoint;
	currentPoint.x = m_msgVehPosture.dLatitude;
	currentPoint.y = m_msgVehPosture.dLongitude;
	if (!m_bIsCurrentPosGet)
	{
		m_iStartNodeID = GetLocateNodeID(currentPoint,false);
		m_iCurrentPathIndex = 0;
		m_stMapGraph.DeepFirstSearch(m_iStartNodeID, m_iDestinationNodeID);
		GetNextStatus();
		m_bIsCurrentPosGet = true;
	}
	else
	{
		GetMapPos(currentPoint);
	}

	double dDis2Line = -1.0;
	if (m_stMapPos.bOnRoad)
	{
		int iLeftID = 0;
		for (vector<METLine>::iterator Lit = m_pCurrentSection->vec_lines.begin(); Lit != m_pCurrentSection->vec_lines.end(); Lit++)
		{
			dDis2Line = DistanceVeh2Line(&(*Lit), currentPoint);
			if (dDis2Line < 0)
			{
				dDis2Line = DistanceVeh2Line(&(*(Lit + 1)), currentPoint);
				if (dDis2Line > 0)
				{
					iLeftID = Lit->stKeyIndex.nEdgeNum;
					PublishLineMessage(iLeftID);
					break;
				}
			}
		}
	}
	else
	{
		if (m_stMapPos.iInterSectionID < 0)
		{
			return;
		}
		else
		{
			PointXY tmpPoint;
			list<METRoadPoint> tmpPointsList;
			m_msgMapLines.bLeftLeftLine = false;
			m_msgMapLines.bRightRightLine = false;
//left virtual line
			m_msgMapLines.bLeftLine = true;
			int iIndex = 100;
			int ReIndex = 99;
			vector<PointXY> tmpVecPoints;
			tmpPointsList = m_pLeftVirtualLine->list_points;
			vector<METRoadPoint> nextPointList = m_pNextRoad->list_sections.front().vec_lines[m_pLeftVirtualLine->nWayOutLaneID - 1].vec_points;
			for (vector<METRoadPoint>::iterator iter1 = nextPointList.begin(); iter1 != nextPointList.end(); iter1++)
			{
				tmpPointsList.push_back(*iter1);
			}
			//m_pLeftVirtualLine->list_points.merge(nextPointList);
			bool bGetFirst = false;
			//for (list<METRoadPoint>::iterator it = m_pLeftVirtualLine->list_points.begin(); it != m_pLeftVirtualLine->list_points.end(); it++)
			for (list<METRoadPoint>::iterator it = tmpPointsList.begin(); it != tmpPointsList.end(); it++)
			{
				tmpPoint = GCST2VEH(it->stPoint.dLatitude, it->stPoint.dLongitude, m_msgVehPosture.dLatitude, m_msgVehPosture.dLongitude, m_msgVehPosture.dHeading);
				if (tmpPoint.y >= 0.0)
				{
					if (!bGetFirst)
					{
						bGetFirst = true;
					}
					m_msgMapLines.gfLeftLineX[iIndex] = (float)(tmpPoint.x);
					m_msgMapLines.gfLeftLineY[iIndex] = (float)(tmpPoint.y);
					iIndex++;
				}
				else
				{
					if (!bGetFirst)
					{
						tmpVecPoints.push_back(tmpPoint);
					}
				}
				if (iIndex > 299)
				{
					break;
				}
			}
			for (vector<PointXY>::reverse_iterator re_it = tmpVecPoints.rbegin(); re_it != tmpVecPoints.rend(); re_it++)
			{
				tmpPoint = *re_it;
				m_msgMapLines.gfLeftLineX[ReIndex] = (float)(re_it->x);
				m_msgMapLines.gfLeftLineY[ReIndex] = (float)(re_it->y);
				ReIndex--;
				if (ReIndex < 0)
				{
					break;
				}
			}
			if (ReIndex > 0)
			{
				for (int i = 0; i <= ReIndex; i++)
				{
					m_msgMapLines.gfLeftLineX[i] = (float)(tmpPoint.x);
					m_msgMapLines.gfLeftLineY[i] = (float)(tmpPoint.y);				
				}
			}
			m_msgMapLines.nLeftArrayLength = iIndex - 100;
//right virtual line
			vector<PointXY>().swap(tmpVecPoints);
			vector<METRoadPoint>().swap(nextPointList);
			m_msgMapLines.bRightLine = true;
			iIndex = 100;
			ReIndex = 99;
			tmpPointsList = m_pRightVirtualLine->list_points;
			nextPointList = m_pNextRoad->list_sections.front().vec_lines[m_pLeftVirtualLine->nWayOutLaneID].vec_points;
			for (vector<METRoadPoint>::iterator iter1 = nextPointList.begin(); iter1 != nextPointList.end(); iter1++)
			{
				tmpPointsList.push_back(*iter1);
			}
			bGetFirst = false;
			//for (list<METRoadPoint>::iterator it = m_pRightVirtualLine->list_points.begin(); it != m_pRightVirtualLine->list_points.end(); it++)
			for (list<METRoadPoint>::iterator it = tmpPointsList.begin(); it != tmpPointsList.end(); it++)
			{
				tmpPoint = GCST2VEH(it->stPoint.dLatitude, it->stPoint.dLongitude, m_msgVehPosture.dLatitude, m_msgVehPosture.dLongitude, m_msgVehPosture.dHeading);
				if (tmpPoint.y >= 0.0)
				{
					if (!bGetFirst)
					{
						bGetFirst = true;
					}
					m_msgMapLines.gfRightLineX[iIndex] = (float)(tmpPoint.x);
					m_msgMapLines.gfRightLineY[iIndex] = (float)(tmpPoint.y);
					iIndex++;
				}
				else
				{
					if (!bGetFirst)
					{
						tmpVecPoints.push_back(tmpPoint);
					}
				}
				if (iIndex > 299)
				{
					break;
				}
			}
			for (vector<PointXY>::reverse_iterator re_it = tmpVecPoints.rbegin(); re_it != tmpVecPoints.rend(); re_it++)
			{
				tmpPoint = *re_it;
				m_msgMapLines.gfRightLineX[ReIndex] = (float)(re_it->x);
				m_msgMapLines.gfRightLineY[ReIndex] = (float)(re_it->y);
				ReIndex--;
				if (ReIndex < 0)
				{
					break;
				}
			}
			if (ReIndex > 0)
			{
				for (int i = 0; i <= ReIndex; i++)
				{
					m_msgMapLines.gfRightLineX[i] = (float)(tmpPoint.x);
					m_msgMapLines.gfRightLineY[i] = (float)(tmpPoint.y);
				}
			}
			m_msgMapLines.nRightArrayLength = iIndex - 100;
			m_msgMapLines.header.nCounter = (static_cast<unsigned int> (m_msgMapLines.header.nCounter) + 1) % 65535;
			m_msgMapLines.header.nTimeStamp = timestamp_now();
			m_pLCMPublishLines->publish("MAP_LINES", &m_msgMapLines);
			ResetMessage();
		}
	}
	/*if (m_stMapPos.bOnRoad)
	{
		int iLeftID = 0;
		for (vector<METRoad>::iterator R_it = m_stMap.vec_Roads.begin(); R_it != m_stMap.vec_Roads.end(); R_it++)
		{
			if (R_it->nRoadID == m_stMapPos.iRoadID)
			{
				for (list<METSection>::iterator S_it = R_it->list_sections.begin(); S_it != R_it->list_sections.end(); S_it++)
				{
					if (S_it->nSectionID == m_stMapPos.iSectionID)
					{
						double dDis2Line = -1.0;
						for (vector<METLine>::iterator Lit = S_it->vec_lines.begin(); Lit != S_it->vec_lines.end(); Lit++)
						{
							dDis2Line = DistanceVeh2Line(&(*Lit), currentPoint);
							if (dDis2Line < 0)
							{
								dDis2Line = DistanceVeh2Line(&(*(Lit + 1)), currentPoint);
								if (dDis2Line > 0)
								{
									iLeftID = Lit->stKeyIndex.nEdgeNum;
									break;
								}
							}
						}
						break;
					}
				}
				break;
			}
		}

	}*/
#ifdef COUTCALTIME
	end_t = timestamp_now();
	printf("Cost time is %ld microseconds\n", (end_t - start_t));
#endif // COUTCALTIME
	m_mtxVehPosture.unlock();
}

vector<METRoadPoint> CLineProcessor::ConnectLine(int vectorIndex)
{
	vector<METRoadPoint> vecResult;
	vecResult = m_pCurrentSection->vec_lines.at(vectorIndex).vec_points;
	//if the line num change
	if (!m_pCurrentSection->bConnected)
	{
		int iLastNum, iCurrentNum, iNextNum;
		if (!m_pCurrentSection->pLastSection)//if (!m_pLastSection)
		{
			iLastNum = 0;
		}
		else
		{
			iLastNum = m_pCurrentSection->pLastSection->vec_lines.size(); //iLastNum = m_pLastSection->vec_lines.size();
		}
		if (!m_pCurrentSection->pNextSection)//if (!m_pNextSection)
		{
			iNextNum = 0;
		}
		else
		{
			iNextNum = m_pCurrentSection->pNextSection->vec_lines.size(); //iNextNum = m_pNextSection->vec_lines.size();
		}
		iCurrentNum = m_pCurrentSection->vec_lines.size();

		if (iLastNum != 0)
		{
			if (iLastNum < iCurrentNum)
			{
			}
			if (iLastNum > iCurrentNum)
			{

			}
			if (iLastNum == iCurrentNum)
			{
				vecResult.insert(vecResult.begin(), m_pCurrentSection->pLastSection->vec_lines[vectorIndex].vec_points.begin(), m_pCurrentSection->pLastSection->vec_lines[vectorIndex].vec_points.end());
				//vecResult.insert(vecResult.begin(), m_pLastSection->vec_lines[vectorIndex].vec_points.begin(),m_pLastSection->vec_lines[vectorIndex].vec_points.end());
			}
		}
		if (iNextNum != 0)
		{
			if (iNextNum == iCurrentNum)
			{
				vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.begin(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.end());
				//vecResult.insert(vecResult.end(), m_pNextSection->vec_lines[vectorIndex].vec_points.begin(),m_pNextSection->vec_lines[vectorIndex].vec_points.end());
			}
			else
			{
				if (m_pCurrentSection->pNextSection->vec_pois.size() == 1)
				{
					MET_POI tmpPOI;
					tmpPOI = m_pCurrentSection->pNextSection->vec_pois[0];
					if (tmpPOI.bExist)
					{
						switch (tmpPOI.enType)
						{
						case LINE_SPLIT_LEFT:
							vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex + 1].vec_points.begin(),
								m_pCurrentSection->pNextSection->vec_lines[vectorIndex + 1].vec_points.end());
							break;
						case LINE_SPLIT_RIGHT:
						{
							if ((vectorIndex + 1) == tmpPOI.iConnectedID)
							{
								int k = m_pCurrentSection->pNextSection->vec_lines.size() - 2;
								vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[k].vec_points.begin(),
									m_pCurrentSection->pNextSection->vec_lines[k].vec_points.end());
							}
							else
							{
								vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.begin(),
									m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.end());
							}
							break;
						}
						case LINE_MERGE_LEFT:
						{
							if (vectorIndex > 0)
							{
								vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex - 1].vec_points.begin(),
									m_pCurrentSection->pNextSection->vec_lines[vectorIndex - 1].vec_points.end());
							}
							break;
						}
						case LINE_MERGE_RIGHT:
						{
							if ((vectorIndex + 1) != tmpPOI.iConnectedID)
							{
								vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.begin(),
									m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.end());
							}
							break;
						}
						case LANE_SPLIT_LEFT:
						{
							if ((vectorIndex + 1) <= tmpPOI.iConnectedID)
							{
								vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.begin(),
									m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.end());
							}
							break;
						}
						case LANE_SPLIT_RIGHT:
						{
							if ((vectorIndex + 1) >= tmpPOI.iConnectedID)
							{
								int k = (vectorIndex + 1 - tmpPOI.iConnectedID);
								vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[k].vec_points.begin(),
									m_pCurrentSection->pNextSection->vec_lines[k].vec_points.end());
							}
							break;
						}
						case LANE_MERGE_LEFT:
							vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.begin(),
								m_pCurrentSection->pNextSection->vec_lines[vectorIndex].vec_points.end());
							break;
						case LANE_MERGE_RIGHT:
						{
							int j = tmpPOI.iConnectedID - 1 + vectorIndex;
							vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[j].vec_points.begin(),
								m_pCurrentSection->pNextSection->vec_lines[j].vec_points.end());
							break;
						}
						default:
							break;
						}
					}
					else
					{
						vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[vectorIndex + 1].vec_points.begin(),
							m_pCurrentSection->pNextSection->vec_lines[vectorIndex + 1].vec_points.end());
					}
				}
				else if (m_pCurrentSection->pNextSection->vec_pois.size() == 2)
				{
					MET_POI tmpPOI_1 = m_pCurrentSection->pNextSection->vec_pois[0];
					MET_POI tmpPOI_2 = m_pCurrentSection->pNextSection->vec_pois[1];
					if (tmpPOI_1.enType == LANE_MERGE_RIGHT && tmpPOI_2.enType == LINE_MERGE_RIGHT)
					{
						if ((vectorIndex + 1) != tmpPOI_2.iConnectedID)
						{
							int j = tmpPOI_1.iConnectedID - 1 + vectorIndex;
							vecResult.insert(vecResult.end(), m_pCurrentSection->pNextSection->vec_lines[j].vec_points.begin(),
								m_pCurrentSection->pNextSection->vec_lines[j].vec_points.end());
						}
					}
				}
			}
		}
	}
	return vecResult;
}

void CLineProcessor::InterpolateLine(int vectorIndex, int index)
{
	vector<METRoadPoint> vec_points;
	//vec_points = (m_pCurrentSection->vec_lines.at(vectorIndex).vec_points);
	vec_points = ConnectLine(vectorIndex);
	PointXY tmpPoint;
	vector<METRoadPoint>::iterator it = vec_points.begin();
	bool bGetTheStartIndex = false;
	int iStartIndex = -10;
	for (; it != vec_points.end(); it++)
	{
		tmpPoint = GCST2VEH(it->stPoint.dLatitude, it->stPoint.dLongitude, m_msgVehPosture.dLatitude, m_msgVehPosture.dLongitude, m_msgVehPosture.dHeading);
		if (!bGetTheStartIndex)
		{
			if (tmpPoint.y >= -100)
			{
				bGetTheStartIndex = true;
				iStartIndex = int(floor(tmpPoint.y) + 100);
				switch (index)
				{
				case 1:
					for (int i = 0; i <= iStartIndex; i++)
					{
						m_msgMapLines.gfLeftLeftLineX[i] = (float)(tmpPoint.x);
						m_msgMapLines.gfLeftLeftLineY[i] = (float)(tmpPoint.y);
					}
					break;
				case 2:
					for (int i = 0; i <= iStartIndex; i++)
					{
						m_msgMapLines.gfLeftLineX[i] = (float)(tmpPoint.x);
						m_msgMapLines.gfLeftLineY[i] = (float)(tmpPoint.y);
					}
					break;
				case 3:
					for (int i = 0; i <= iStartIndex; i++)
					{
						m_msgMapLines.gfRightLineX[i] = (float)(tmpPoint.x);
						m_msgMapLines.gfRightLineY[i] = (float)(tmpPoint.y);
					}
					break;
				case 4:
					for (int i = 0; i <= iStartIndex; i++)
					{
						m_msgMapLines.gfRightRightLineX[i] = (float)(tmpPoint.x);
						m_msgMapLines.gfRightRightLineY[i] = (float)(tmpPoint.y);
					}
					break;
				default:
					break;
				}
			}
		}
		else
		{
			iStartIndex++;
			if (iStartIndex < 300)
			{
				switch (index)
				{
				case 1:
					m_msgMapLines.gfLeftLeftLineX[iStartIndex] = (float)(tmpPoint.x);
					m_msgMapLines.gfLeftLeftLineY[iStartIndex] = (float)(tmpPoint.y);
					break;
				case 2:
					m_msgMapLines.gfLeftLineX[iStartIndex] = (float)(tmpPoint.x);
					m_msgMapLines.gfLeftLineY[iStartIndex] = (float)(tmpPoint.y);
					break;
				case 3:
					m_msgMapLines.gfRightLineX[iStartIndex] = (float)(tmpPoint.x);
					m_msgMapLines.gfRightLineY[iStartIndex] = (float)(tmpPoint.y);
					break;
				case 4:
					m_msgMapLines.gfRightRightLineX[iStartIndex] = (float)(tmpPoint.x);
					m_msgMapLines.gfRightRightLineY[iStartIndex] = (float)(tmpPoint.y);
					break;
				default:
					break;
				}
			}
			if (iStartIndex == 299)
			{
				break;
			}
		}
	}
	switch (index)
	{
	case 1:
		m_msgMapLines.nLeftLeftArrayLength = (iStartIndex + 1) - 100;
		break;
	case 2:
		m_msgMapLines.nLeftArrayLength = (iStartIndex + 1) - 100;
		break;
	case 3:
		m_msgMapLines.nRightArrayLength = (iStartIndex + 1) - 100;
		break;
	case 4:
		m_msgMapLines.nRightRightArrayLength = (iStartIndex + 1) - 100;
		break;
	default:
		break;
	}
}

void CLineProcessor::PublishLineMessage(int LeftID)
{
	if (LeftID == 0 || m_pCurrentSection->vec_lines.size() < 2)
	{
		return;
	}
	if (LeftID == 1)
	{
		m_msgMapLines.bLeftLeftLine = false;
		m_msgMapLines.bLeftLine = true;
		m_msgMapLines.nLeftLineType = int(m_pCurrentSection->vec_lines.at(LeftID - 1).enType);
		//vec_points = (m_pCurrentSection->vec_lines.at(0).vec_points);
		InterpolateLine((LeftID - 1), 2);//left line
		if (m_pCurrentSection->vec_lines.size() >= 3)
		{
			m_msgMapLines.bRightLine = true;
			m_msgMapLines.nRightLineType = int(m_pCurrentSection->vec_lines.at(LeftID).enType);
			InterpolateLine((LeftID), 3);//right line
			m_msgMapLines.bRightRightLine = true;
			m_msgMapLines.nRightRightLineType = int(m_pCurrentSection->vec_lines.at(LeftID + 1).enType);
			InterpolateLine((LeftID + 1) , 4);//next right line
		}
		if (m_pCurrentSection->vec_lines.size() == 2)
		{
			m_msgMapLines.bRightLine = true;
			m_msgMapLines.nRightLineType = int(m_pCurrentSection->vec_lines.at(LeftID).enType);
			InterpolateLine((LeftID), 3);
			m_msgMapLines.bRightRightLine = false;
		}
	}
	else if (LeftID >= 2)
	{
		m_msgMapLines.bLeftLeftLine = true;
		m_msgMapLines.nLeftLeftLineType = int(m_pCurrentSection->vec_lines.at(LeftID - 2).enType);
		InterpolateLine((LeftID - 2), 1);
		m_msgMapLines.bLeftLine = true;
		m_msgMapLines.nLeftLineType = int(m_pCurrentSection->vec_lines.at(LeftID - 1).enType);
		InterpolateLine((LeftID - 1), 2);
		if (m_pCurrentSection->vec_lines.size() == 2)
		{
			m_msgMapLines.bRightLine = true;
			m_msgMapLines.nRightLineType = int(m_pCurrentSection->vec_lines.at(LeftID).enType);
			InterpolateLine((LeftID), 3);
			m_msgMapLines.bRightRightLine = false;
		}
		if (m_pCurrentSection->vec_lines.size() >= 3)
		{
			if (LeftID <= (m_pCurrentSection->vec_lines.size() - 1))
			{
				m_msgMapLines.bRightLine = true;
				m_msgMapLines.nRightLineType = int(m_pCurrentSection->vec_lines.at(LeftID).enType);
				InterpolateLine((LeftID), 3);
			}
			if (LeftID <= (m_pCurrentSection->vec_lines.size() - 2))
			{
				m_msgMapLines.bRightRightLine = true;
				m_msgMapLines.nRightRightLineType = int(m_pCurrentSection->vec_lines.at(LeftID + 1).enType);
				InterpolateLine((LeftID + 1), 4);
			}
		}
	}

	if (m_pCurrentSection->bConnected)
	{
		vector<METVirtualLine>::iterator ITE = m_pNextInterSection->vec_VirtualLaneLines.begin();
		for (; ITE != m_pNextInterSection->vec_VirtualLaneLines.end(); ITE++)
		{
			PointXY tmpPoint;
			if (ITE->nWayInRoadID == m_pCurrentRoad->nRoadID && ITE->nWayOutRoadID == m_pNextRoad->nRoadID &&
				ITE->nWayInLaneID == LeftID && ITE->nWayOutLaneID == 1)
			{
				if (ITE->nLineID % 2 == 1)
				{
					m_pLeftVirtualLine = &(*ITE);
					for (list<METRoadPoint>::iterator RP_it = ITE->list_points.begin(); RP_it != ITE->list_points.end(); RP_it++)
					{
						if (m_msgMapLines.nLeftArrayLength < 300)
						{
							tmpPoint = GCST2VEH(RP_it->stPoint.dLatitude, RP_it->stPoint.dLongitude,
								m_msgVehPosture.dLatitude, m_msgVehPosture.dLongitude, m_msgVehPosture.dHeading);
							m_msgMapLines.gfLeftLineX[m_msgMapLines.nLeftArrayLength + 100] = float(tmpPoint.x);
							m_msgMapLines.gfLeftLineY[m_msgMapLines.nLeftArrayLength + 100] = float(tmpPoint.y);
							m_msgMapLines.nLeftArrayLength++;
						}
					}
				}
				else
				{
					m_pRightVirtualLine = &(*ITE);
					for (list<METRoadPoint>::iterator RP_it = ITE->list_points.begin(); RP_it != ITE->list_points.end(); RP_it++)
					{
						if (m_msgMapLines.nRightArrayLength < 300)
						{
							tmpPoint = GCST2VEH(RP_it->stPoint.dLatitude, RP_it->stPoint.dLongitude,
								m_msgVehPosture.dLatitude, m_msgVehPosture.dLongitude, m_msgVehPosture.dHeading);
							m_msgMapLines.gfRightLineX[m_msgMapLines.nRightArrayLength + 100] = float(tmpPoint.x);
							m_msgMapLines.gfRightLineY[m_msgMapLines.nRightArrayLength + 100] = float(tmpPoint.y);
							m_msgMapLines.nRightArrayLength++;
						}
					}
				}
			}
		}
	}

	if (m_enPOIType == LANE_SPLIT_LEFT && m_msgMapLines.bLeftLeftLine)
	{
		if (LeftID >= m_stPOI.iConnectedID)
		{
			m_msgMapLines.gnLaneProperty[0] = 1;
		}
	}
	else if (m_enPOIType == LANE_SPLIT_RIGHT && m_msgMapLines.bRightRightLine)
	{
		if (LeftID <= m_stPOI.iConnectedID)
		{
			m_msgMapLines.gnLaneProperty[2] = 1;
		}
	}
	if (m_pCurrentSection->pNextSection)
	{
		for (vector<MET_POI>::iterator it = m_pCurrentSection->pNextSection->vec_pois.begin(); it != m_pCurrentSection->pNextSection->vec_pois.end(); it++)
		{
			if (it->bExist && it->enType == LINE_MERGE_RIGHT)
			{
				if ((LeftID + 1) == it->iConnectedID && Min(m_msgMapLines.nLeftArrayLength, m_msgMapLines.nRightArrayLength) < 200)
				{
					m_msgMapLines.gnLaneProperty[0] = 1;
				}
			}
			if (it->bExist && it->enType == LINE_MERGE_LEFT)
			{
				if (LeftID == it->iConnectedID && Min(m_msgMapLines.nLeftArrayLength, m_msgMapLines.nRightArrayLength) < 200)
				{
					m_msgMapLines.gnLaneProperty[2] = 1;
				}
			}
		}
		if (m_pCurrentSection->pNextSection->bConnected)
		{
			LaneDiversion enHostDiversion = m_pCurrentSection->pNextSection->vec_lanes[LeftID - 1].enLaneDiversion;
			switch (m_enDesireDirection)
			{
			case GO_STRAIGHT:
				if ((enHostDiversion == LEFT) || (enHostDiversion == LEFT_UTURN) || (enHostDiversion == UTURN))
				{
					m_msgMapLines.gnLaneProperty[2] = 1;
				}
				if (enHostDiversion == RIGHT)
				{
					m_msgMapLines.gnLaneProperty[0] = 1;
				}
				break;
			case LEFT_TURN:
				if ((enHostDiversion != LEFT) && (enHostDiversion != LEFT_UTURN) && (enHostDiversion != LEFT_STRAIGHT_UTURN) && (enHostDiversion != LEFT_STRAIGHT))
				{
					m_msgMapLines.gnLaneProperty[0] = 1;
				}
				break;
			case RIGHT_TURN:
				if ((enHostDiversion != RIGHT) && (enHostDiversion != STRAIGHT_RIGHT))
				{
					m_msgMapLines.gnLaneProperty[2] = 1;
				}
				break;
			case GO_UTURN:
				if ((enHostDiversion != LEFT_STRAIGHT_UTURN) && (enHostDiversion != LEFT_UTURN) && (enHostDiversion != UTURN))
				{
					m_msgMapLines.gnLaneProperty[0] = 1;
				}
				break;
			default:
				break;
			}
		}
	}

	m_msgMapLines.header.nCounter = (static_cast<unsigned int> (m_msgMapLines.header.nCounter) + 1) % 65535;
	m_msgMapLines.header.nTimeStamp = timestamp_now();
	m_pLCMPublishLines->publish("MAP_LINES", &m_msgMapLines);
	ResetMessage();
}

void CLineProcessor::ResetMessage()
{
	for (int i = 0; i < 3; i++)
	{
		m_msgMapLines.gnLaneProperty[i] = 0;
	}
	m_msgMapLines.bLeftLeftLine = false;
	m_msgMapLines.bLeftLine = false;
	m_msgMapLines.bRightLine = false;
	m_msgMapLines.bRightRightLine = false;
	for (size_t i = 0; i < 300; i++)
	{
		m_msgMapLines.gfLeftLeftLineX[i] = 0.0;
		m_msgMapLines.gfLeftLeftLineY[i] = 0.0;
		m_msgMapLines.gfLeftLineX[i] = 0.0;
		m_msgMapLines.gfLeftLineY[i] = 0.0;
		m_msgMapLines.gfRightLineX[i] = 0.0;
		m_msgMapLines.gfRightLineY[i] = 0.0;
		m_msgMapLines.gfRightRightLineX[i] = 0.0;
		m_msgMapLines.gfRightRightLineY[i] = 0.0;
	}
	m_msgMapLines.nLeftArrayLength = 0;
	m_msgMapLines.nLeftLeftArrayLength = 0;
	m_msgMapLines.nRightArrayLength = 0;
	m_msgMapLines.nRightRightArrayLength = 0;
	m_msgMapLines.nLeftLineType = 0;
	m_msgMapLines.nLeftLeftLineType= 0;
	m_msgMapLines.nRightLineType = 0;
	m_msgMapLines.nRightRightLineType= 0;
}

METIntersection* CLineProcessor::GetInterSection(int ID)
{
	for (vector<METIntersection>::iterator it = m_stMap.vec_InterSections.begin(); it != m_stMap.vec_InterSections.end(); it++)
	{
		if (it->nIntersectionID == ID)
		{
			return &(*it);
		}
	}
	return NULL;
}

METRoad* CLineProcessor::GetRoad(int ID1, int ID2)
{
	METIntersection* pFirstIntersection = GetInterSection(ID1);
	METIntersection* pSecondIntersection = GetInterSection(ID2);
	if (!pFirstIntersection || !pSecondIntersection)
	{
		return NULL;
	}
	bool bConnected = false;
	int iRoadID = -1;
	for (vector<ROAD_CONNECTION>::iterator Fit = pSecondIntersection->vec_RoadConnections.begin(); Fit != pSecondIntersection->vec_RoadConnections.end(); Fit++)
	{
		if (bConnected)
		{
			break;
		}
		for (vector<ROAD_CONNECTION>::iterator it = pFirstIntersection->vec_RoadConnections.begin(); it != pFirstIntersection->vec_RoadConnections.end(); it++)
		{
			if (bConnected)
			{
				break;
			}
			for (vector<ROAD_CONNECTION_OUT>::iterator o_it = it->vec_RoadOuts.begin(); o_it != it->vec_RoadOuts.end(); o_it++)
			{
				if (o_it->iOutRoadID == Fit->iInRoadID)
				{
					bConnected = true;
					iRoadID = Fit->iInRoadID;
					break;
				}
			}
		}
	}
	if (iRoadID < 0)
	{
		return NULL;
	}
	else
	{
		for (vector<METRoad>::iterator it = m_stMap.vec_Roads.begin(); it != m_stMap.vec_Roads.end(); it++)
		{
			if (it->nRoadID == iRoadID)
			{
				return &(*it);
			}
		}
		return NULL;
	}
}

void CLineProcessor::GetNextStatus()
{
	m_enDesireDirection = GO_STRAIGHT;
	if (m_iCurrentPathIndex < 0 || m_iCurrentPathIndex >= m_stMapGraph.m_vecPathVerteies.size())
	{
		return;
	}
	if (m_iCurrentPathIndex == m_stMapGraph.m_vecPathVerteies.size()-1)
	{
		m_pNextInterSection = NULL;
		m_pNextRoad = NULL;
		return;
	}
	
	m_pNextInterSection = GetInterSection(m_stMapGraph.m_vecPathVerteies[m_iCurrentPathIndex + 1].iNodeID);
	if (m_stMapPos.bOnRoad)
	{
		if (m_iCurrentPathIndex == m_stMapGraph.m_vecPathVerteies.size() - 2)
		{
			m_pNextRoad = NULL;
			return;
		}
		else
		{
			m_pNextRoad = GetRoad(m_stMapGraph.m_vecPathVerteies[m_iCurrentPathIndex + 1].iNodeID,
				m_stMapGraph.m_vecPathVerteies[m_iCurrentPathIndex + 2].iNodeID);
		}
	}
	else
	{
		if (m_stMapPos.iInterSectionID > 0)
		{
			m_pNextRoad = GetRoad(m_stMapGraph.m_vecPathVerteies[m_iCurrentPathIndex].iNodeID, 
				m_stMapGraph.m_vecPathVerteies[m_iCurrentPathIndex + 1].iNodeID);
		}
		else
		{
			m_pNextRoad = NULL;
		}
		return;
	}

	bool bConnected = false;
	vector<ROAD_CONNECTION>::iterator connection_it = m_pNextInterSection->vec_RoadConnections.begin();
	for (; connection_it != m_pNextInterSection->vec_RoadConnections.end(); connection_it++)
	{
		if (bConnected)
		{
			break;
		}
		if (m_pCurrentRoad->nRoadID == connection_it->iInRoadID)
		{
			vector<ROAD_CONNECTION_OUT>::iterator out_it = connection_it->vec_RoadOuts.begin();
			for (; out_it != connection_it->vec_RoadOuts.end(); out_it++)
			{
				if (out_it->iOutRoadID == m_pNextRoad->nRoadID)
				{
					bConnected = true;
					m_enDesireDirection = out_it->enConnectType;
				}
			}
		}
	}
}