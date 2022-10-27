#pragma once

#include <algorithm>
#include <vector>

namespace utils
{
	float move_towards(float current, float target, float maxDelta);

	template <typename T> 
	int signum(T val) {
		return (T(0) < val) - (val < T(0));
	}

	template <typename T>
	void remove_by_value(std::vector<T> vec, T value)
	{
		vec.erase(std::remove(vec.begin(), vec.end(), value), vec.end());
	}
}