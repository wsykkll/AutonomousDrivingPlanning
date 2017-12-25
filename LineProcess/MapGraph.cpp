#include "MapGraph.h"


CMapGraph::CMapGraph()
{
}


CMapGraph::~CMapGraph()
{
}

void CMapGraph::InitMapGraph(int iVertexNum, GraphKind _kind)
{
	m_iVertexNum = iVertexNum + 1;//@todo
	m_iEdgeNum = 0;
	m_enGraphKind = _kind;
	VertexNode tmpVertexNode;
	tmpVertexNode.cTypeData = "G";
	tmpVertexNode.iNodeID = 0;
	m_vecVerteices.push_back(tmpVertexNode);
	m_vecNodeIsVisited.push_back(false);
	for (int i = 1; i < m_iVertexNum; i++)
	{
		//m_vecVerteices[i].pFirstArc = NULL;
		m_vecVerteices.push_back(tmpVertexNode);
		m_vecNodeIsVisited.push_back(false);
	}
}

//void CMapGraph::CreateGraph()
//{
//	switch (m_enGraphKind)
//	{
//	case DG:
//		CreateDG();
//		break;
//	case WDG:
//		CreateWDG();
//		break;
//	case UDG:
//		CreateUDG();
//		break;
//	case WUDG:
//		CreateWUDG();
//		break;
//	default:
//		break;
//	}
//}

void CMapGraph::InsertArc(int iVHead, int iVTail, int iWeight)
{
	ArcNode* newArcNode = new ArcNode();
	newArcNode->iAdjVertexIndex = iVTail;
	newArcNode->pNextArc = NULL;
	newArcNode->info = iWeight;

	ArcNode* pArcNode = m_vecVerteices[iVHead].pFirstArc;
	if (pArcNode == NULL)
	{
		m_vecVerteices[iVHead].pFirstArc = newArcNode;
	}
	else
	{
		while (pArcNode->pNextArc != NULL)
		{
			pArcNode = pArcNode->pNextArc;
		}
		pArcNode->pNextArc = newArcNode;
	}
	m_iEdgeNum++;
}

void CMapGraph::DisplayGraph()
{
	for (size_t i = 0; i < m_iVertexNum; i++)
	{
		cout << "Vertex Node " << i + 1 << "is " << m_vecVerteices[i].cTypeData << endl;
		if (!m_vecVerteices[i].pFirstArc)
		{
			cout << m_vecVerteices[i].pFirstArc->iAdjVertexIndex;
		}
	}
}

void CMapGraph::DFS(int v)
{
	ArcNode* pArcNode;
	m_vecPathVerteies.push_back(m_vecVerteices[v]);
	if (v == m_iEndNodeIndex)
	{
		return;
	}
	m_vecNodeIsVisited[v] = true;
	pArcNode = m_vecVerteices[v].pFirstArc;
	while (pArcNode)
	{
		if (!m_vecNodeIsVisited[pArcNode->iAdjVertexIndex])
		{
			DFS(pArcNode->iAdjVertexIndex);
		}
		pArcNode = pArcNode->pNextArc;
	}
}

void CMapGraph::BFS(int v)
{
	ArcNode* pArcNode;
	queue<int> iQueue;
	vector<bool> vecFlag;
	for (size_t i = 0; i < m_iVertexNum; i++)
	{
		vecFlag.push_back(false);
	}
	m_vecPathVerteies.push_back(m_vecVerteices[v]);
	vecFlag[v] = true;
	iQueue.push(v);
	int w;
	while (!iQueue.empty())
	{
		w = iQueue.front();
		iQueue.pop();
		pArcNode = m_vecVerteices[w].pFirstArc;
		while (pArcNode)
		{
			if (!vecFlag[pArcNode->iAdjVertexIndex])
			{
				m_vecVerteices.push_back(m_vecVerteices[pArcNode->iAdjVertexIndex]);
				vecFlag[pArcNode->iAdjVertexIndex] = true;
				iQueue.push(pArcNode->iAdjVertexIndex);
			}
			pArcNode = pArcNode->pNextArc;
		}
	}
}

void CMapGraph::DeepFirstSearch(int StartNodeID, int EndNodeID)
{
	//the start node ID and end node ID to Index
	int StartIndex;
	for (size_t i = 0; i < m_iVertexNum; i++)
	{
		if (m_vecVerteices[i].iNodeID == StartNodeID)
		{
			StartIndex = i;
		}
		if (m_vecVerteices[i].iNodeID == EndNodeID)
		{
			m_iEndNodeIndex = i;
		}
	}
	DFS(StartIndex);
}

void CMapGraph::BreadthFirstSearch(int StartIndex, int EndIndex)
{

}

double CMapGraph::CrossMulti(PointXY p1, PointXY p2, PointXY p0)
{
	return (p1.x - p0.x)*(p2.y - p0.y) - (p2.x - p0.x)*(p1.y - p0.y);
}

double CMapGraph::PointMulti(PointXY p1, PointXY p2, PointXY p0)
{
	return (p1.x - p0.x)*(p2.x - p0.x) + (p1.y - p0.y)*(p2.y - p0.y);
}

inline bool CMapGraph::IsOnline(PointXY p, Segment segment)
{
	if ((fabs(CrossMulti(segment.SPoint, p, segment.EPoint)) <= MIN_E) && (p.x <= Max(segment.SPoint.x, segment.EPoint.x)) &&
		(Min(segment.SPoint.y, segment.EPoint.y) <= p.y) && (p.y <= Max(segment.SPoint.y, segment.EPoint.y)))
	{
		return true;
	}
	return false;
}

inline bool CMapGraph::IsSegmentCrossing(Segment s1, Segment s2)
{
	return ((Max(s1.SPoint.x, s1.EPoint.x) >= Min(s2.SPoint.x, s2.EPoint.x)) &&
		(Max(s2.SPoint.x, s2.EPoint.x) >= Min(s1.SPoint.x, s1.EPoint.x)) &&
		(Max(s1.SPoint.y, s1.EPoint.y) >= Min(s2.SPoint.y, s2.EPoint.y)) &&
		(Max(s2.SPoint.y, s2.EPoint.y) >= Min(s1.SPoint.y, s1.EPoint.y)) &&
		(CrossMulti(s2.SPoint, s1.EPoint, s1.SPoint)*CrossMulti(s1.EPoint, s2.EPoint, s1.SPoint) >= 0) &&
		(CrossMulti(s1.SPoint, s2.EPoint, s2.SPoint)*CrossMulti(s2.EPoint, s1.EPoint, s2.SPoint) >= 0));
}

bool CMapGraph::IsInArea(PointXY pt, vector<PointXY> vecPt)
{
	Segment tmpSeg;
	Segment segRay;
	int num = 0;
	PointXY MaxPoint;
	MaxPoint.y = pt.y;
	MaxPoint.x = MAX_E;
	segRay.SPoint = pt;
	segRay.EPoint = MaxPoint;
	for (size_t i = 0; i < vecPt.size(); i++)
	{
		tmpSeg.SPoint = vecPt[i];
		tmpSeg.EPoint = vecPt[(i + 1) % vecPt.size()];
		if (IsOnline(pt,tmpSeg))
		{
			return true;
		}
		if (fabs(tmpSeg.SPoint.y - tmpSeg.EPoint.y) < MIN_E)
		{
			continue;
		}
		if (IsOnline(tmpSeg.SPoint,segRay))
		{
			if (tmpSeg.SPoint.y > tmpSeg.EPoint.y)
			{
				num++;
			}
		}
		else if (IsOnline(tmpSeg.EPoint,segRay))
		{
			if (tmpSeg.EPoint.y > tmpSeg.SPoint.y)
			{
				num++;
			}
		}
		else if (IsSegmentCrossing(segRay, tmpSeg))
		{
			num++;
		}
	}
	if (num % 2 == 1)
	{
		return true;
	}
	return false;
}

PointXY CMapGraph::CrossPoint(PointXY p1, PointXY p2)
{
	if (p1.theta < 0)
	{
		p1.theta = p1.theta + 360;
	}
	if (p2.theta < 0)
	{
		p2.theta = p2.theta + 360;
	}
	PointXY RePoint;
	double dDeltaTheta = fabs(p2.theta - p1.theta);
	if (dDeltaTheta < 0.5)
	{

	}
	else if (fabs(dDeltaTheta - 180) < 0.5)
	{
		RePoint.x = (p1.x + p2.x) / 2.0;
		RePoint.y = (p1.y + p2.y) / 2.0;
	}
	else
	{
		double t1 = tan(p1.theta*DEGREE_TO_RADIAN);
		double t2 = tan(p2.theta*DEGREE_TO_RADIAN);
		RePoint.x = (t1*p1.x - t2*p2.x + p2.y - p1.y) / (t1 - t2);
		RePoint.y = t1*(RePoint.x - p1.x) + p1.y;
	}
	return RePoint;
}

vector<PointXY> CMapGraph::GenerateBezier(PointXY* Anchor1, PointXY* Anchor2, int pointNum)
{
	PointXY controlPoint = CrossPoint(*Anchor1, *Anchor2);
	vector<PointXY> returnVecPoints;
	PointXY tmpPoint;
	//returnVecPoints.push_back(*Anchor1);
	float step = 1.0 / float(pointNum);
	for (int i = 1; i < pointNum; i++)
	{
		float t = i*step;
		tmpPoint.x = (1 - t)*(1 - t)*Anchor1->x + 2 * t*(1 - t)*controlPoint.x + t*t*Anchor2->x;
		tmpPoint.y = (1 - t)*(1 - t)*Anchor1->y + 2 * t*(1 - t)*controlPoint.y + t*t*Anchor2->y;
		returnVecPoints.push_back(tmpPoint);
	}
	returnVecPoints.push_back(*Anchor2);
	return returnVecPoints;
}