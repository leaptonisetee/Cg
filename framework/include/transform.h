#pragma once

#include <d3d.h>
#include <d3d11.h>
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

struct Transform
{
	Transform* parent = nullptr;

	Vector3 position = Vector3::Zero;
	Quaternion rotation = Quaternion::Identity;
	Vector3 scale = Vector3::One;

	void SetPosition(float x, float y, float z);
	void OffsetPosition(float deltaX, float deltaY, float deltaZ);
	
	void SetRotation(float roll, float pitch, float yaw);
	void SetRotation(Quaternion rotation);

	void SetScale(float scale);
	void SetScale(float x, float y, float z);

	Vector3 GetAbsolutePosition();
	XMMATRIX GetWorldMatrix();
};