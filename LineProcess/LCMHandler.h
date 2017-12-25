#pragma once
#include "global.hpp"
#include "VehiclePosture.hpp"
#include "LineProcessor.h"

class CLCMHandler
{
public:
	CLCMHandler();
	~CLCMHandler();

	void CallbackVehiclePosture(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName);

private:
	CLineProcessor m_stLineProcessor;
};

