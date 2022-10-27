#pragma once

#include "lab3.h"

#include <components/scene.h>
#include <delegates.h>
#include <timer.h>

#define MIN_CAMERA_ORBIT_RADIUS 1.0f
#define DEFAULT_CAMERA_ORBIT_RADIUS 5.0f
#define MAX_CAMERA_ORBIT_RADIUS 10.0f

class CameraControllerComponent : public GameComponent
{
private:
	DelegateHandle keyPressHandle;
	DelegateHandle mouseMoveHandle;
	SceneComponent* targetComponent = nullptr;

	XMFLOAT3 savedCameraPos, savedCameraLook, savedCameraUp;

	float cameraOrbitRadius = DEFAULT_CAMERA_ORBIT_RADIUS;
	Timer cameraOrbitTimer = Timer(5, true);

	void SetTargetComponent(SceneComponent* component);

	void UpdateFreeCamera(float deltaTime);
	void UpdateOrbitingCamera(float deltaTime);

public:
	CameraControllerComponent(Game& game);
	void Init();
	void Update(float deltaTime);
	void Destroy();
};