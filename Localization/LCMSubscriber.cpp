#include "LCMSubscriber.h"


CLCMSubscriber::CLCMSubscriber():
m_pLCM(new lcm::LCM("udpm://239.255.76.67:7667?ttl=0")),
m_bInitialized(false)
{
	m_bInitialized = InitializeLCM();
}


CLCMSubscriber::~CLCMSubscriber()
{
}

bool CLCMSubscriber::InitializeLCM()
{
	if (!m_pLCM->good())
	{
		return false;
	}
	//subscribe the GPS,Detected Lanes and Detected Traffic Signs
	return true;
}

bool CLCMSubscriber::IsInitialized()
{
	return m_bInitialized;
}

void CLCMSubscriber::run()
{
	while (0 == m_pLCM->handle())
	{

	}
}