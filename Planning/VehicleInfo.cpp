#include "VehicleInfo.h"

VehicleInfoData gVehcleInfo;
shared_mutex gVehicleInfoMutex;

CVehicleInfo::CVehicleInfo()
{
	m_bIsThreadRun = true;
}


CVehicleInfo::~CVehicleInfo()
{
}

bool CVehicleInfo::InitializeLCM()
{
	m_iLastRecvTime = timestamp_now();
	m_stVehicleInfo.iLastTimeStamp = m_iLastRecvTime;
	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
	if (!m_pLCM->good())
	{
		return false;
	}
	return true;
}

void CVehicleInfo::SetThreadState(bool state)
{
	m_bIsThreadRun = state;
}

void CVehicleInfo::VehicleInfoRun()
{
	while (m_bIsThreadRun)
	{
		m_stVehicleInfo.iHandlerReturn = m_pLCM->handleTimeout(500);
		if (m_stVehicleInfo.iHandlerReturn > 0)
		{
			//m_stVehicleInfo.bMessageReveive = true;
			//unique_lock<shared_mutex> vcuLock(gVehicleInfoMutex);
			//gVehcleInfo = m_stVehicleInfo;
			//vcuLock.unlock();
		}
		else if (m_stVehicleInfo.iHandlerReturn == 0)
		{
			m_stVehicleInfo.bMessageReveive = false;
			m_stVehicleInfo.bMessageLost = true;
			m_stVehicleInfo.iMessageLostCounter = MESSAGELOST_COUNTER*MESSAGELOST_RATIO;
			unique_lock<shared_mutex> vcuLock(gVehicleInfoMutex);
			gVehcleInfo = m_stVehicleInfo;
			vcuLock.unlock();
		}
		else
		{
			m_stVehicleInfo.bMessageReveive = false;
			unique_lock<shared_mutex> vcuLock(gVehicleInfoMutex);
			gVehcleInfo = m_stVehicleInfo;
			vcuLock.unlock();
		}
	}
}

void CVehicleInfo::LCMHandler(const lcm::ReceiveBuffer* recvBuf, const string& channelName, const METPublisCANEvent_Lcm* msg)
{
	//m_msgVehicleInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	if (strcmp(channelName.data(), "VehicleInfo_vehicle_speed") == 0)
	{
		m_iRecvTime = timestamp_now();
		m_stVehicleInfo.fSpeed = msg->messageval;
		if (m_iRecvTime - m_iLastSpeedTimeStamp > 0)
		{
			if (fabs(m_stVehicleInfo.fSpeed-m_fLastSpeed)<1e-2)
			{
				m_stVehicleInfo.fAcc = 0.0f;
			}
			else
			{
				double dDeltaTime = (m_iRecvTime - m_iLastRecvTime) / 1000000.0;
				//printf("Delta time is %lf\n", dDeltaTime);
				m_stVehicleInfo.fAcc = (m_stVehicleInfo.fSpeed - m_fLastSpeed) / dDeltaTime;
			}
		}
		m_fLastSpeed = m_stVehicleInfo.fSpeed;
		m_iLastRecvTime = m_iRecvTime;
	}
	if (strcmp(channelName.data(),"VehicleInfo_steering_wheel_angle") == 0)
	{
		m_stVehicleInfo.fSteeringWheelAngle = msg->messageval;
	}
	if (strcmp(channelName.data(), "VehicleInfo_vehicle_yaw_rate") == 0)
	{
		m_stVehicleInfo.fYawRate = msg->messageval;
	}

	writeLock lock(gVehicleInfoMutex);
	gVehcleInfo = m_stVehicleInfo;
	lock.unlock();
}