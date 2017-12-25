#pragma once
#include "global.hpp"

struct RealSpeed
{
	bool bIsConnected;
	float fSpeedLeft;
	float fSpeedRight;
	float fSpeed;
	float fVot;
	int iShift;
	float fDis2Left;
	float fDis2Right;
	RealSpeed()
	{
		bIsConnected = false;
		fSpeedLeft = 0.0f;
		fSpeedRight = 0.0f;
		fSpeed = 0.0f;
		fVot = 0.0f;
		iShift = 0;
		fDis2Left = 0.0f;
		fDis2Right = 0.0f;
	}
};


struct DesignSpeed
{
	float fSpeed;
	int iModle;
	DesignSpeed()
	{
		fSpeed = 0.0f;
		iModle = 0;
	}
};

struct RealSteer
{
	bool bIsConnected;
	int iSpeed;
	int iPosition;
	RealSteer()
	{
		bIsConnected = false;
		iSpeed = 0;
		iPosition = 0;
	}
};

struct DesignSteer
{
	int iSpeed;
	int iPosition;
	DesignSteer()
	{
		iSpeed = 0;
		iPosition = 0;
	}
};

extern RealSteer gRealSteer;
extern RealSpeed gRealSpeed;
extern shared_mutex gSteerMutex;
extern shared_mutex gSpeedMutex;

class CVehControl
{
public:
	CVehControl();
	~CVehControl();
};

