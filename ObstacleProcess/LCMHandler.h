#pragma once
#include "ESRProcess.h"

class CLCMHandler
{
public:
	CLCMHandler();
	~CLCMHandler();
	void CallbackESRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);
private:
	CESRProcess m_stESRProcessor;
};

