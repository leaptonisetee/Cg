#pragma once

#include "colors.h"
#include "mesh.h"

using namespace DirectX::SimpleMath;

namespace Shapes
{
	Mesh* Make2DRectangle(Game& game, Material* material, float width, float height, float z = 0.5f, Vector3 color = Colors::White);

	Mesh* MakeSphere(Game& game, Material* material, float radius, int numSlices, int numStacks, Vector3 color = Colors::White);
}