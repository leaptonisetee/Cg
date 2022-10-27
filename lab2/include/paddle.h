#pragma once

#include <components/mesh.h>
#include <components/scene.h>

#include "ball.h"
#include "controller.h"

class PaddleComponent : public SceneComponent
{
private:
	struct ConstBuffer {
		XMFLOAT4X4 wvpMatrix;
	};

	float speed = 0;
	BallComponent& ball;

	ConstBuffer constBuffer;

public:
	PaddleComponent(Game& game, BallComponent& ball);
	~PaddleComponent() = default;

	virtual void Update(float deltaTime);
	void SetSpeed(float speed);
};