#include "SceneSpeedPlanner.h"
float NextSpeed(bool target_flag, float speed_limit, float distance, float self_speed, float front_obstacle_speed, float self_acc, float delta_time)
{
	float fNextSpeed = self_speed;
	float fAccDis = 0.0f;
	float fAccSpeed = 0.0f;
	float fAcc = 0.0f;
	float fSafeDis = 0.0f;
	float fFollowDis = 0.0f;
	float fDeltaSpeed = 0.0f;
	if (!target_flag || front_obstacle_speed > speed_limit)//no obs front or the front obs's speed > selfspeed 
	{
		front_obstacle_speed = speed_limit;
	}

	if (front_obstacle_speed >= self_speed)
	{
		fFollowDis = 2 * self_speed + STOP_DISTANCE;
	}
	else
	{
		fFollowDis = 2 * front_obstacle_speed + STOP_DISTANCE;
	}

	fDeltaSpeed = front_obstacle_speed - self_speed;
	if (fDeltaSpeed > 0)
	{
		fSafeDis = fFollowDis;
	}
	else
	{
		fSafeDis = fDeltaSpeed*fDeltaSpeed / 2 + fFollowDis;
	}

	if (!target_flag)
	{
		if (self_speed < speed_limit)
		{
			distance = fSafeDis + (speed_limit - self_speed) * 5;
		}
		else
		{
			distance = fSafeDis + (speed_limit - self_speed) * 2;
		}
	}
	if (distance > fSafeDis)
	{
		fAccDis = 3 * atan((distance - fSafeDis) / 17);
	}
	else
	{
		fAccDis = 0.45 * (distance - fSafeDis);
	}

	if (distance > fFollowDis)
	{
		if (fDeltaSpeed < 0)
		{
			fAccSpeed = GetMax((-fDeltaSpeed*fDeltaSpeed / 2 / (distance - fFollowDis)), (fDeltaSpeed*1.3f / 1.9f));
		}
		else
		{
			fAccSpeed = fDeltaSpeed*pow(0.72, distance - fFollowDis)*1.3f / 1.9f;
		}
	}
	else
	{
		fAccSpeed = fDeltaSpeed*1.3f / 1.9f;
	}

	if (target_flag && fAccDis>0.0f)
	{
		if (self_speed<speed_limit)
		{
			fAccDis = 3.0f*atan((speed_limit - self_speed)*5.0f / 17);
		}
		else
		{
			fAccDis = 0.45f*((speed_limit - self_speed)*2.0);
		}
	}

	if (fAcc > MAX_ACCLERATION)
	{
		fAcc = MAX_ACCLERATION;
	}
	if (fAcc < MIN_ACCLERATION)
	{
		fAcc = MIN_ACCLERATION;
	}
	fNextSpeed = self_speed + fAcc*delta_time;
	if (fNextSpeed > speed_limit && self_speed <= speed_limit)
	{
		fNextSpeed = speed_limit;
	}
	if (fNextSpeed < 0.0f)
	{
		fNextSpeed = 0.0f;
	}
	return fNextSpeed;
}