#include "include/cameraController.h"

#include <keys.h>

#include <algorithm>

#define CAMERA_SPEED 5.0f

CameraControllerComponent::CameraControllerComponent(Game& game) : GameComponent(game)
{

}

void CameraControllerComponent::Init()
{
	keyPressHandle = game.Input.KeyPressedEvent.AddLambda([this](Key key) {
		auto game = dynamic_cast<SolarSystemGame*>(&this->game);
		if (game == nullptr) return;

		if (key == Key::Key0) SetTargetComponent(nullptr);
		else if (key == Key::Key1) SetTargetComponent(game->mercury);
		else if (key == Key::Key2) SetTargetComponent(game->venus);
		else if (key == Key::Key3) SetTargetComponent(game->earth);
		else if (key == Key::Key4) SetTargetComponent(game->mars);
		else if (key == Key::Key5) SetTargetComponent(game->jupiter);
		else if (key == Key::Key6) SetTargetComponent(game->saturn);
		else if (key == Key::Key7) SetTargetComponent(game->uranus);
		else if (key == Key::Key8) SetTargetComponent(game->neptune);
		else if (key == Key::Key9) SetTargetComponent(game->pluto);
	});

	mouseMoveHandle = game.Input.MouseMoveEvent.AddLambda([this](const MouseMoveArgs& args) {
		if (this->targetComponent != nullptr) return;

		auto offset = args.Offset;
		auto& camera = this->game.Camera;
		
		float dx = XMConvertToRadians(0.125f * offset.x);
		float dy = XMConvertToRadians(0.125f * offset.y);

		camera.RotateY(dx);
		camera.Pitch(dy);
	});
}

void CameraControllerComponent::SetTargetComponent(SceneComponent* component)
{
	cameraOrbitRadius = DEFAULT_CAMERA_ORBIT_RADIUS;

	if (targetComponent != nullptr && component == nullptr)
	{
		game.Camera.SetPosition(savedCameraPos);
		game.Camera.SetLook(savedCameraLook);
		game.Camera.SetUp(savedCameraUp);
	}
	else if (targetComponent == nullptr && component != nullptr)
	{
		savedCameraPos = game.Camera.Position;
		savedCameraLook = game.Camera.Look;
		savedCameraUp = game.Camera.Up;

		cameraOrbitTimer.Reset();
	}

	targetComponent = component;
}

void CameraControllerComponent::Update(float deltaTime)
{
	if (targetComponent == nullptr) UpdateFreeCamera(deltaTime);
	else UpdateOrbitingCamera(deltaTime);
}

void CameraControllerComponent::UpdateFreeCamera(float deltaTime)
{
	if (game.Input.IsKeyDown(Key::W))
	{
		game.Camera.Walk(CAMERA_SPEED * deltaTime);
	}
	else if (game.Input.IsKeyDown(Key::S))
	{
		game.Camera.Walk(-CAMERA_SPEED * deltaTime);
	}

	if (game.Input.IsKeyDown(Key::A))
	{
		game.Camera.Strafe(-CAMERA_SPEED * deltaTime);
	}
	else if (game.Input.IsKeyDown(Key::D))
	{
		game.Camera.Strafe(CAMERA_SPEED * deltaTime);
	}
}

void CameraControllerComponent::UpdateOrbitingCamera(float deltaTime)
{
	cameraOrbitTimer.Update(deltaTime);

	if (game.Input.IsKeyDown(Key::W))
	{
		cameraOrbitRadius -= deltaTime;
	}
	else if (game.Input.IsKeyDown(Key::S))
	{
		cameraOrbitRadius += deltaTime;
	}

	cameraOrbitRadius = std::clamp(cameraOrbitRadius, MIN_CAMERA_ORBIT_RADIUS, MAX_CAMERA_ORBIT_RADIUS);

	auto planetPos = targetComponent->transform.position;

	float angle = 2.0f * 3.14f * cameraOrbitTimer.GetProgress();
	auto newPos = planetPos + cameraOrbitRadius * Vector3(cos(angle), 0, sin(angle));
	game.Camera.SetPosition(newPos);

	game.Camera.LookAt(planetPos);
}

void CameraControllerComponent::Destroy()
{
	game.Input.KeyPressedEvent.Remove(keyPressHandle);
	game.Input.MouseMoveEvent.Remove(mouseMoveHandle);
}