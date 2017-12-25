#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum GraphKind
{
	DG,//direction graph
	WDG,//weighted direction graph
	UDG,//none direction graph
	WUDG//weighted none direction graph
};

struct ArcNode
{
	int iAdjVertex;
	ArcNode* pNextArc;
	int info;
};

struct VertexNode
{
	char cTypeData;
	ArcNode* pFirstArc;
};

class CMapGraph
{
public:
	CMapGraph();
	~CMapGraph();

	int m_iVertexNum;//the num of vertex node
	int m_iEdgeNum;//the num of edge node
	GraphKind m_enGraphKind;
	vector<VertexNode> m_vecVerteices;

	void InitMapGraph(int iVertexNum, GraphKind _kind);
	void InsertArc(int iVHead, int iVTail, int iWeight);
	//void CreateGraph();
private:
	
	//void CreateDG();
	//void CreateWDG();
	//void CreateUDG();
	//void CreateWUDG();
};

