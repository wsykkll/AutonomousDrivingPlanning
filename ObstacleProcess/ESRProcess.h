#pragma once
#include "global.hpp"
#include "METRadarObject_Lcm.hpp"

class CESRProcess
{
public:
	CESRProcess();
	~CESRProcess();

	void DecoedeESRMsg(const lcm::ReceiveBuffer* recvBuf);
private:
	METRadarObject_Lcm m_msgESRInfo;
	void LabelESRValidity();
};

