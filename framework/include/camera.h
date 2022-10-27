#pragma once

#include "transform.h"
#include "window.h"

#include <d3d.h>
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Camera
{
	friend class Window;

	XMFLOAT3 Position = { 0, 0, -4 };

	XMFLOAT3 Look = { 0, 0, 1 };
	XMFLOAT3 Up = { 0, 1, 0 };
	XMFLOAT3 Right = { 1, 0, 0 };

	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 pos);
	
	void SetLook(float x, float y, float z);
	void SetLook(Vector3 target);

	void SetUp(float x, float y, float z);
	void SetUp(Vector3 up);

	void LookAt(Vector3 target, Vector3 worldUp = { 0, 1, 0 });

	void Walk(float distance);
	void Strafe(float distance);
	void Pitch(float angle);
	void RotateY(float angle);

	Camera(Window& window);

	void DisableLens();
	void SetLens(float fovY, float zNear, float zFar); //TODO: update when window is resized

	XMFLOAT4X4 GetWVPMatrix(Transform& transform);

private:
	Window& window;

	float fovY;
	float zNear;
	float zFar;

	float nearWindowHeight;
	float farWindowHeight;

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
};