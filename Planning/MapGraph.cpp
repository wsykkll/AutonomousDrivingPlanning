#include "MapGraph.h"


CMapGraph::CMapGraph()
{
}

CMapGraph::~CMapGraph()
{
}

void CMapGraph::InitMapGraph(int iVertexNum, GraphKind _kind)
{
	m_iVertexNum = iVertexNum;
	m_iEdgeNum = 0;
	m_enGraphKind = _kind;
	for (unsigned int i = 0; i < m_iVertexNum; i++)
	{
		m_vecVerteices[i].pFirstArc = NULL;
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
	newArcNode->iAdjVertex = iVTail;
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