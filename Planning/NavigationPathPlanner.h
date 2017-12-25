#pragma once
#include "PerceptionLines.h"
#include "PerceptionObstacles.h"
#include "global.hpp"
#include "Notation.h"
#include "CoordinateTrans.h"

enum GridInLane
{
	LEFT_LANE,
	HOST_LANE,
	RIGHT_LANE
};

class CNavigationPathPlanner
{
public:
	CNavigationPathPlanner();
	~CNavigationPathPlanner();
	void IDLaneKeep();
	void IDLaneLeftChange();
	void IDLaneRightChange();
	void GetVehicleSpeed(float vehSpeed);
	void GetLaneGrid(LaneGrid lanegrid);
	void GetObstacles(vector<Obstacle> obstacles);
	void GenerateVehicleGridID();
	void GenerateNavigationPath();
	vector<PointXY> GetNavigationPath();

	double PursuitByDeltaX(double deltax, double dis);
	vector<PointXY> PathInterpolate(vector<PointXY> PathData);
	vector<PointXY> LocalPathPlan(vector<PointXY> PathData, int PreviewDis);
private:
	bool m_bIsRightShiftHalfgrid;
	bool m_bIsAdjustedBackObs;
	bool m_bIsAdjustedFrontObs;
	int m_iBackLineRange;
	float m_fVehicleSpeed;
	LaneGrid m_stLaneGrid;
	vector<Obstacle> m_vecObstacles;
	vector<PointXY> m_vecNavigationPath;
	GridInLane m_enGridInLane;
	int m_iSelectedGridID;
	int m_iVehicleCurrentGridID;
	int m_iGridShiftLimit;
	int m_iGridShiftNumLaneChange;
	int m_iVehicleOccupyGrid;
	int m_iLeftMaxIDLaneKeep;
	int m_iLeftMaxIDDangerous;
	int m_iLeftForbiddenID;
	int m_iRightMaxIDLaneKeep;
	int m_iRightMaxIDDangerous;
	int m_iRightForbiddenID;

	int MatchXInGrid(float x, Base base);
	void GenerateMaxIDLaneKeep();
	void GenerateMaxIDDangerous();
	float GetLeftLaneFreespace();
	float GetRightLaneFreespace();
	int RightIDLeftLane(Obstacle obs);
	int LeftIDRightLane(Obstacle obs);
	void GenerateGridShiftLimit();
	void GenerateGridShiftNumLaneChange();
	int IDLeftSide(Obstacle obs);
	int IDRightSide(Obstacle obs);
};

