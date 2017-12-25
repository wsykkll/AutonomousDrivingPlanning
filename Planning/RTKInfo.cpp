#include "RTKInfo.h"

RTKData g_RTKData;
shared_mutex gRTKMutex;

CRTKInfo::CRTKInfo()
{
	m_bIsThreadRun = true;
}


CRTKInfo::~CRTKInfo()
{
}

bool CRTKInfo::InitializeLCM()
{
	m_iLastRecvTimeStamp = timestamp_now();
	m_msgRTKData.iLastTimeStamp = m_iLastRecvTimeStamp;
	m_pLCM = new lcm::LCM("udpm://239.255.76.67:7667?ttl=0");
	if (!m_pLCM->good())
	{
		printf("Cannot initialize LCM, please check the network Connection\n");
		return false;
	}
	return true;
}

void CRTKInfo::LCMHandler(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName, const METGPSInfo_Lcm* msg)
{
	m_msgRTKData.bMsgConnected = true;
	m_msgRTKData.iLastTimeStamp = m_msgRTKData.iTimeStamp;
	m_msgRTKData.iLastCounter = m_msgRTKData.iCounter;
	m_msgRTKData.iTimeStamp = msg->header.nTimeStamp;
	m_msgRTKData.iCounter = msg->header.nCounter;
	m_msgRTKData.dLatitude = msg->GGA_dwLat;
	m_msgRTKData.dLongitude = msg->GGA_dwLon;
	m_msgRTKData.fDirection = msg->TRA_dwHeading;
	m_msgRTKData.fPitch = msg->TRA_dwPitch;
	m_msgRTKData.fRoll = msg->TRA_nRoll;
	m_msgRTKData.fSpeed = msg->RMC_dwSpeedIn*0.5144f*3.6f;

	//if ((m_msgRTKData.iCounter - m_msgRTKData.iLastCounter) != 1 && (m_msgRTKData.iCounter - m_msgRTKData.iLastCounter) != -65534)
	//{
	//	m_msgRTKData.iMsgLostNum++;
	//	if (m_msgRTKData.iMsgLostNum > MESSAGELOST_COUNTER)
	//	{
	//		m_msgRTKData.iMsgLostNum = MESSAGELOST_COUNTER;
	//	}
	//}
	//else
	//{
	//	m_msgRTKData.iMsgLostNum--;
	//	if (m_msgRTKData.iMsgLostNum < 0)
	//	{
	//		m_msgRTKData.iMsgLostNum = 0;
	//	}
	//}
	//if (m_msgRTKData.iMsgLostNum >= MESSAGELOST_COUNTER*MESSAGELOST_RATIO)
	//{
	//	m_msgRTKData.bMsgLost = true;
	//}
	//if (m_msgRTKData.iMsgLostNum == 0)
	//{
	//	m_msgRTKData.bMsgLost = false;
	//}

	unique_lock<shared_mutex> RTKInfoLock(gRTKMutex);
	g_RTKData = m_msgRTKData;
	RTKInfoLock.unlock();
}

void CRTKInfo::SetThreadState(bool state)
{
	m_bIsThreadRun = state;
}

void CRTKInfo::RTKInfoRun()
{
	while (m_bIsThreadRun)
	{
		m_msgRTKData.iHandlerReturn = m_pLCM->handleTimeout(500);
		if (m_msgRTKData.iHandlerReturn > 0)
		{
			//m_msgRTKData.bMsgConnected = true;
			//unique_lock<shared_mutex> lock(gRTKMutex);
			//g_RTKData = m_msgRTKData;
			//lock.unlock();
		}
		else if (m_msgRTKData.iHandlerReturn == 0)
		{
			m_msgRTKData.bMsgConnected = false;
			m_msgRTKData.bMsgLost = true;
			m_msgRTKData.iMsgLostNum = MESSAGELOST_COUNTER * MESSAGELOST_RATIO;
			unique_lock<shared_mutex> lock(gRTKMutex);
			g_RTKData = m_msgRTKData;
			lock.unlock();
		}
		else
		{
			m_msgRTKData.bMsgConnected = false;
			unique_lock<shared_mutex> lock(gRTKMutex);
			g_RTKData = m_msgRTKData;
			lock.unlock();
			break;
		}
	}
}
