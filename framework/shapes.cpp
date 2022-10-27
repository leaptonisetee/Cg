#include "pch.h"

Mesh* Shapes::Make2DRectangle(Game& game, Material* material, float width, float height, float z, Vector3 color)
{
	float halfWidth = width / 2;
	float halfHeight = height / 2;

	std::vector<Vertex> vertices = {
		Vertex(halfWidth, halfHeight,   z, -Vector3::Forward, color),
		Vertex(halfWidth, -halfHeight,  z, -Vector3::Forward, color),
		Vertex(-halfWidth, -halfHeight, z, -Vector3::Forward, color),
		Vertex(-halfWidth, halfHeight,  z, -Vector3::Forward, color)
	};

	std::vector<Vector3> tris = {
		{0, 1, 2}, {2, 3, 0}
	};

	return new Mesh(game, vertices, tris, material);
}

Mesh* Shapes::MakeSphere(Game& game, Material* material, float radius, int numSlices, int numStacks, Vector3 color)
{
	std::vector<Vertex> vertices;
	std::vector<Vector3> tris;

	Vertex northPole(0, +radius, 0, Vector3(0, 1, 0), color);
	Vertex southPole(0, -radius, 0, Vector3(0, -1, 0), color);

	vertices.push_back(northPole);

	float phiStep = XM_PI / numStacks;
	float thetaStep = 2.0f * XM_PI / numSlices;

	for (int i = 1; i <= numStacks - 1; i++)
	{
		float phi = i * phiStep;

		for (int j = 0; j <= numSlices; ++j)
		{
			float theta = j * thetaStep;

			float x = radius * sinf(phi) * cosf(theta);
			float y = radius * cosf(phi);
			float z = radius * sinf(phi) * sinf(theta);

			Vector3 normal(x, y, z);
			normal.Normalize();

			Vertex v(x, y, z, normal, color);
			vertices.push_back(v);
		}
	}

	vertices.push_back(southPole);

	for (int i = 1; i <= numSlices; i++)
	{
		tris.push_back(Vector3(0, i + 1, i));
	}

	int baseIndex = 1;
	int ringVertexCount = numSlices + 1;
	for (int i = 0; i < numStacks - 2; ++i)
	{
		for (int j = 0; j < numSlices; ++j)
		{
			tris.push_back(Vector3(
				baseIndex + i * ringVertexCount + j,
				baseIndex + i * ringVertexCount + j + 1,
				baseIndex + (i + 1) * ringVertexCount + j
			));

			tris.push_back(Vector3(
				baseIndex + (i + 1) * ringVertexCount + j,
				baseIndex + i * ringVertexCount + j + 1,
				baseIndex + (i + 1) * ringVertexCount + j + 1
			));
		}
	}

	int southPoleIndex = vertices.size() - 1;

	baseIndex = southPoleIndex - ringVertexCount;
	for (int i = 0; i < numSlices; ++i)
	{
		tris.push_back(Vector3(southPoleIndex, baseIndex + i, baseIndex + i + 1));
	}

	return new Mesh(game, vertices, tris, material);
}