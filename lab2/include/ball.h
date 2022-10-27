#pragma once

#include <components/scene.h>

#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class BallComponent : public SceneComponent
{
private:
	struct ConstBuffer {
		XMFLOAT4X4 wvpMatrix;
	};

	Vector2 direction;
	float speed;

	ConstBuffer constBuffer;

public:
	BallComponent(Game& game);
	~BallComponent() = default;

	virtual void Update(float deltaTime);

	void ResetPosition();
};