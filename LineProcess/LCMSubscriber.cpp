#include "LCMSubscriber.h"


CLCMSubscriber::CLCMSubscriber():
m_pLCM(new lcm::LCM("udpm://239.255.76.67:7667?ttl=0")),
m_bIsInitialized(false)
{
	m_bIsInitialized = InitializeLCM();
}


CLCMSubscriber::~CLCMSubscriber()
{
	delete m_pLCM;
}

bool CLCMSubscriber::InitializeLCM()
{
	if (!m_pLCM->good())
	{
		return false;
	}
	m_pLCM->subscribe("VehiclePosture", &CLCMHandler::CallbackVehiclePosture, &m_lcmHandler);
	return true;
}

bool CLCMSubscriber::IsInitialized()
{
	return m_bIsInitialized;
}

void CLCMSubscriber::run()
{
	while (0 == m_pLCM->handle())
	{

	}
}