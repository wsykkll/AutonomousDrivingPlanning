#include "LCMHandler.h"


CLCMHandler::CLCMHandler()
{
}


CLCMHandler::~CLCMHandler()
{
}

void CLCMHandler::CallbackESRInfo(const lcm::ReceiveBuffer* recvBuf, const std::string& channelName)
{
	m_stESRProcessor.DecoedeESRMsg(recvBuf);
}