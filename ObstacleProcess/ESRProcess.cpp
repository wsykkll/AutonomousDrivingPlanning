#include "ESRProcess.h"


CESRProcess::CESRProcess()
{
}


CESRProcess::~CESRProcess()
{
}

void CESRProcess::DecoedeESRMsg(const lcm::ReceiveBuffer* recvBuf)
{
	m_msgESRInfo.decode(recvBuf->data, 0, recvBuf->data_size);
}

void CESRProcess::LabelESRValidity()
{
	for (size_t i = 0; i < 64; i++)
	{
		if (m_msgESRInfo.objList[i].trackStatus!=0)
		{
		}
	}
}