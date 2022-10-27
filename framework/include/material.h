#pragma once

#include <DirectXMath.h>
#include <memory.h>
#include <SimpleMath.h>

#include "shader.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#pragma pack(push, 4)
struct MaterialData
{
	Vector4 emissive = Vector4(0, 0, 0, 1);
	float diffuse = 1.0f;		
	float ambient = 0.1f;		
	float specular = 1.0f;		
	float specularPower = 128.0f;	
};
#pragma pack(pop)

struct Material
{
	std::unique_ptr<VertexShader> vertexShader;
	std::unique_ptr<PixelShader> pixelShader;
	MaterialData data;
};