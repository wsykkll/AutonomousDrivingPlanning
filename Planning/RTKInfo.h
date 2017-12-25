#pragma once
#include "METGPSInfo_Lcm.hpp"
#include "global.hpp"
#include "Notation.h"

struct RTKData
{
	bool bMsgConnected;//whether receive the perception line data
	bool bMsgLost;//whether drop frame
	int16_t iCounter;
	int16_t iLastCounter;
	int64_t iTimeStamp;
	int64_t iLastTimeStamp;
	int16_t iMsgLostNum;//the num of drop frame

	int iRTKStatus;//4:fixed 6:INS integration
	double dLatitude;
	double dLongitude;
	float fSpeed;
	float fDirection;
	float fRoll;
	float fPitch;
	int iHandlerReturn;

	RTKData()
	{
		bMsgConnected = false;
		bMsgLost = false;
		iCounter = 0;
		iLastCounter = 0;
		iTimeStamp = 0;
		iLastTimeStamp = 0;
		iMsgLostNum = 0;

		iRTKStatus = 0;//invalid
		dLatitude = 0.0;
		dLongitude = 0.0;
		fSpeed = 0.0f;
		fDirection = 0.0f;
		fRoll = 0.0f;
		fPitch = 0.0f;
		iHandlerReturn = 0;
	}
};

extern RTKData g_RTKData;
extern shared_mutex gRTKMutex;

class CRTKInfo
{
public:
	CRTKInfo();
	~CRTKInfo();

	RTKData m_msgRTKData;
	int64_t m_iLastRecvTimeStamp;
	int64_t m_iCurrentRecvTimeStamp;

	lcm::LCM* m_pLCM;
	void LCMHandler(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const METGPSInfo_Lcm* msg);
	bool InitializeLCM();
	void SetThreadState(bool state);
	void RTKInfoRun();
private:
	bool m_bIsThreadRun;
};

