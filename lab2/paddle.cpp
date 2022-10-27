#include "include/paddle.h"

#include <shapes.h>

#include <algorithm>
#include <iostream>

static const float width = 0.05f;
static const float height = 0.5f;

PaddleComponent::PaddleComponent(Game& game, BallComponent& ball) : SceneComponent(game), ball(ball)
{
	auto material = new Material {
		.vertexShader = std::make_unique<VertexShader>(game, L"shaders/vertexShader.hlsl", nullptr, nullptr),
		.pixelShader = std::make_unique<PixelShader>(game, L"shaders/pixelShader.hlsl", nullptr, nullptr)
	};

	material->vertexShader->SetConstBuffer(&constBuffer, sizeof(PaddleComponent::ConstBuffer));

	auto mesh = Shapes::Make2DRectangle(game, material, width, height);
	AddChild(new MeshComponent(game, mesh));

	AddChild(new BoxColliderComponent(game, Vector3(width / 2, height / 2, 0.5f)));
}

void PaddleComponent::Update(float deltaTime)
{
	constBuffer.wvpMatrix = game.Camera.GetWVPMatrix(transform);
}

void PaddleComponent::SetSpeed(float speed)
{
	this->speed = speed;
}