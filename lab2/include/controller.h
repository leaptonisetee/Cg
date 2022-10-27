#pragma once

#include <game.h>
#include <component.h>

#include "ball.h"

class PaddleComponent;

class AbstractController : public GameComponent
{
protected:
	AbstractController(Game& game);

public:
	virtual void Update(float deltaTime) = 0;
};

class PlayerController : public AbstractController
{
public:
	PlayerController(Game& game);
	virtual void Update(float deltaTime);
};



class AIController : public AbstractController
{
private:
	BallComponent& ball;

public:
	AIController(Game& game, BallComponent& ball);
	virtual void Update(float deltaTime);
};