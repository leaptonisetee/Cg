#pragma once

#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

struct PointLightData {
	PointLightData()
	{
		ZeroMemory(this, sizeof(PointLightData));
	}

	Vector4 position;
	Vector4 color;
	Vector3 attenuation;
	float _padding[1];
};