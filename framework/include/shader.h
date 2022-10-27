#pragma once

#include "game.h"

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

struct ShaderBase
{
protected:
	ShaderBase(Game& game, LPCWSTR filename, LPCSTR target, const D3D_SHADER_MACRO* macros, ID3DInclude* include);
	Game& game;

	void* constBufferData = nullptr;
	UINT constBufferSize = 0;

public:
	ComPtr<ID3DBlob> byteCode;
	ComPtr<ID3D11Buffer> constBuffer;

	void SetConstBuffer(void* data, UINT size);
	void UpdateConstBuffer(ComPtr<ID3D11DeviceContext> context);
};

struct VertexShader : public ShaderBase
{
public:
	VertexShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include);
	ComPtr<ID3D11VertexShader> shader;
};

struct PixelShader : public ShaderBase
{
public:
	PixelShader(Game& game, LPCWSTR filename, const D3D_SHADER_MACRO* macros, ID3DInclude* include);
	ComPtr<ID3D11PixelShader> shader;
};