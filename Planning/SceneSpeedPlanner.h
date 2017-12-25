#pragma once
#include "Notation.h"

#define STOP_DISTANCE 10
#define STOP_DISTANCE_SPEED_0 50
const float MAX_ACCLERATION = 4.5f;
const float MIN_ACCLERATION = -9.0f;

float NextSpeed(bool target_flag, float speed_limit, float distance, float self_speed, float front_obstacle_speed,float self_acc, float delta_time);