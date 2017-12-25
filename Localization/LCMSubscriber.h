#pragma once
#include <lcm/lcm-cpp.hpp>
#include "LCMHandler.h"

class CLCMSubscriber
{
public:
	CLCMSubscriber();
	~CLCMSubscriber();
	bool IsInitialized();
	void run();

private:
	bool InitializeLCM();
	lcm::LCM* m_pLCM;
	bool m_bInitialized;
	CLCMHandler m_lcmhandler;
};

