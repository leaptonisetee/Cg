#include <game.h>
#include <keys.h>
#include <utils.h>

#include "include/paddle.h"

AbstractController::AbstractController(Game& game) : GameComponent(game)
{

}

PlayerController::PlayerController(Game& game) : AbstractController(game)
{

}

void PlayerController::Update(float deltaTime)
{
	auto paddle = static_cast<PaddleComponent*>(parent);

	int speed = 0;
	if (game.Input.IsKeyDown(Key::Up)) speed = 1;
	else if (game.Input.IsKeyDown(Key::Down)) speed = -1;

	if (speed != 0)
	{
		float y = std::clamp(paddle->transform.position.y + deltaTime * speed, -0.75f, 0.75f);
		paddle->transform.position.y = y;
	}
}

AIController::AIController(Game& game, BallComponent& ball) : AbstractController(game), ball(ball)
{

}

void AIController::Update(float deltaTime)
{
	auto paddle = static_cast<PaddleComponent*>(parent);

	float currentY = paddle->transform.position.y;
	float targetY = ball.transform.position.y;
	
	float newY = std::clamp(utils::move_towards(currentY, targetY, deltaTime / 2), -0.75f, 0.75f);
	paddle->transform.position.y = newY;
}