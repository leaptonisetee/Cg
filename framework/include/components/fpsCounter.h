#pragma once

#include "../component.h"

class FpsCounterComponent : public GameComponent
{
private:
	float totalTime = 0;
	int frameCount = 0;
	float fps = 0;

public:
	FpsCounterComponent(Game& game);
	void Update(float deltaTime);
};