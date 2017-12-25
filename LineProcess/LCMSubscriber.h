#pragma once
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
	bool m_bIsInitialized;
	CLCMHandler m_lcmHandler;
};

