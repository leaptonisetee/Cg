#pragma once

struct Timer
{
private:
	float period;
	float elapsedTime = 0;
	bool isRunning = true;
	bool autoReset;

public:
	Timer(float period, bool autoReset = false);
	void Update(float deltaTime);
	void Reset();

	bool IsRunning();
	float GetProgress();
};