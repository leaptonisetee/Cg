#include "include/ball.h"
#include "include/paddle.h"

#include <components/collider.h>
#include <components/mesh.h>
#include <shapes.h>

#include <algorithm>
#include <random>

static const float R = 0.025;

static const float MIN_SPEED = 0.5;
static const float SPEED_STEP = 0.1;
static const float MAX_SPEED = 1.5;

BallComponent::BallComponent(Game& game) : SceneComponent(game)
{
	auto material = new Material();
	material->vertexShader = std::make_unique<VertexShader>(game, L"shaders/vertexShader.hlsl", nullptr, nullptr);
	material->pixelShader = std::make_unique<PixelShader>(game, L"shaders/pixelShader.hlsl", nullptr, nullptr);
	
	material->vertexShader->SetConstBuffer(&constBuffer, sizeof(BallComponent::ConstBuffer));

	auto mesh = Shapes::Make2DRectangle(game, material, R*2, R*2);
	AddChild(new MeshComponent(game, mesh));

	AddChild(new BoxColliderComponent(game, Vector3(R, R, 0.5f)));

	CollisionStartEvent.AddLambda([this](SceneComponent* other) {
		auto paddle = dynamic_cast<PaddleComponent*>(other);
		if (paddle != nullptr)
		{
			auto d = transform.position - paddle->transform.position;
			d.Normalize();

			direction = (Vector2(-direction.x, direction.y) + Vector2(d.x, d.y)) / 2;
			direction.Normalize();

			if (speed < MAX_SPEED) speed += SPEED_STEP;
		}
	});

	ResetPosition();
}

void BallComponent::Update(float deltaTime)
{
	Vector2 deltaPos = direction * speed * deltaTime;
	float x = transform.position.x + deltaPos.x;
	float y = transform.position.y + deltaPos.y;

	if (y > 1 || y < -1) direction.y *= -1;
	transform.SetPosition(x, std::clamp(y, -1.0f, 1.0f), 0.5f);

	constBuffer.wvpMatrix = game.Camera.GetWVPMatrix(transform);
}

void BallComponent::ResetPosition()
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_real_distribution<float> angleDistribution(0, 2 * 3.14f);

	do
	{
		float a = angleDistribution(engine);
		direction = Vector2(cos(a), sin(a));
	} while (abs(direction.y) >= 0.75);

	transform.SetPosition(0, 0, 0.5f);
	
	speed = MIN_SPEED;
}