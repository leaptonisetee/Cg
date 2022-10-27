#include "pch.h"

float utils::move_towards(float current, float target, float maxDelta)
{
	if (abs(current - target) <= maxDelta) return target;
	return current + signum(target - current) * maxDelta;
}