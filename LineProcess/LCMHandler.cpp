#include "LCMHandler.h"


CLCMHandler::CLCMHandler()
{
}


CLCMHandler::~CLCMHandler()
{
}

void CLCMHandler::CallbackVehiclePosture(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stLineProcessor.DecodeVehiclePosture(recvBuf);
}
