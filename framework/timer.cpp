#include "pch.h"

Timer::Timer(float period, bool autoReset) : period(period), autoReset(autoReset)
{

}

void Timer::Update(float deltaTime)
{
	if (!isRunning) return;

	elapsedTime += deltaTime;
	if (elapsedTime >= period)
	{
		if (autoReset)
		{
			while (elapsedTime >= period)
			{
				elapsedTime -= period;
			}
		}
		else
		{
			elapsedTime = 0;
			isRunning = false;
		}
	}
}

void Timer::Reset()
{
	elapsedTime = 0;
	isRunning = true;
}

bool Timer::IsRunning()
{
	return isRunning;
}

float Timer::GetProgress()
{
	return elapsedTime / period;
}