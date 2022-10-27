#pragma once

#include <components/scene.h>
#include <material.h>
#include <timer.h>

#include <d3d11.h>
#include "pointLight.h"

using namespace DirectX::SimpleMath;

class CelestialBodyComponent : public SceneComponent
{
protected:
#pragma pack(push, 4)
	struct VertexConstBuffer {
		VertexConstBuffer()
		{
			ZeroMemory(this, sizeof(VertexConstBuffer));
		}

		XMFLOAT4X4 wvpMatrix;
		XMFLOAT4X4 worldMatrix;
	};

	struct PixelConstBuffer {
		PixelConstBuffer()
		{
			ZeroMemory(this, sizeof(PixelConstBuffer));
		}

		MaterialData material;		//32
		PointLightData pointLight;	//64
		Vector4 ambientLight;		//80
		Vector4 cameraPos;			//96
	};
#pragma pack(pop)

	float orbitRadius;
	Timer orbitTimer;
	Timer rotationTimer;

	VertexConstBuffer vertexConstBuffer;
	PixelConstBuffer pixelConstBuffer;

public:
	CelestialBodyComponent(Game& game, float radius, Vector3 color, float orbitRadius, float orbitPeriod);
	void Update(float deltaTime);
};