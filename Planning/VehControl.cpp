#include "VehControl.h"

RealSteer gRealSteer;
RealSpeed gRealSpeed;
shared_mutex gSteerMutex;
shared_mutex gSpeedMutex;

CVehControl::CVehControl()
{
}


CVehControl::~CVehControl()
{
}
