#pragma once

#include "game.h"
#include "material.h"

#include <DirectXMath.h>
#include <SimpleMath.h>
#include <vector>

struct Vertex
{
	Vector3 pos = Vector3::Zero;
	Vector3 normal = Vector3(0, 0, -1);
	Vector4 color = Vector4::One;

public:
	Vertex(float x, float y, float z, Vector3 normal);
	Vertex(float x, float y, float z, Vector3 normal, Vector3 color);
	Vertex(float x, float y, float z, Vector3 normal, Vector4 color);
};

struct Mesh
{
	std::shared_ptr<Material> material;
	ComPtr<ID3D11InputLayout> layout;

	ComPtr<ID3D11Buffer> indexBuffer;
	ComPtr<ID3D11Buffer> vertexBuffer;

	std::vector<DirectX::XMFLOAT4> points;
	std::vector<int> indexes;

	UINT strides[1] = { sizeof(Vector4) * 3 };
	UINT offsets[1] = { 0 };

	Mesh(Game& game, std::vector<Vertex>& vertices, std::vector<Vector3>& tris, Material* material);
	~Mesh() = default;
};