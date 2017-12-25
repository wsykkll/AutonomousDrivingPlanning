#pragma once
#include "Notation.h"
#include "global.hpp"
#include "METPublisCANEvent_Lcm.hpp"

struct VehicleInfoData
{
	bool bMessageReveive;
	bool bMessageLost;
	int64_t iCounter;
	int64_t iLastCounter;
	int64_t iTimeStamp;
	int64_t iLastTimeStamp;
	int32_t iMessageLostCounter;

	float fSteeringWheelAngle;
	float fYawRate;
	float fSpeed;
	float fAcc;
	int32_t iHandlerReturn;

	VehicleInfoData()
	{
		bMessageLost = false;
		bMessageReveive = true;
		iCounter = 0;
		iLastCounter = 0;
		iTimeStamp = 0;
		iLastTimeStamp = 0;

		fSteeringWheelAngle = 0.0f;
		fYawRate = 0.0f;
		fSpeed = 0.0f;
		iHandlerReturn = 0;
	}
};

extern VehicleInfoData gVehcleInfo;
extern shared_mutex gVehicleInfoMutex;

class CVehicleInfo
{
public:
	CVehicleInfo();
	~CVehicleInfo();
	VehicleInfoData m_stVehicleInfo;
	//METPublisCANEvent_Lcm m_msgVehicleInfo;
	int64_t m_iLastRecvTime;

	lcm::LCM* m_pLCM;
	bool InitializeLCM();
	void LCMHandler(const lcm::ReceiveBuffer* recvBuf, const string& channelName,const METPublisCANEvent_Lcm* msg);

	void SetThreadState(bool state);
	void VehicleInfoRun();
private:
	bool m_bIsThreadRun;
	float m_fLastSpeed;
	int64_t m_iLastSpeedTimeStamp;
	int64_t m_iRecvTime;
};

