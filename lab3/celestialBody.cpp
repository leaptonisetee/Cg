#include "include/celestialBody.h"

#include <components/mesh.h>
#include <colors.h>
#include <iostream>
#include <shapes.h>
#include <transform.h>

CelestialBodyComponent::CelestialBodyComponent(Game& game, float radius, Vector3 color, float orbitRadius, float orbitPeriod)
	: SceneComponent(game), orbitRadius(orbitRadius), orbitTimer(orbitPeriod, true), rotationTimer(10, true)
{
	auto material = new Material{
		.vertexShader = std::make_unique<VertexShader>(game, L"shaders/vertexShader.hlsl", nullptr, nullptr),
		.pixelShader = std::make_unique<PixelShader>(game, L"shaders/pixelShader.hlsl", nullptr, nullptr),
		.data = MaterialData()
	};

	if (orbitRadius == 0)
	{
		material->data.emissive = Vector4::One;
	}

	material->vertexShader->SetConstBuffer(&vertexConstBuffer, sizeof(CelestialBodyComponent::VertexConstBuffer));
	material->pixelShader->SetConstBuffer(&pixelConstBuffer, sizeof(CelestialBodyComponent::PixelConstBuffer));

	pixelConstBuffer.material = material->data;

	pixelConstBuffer.pointLight = PointLightData();
	pixelConstBuffer.pointLight.position = Vector4::Zero;
	pixelConstBuffer.pointLight.color = Vector4::One;
	pixelConstBuffer.pointLight.attenuation = Vector3(1, 0.08f, 0) / 2;

	pixelConstBuffer.ambientLight = Vector4::One;

	auto mesh = Shapes::MakeSphere(game, material, radius, 10, 10, color);
	AddChild(new MeshComponent(game, mesh));

	transform.SetPosition(orbitRadius, 0, 0);
}

void CelestialBodyComponent::Update(float deltaTime)
{
	if (orbitRadius > 0)
	{
		orbitTimer.Update(deltaTime);
		rotationTimer.Update(deltaTime);

		float angle = 2.0f * 3.14f * orbitTimer.GetProgress();
		transform.SetPosition(orbitRadius * cos(angle), orbitRadius * sin(angle), 0);

		float rotationAngle = 2.0f * 3.14f * rotationTimer.GetProgress();
		transform.SetRotation(0, rotationAngle, 0);
	}

	vertexConstBuffer.wvpMatrix = game.Camera.GetWVPMatrix(transform);
	
	auto worldMatrix = transform.GetWorldMatrix();
	auto transposed = XMMatrixTranspose(worldMatrix);
	XMStoreFloat4x4(&vertexConstBuffer.worldMatrix, transposed);

	auto pos = game.Camera.Position;
	pixelConstBuffer.cameraPos = Vector4(pos.x, pos.y, pos.z, 0);
}