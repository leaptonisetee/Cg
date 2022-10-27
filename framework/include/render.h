#pragma once

#include "window.h"

#include <d3d.h>
#include <d3d11.h>
#include <SimpleMath.h>
#include <wrl.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace Microsoft::WRL;

class RenderDevice
{
	friend class Component;

private:
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11RenderTargetView> renderView;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RasterizerState> rastState;
	//ComPtr<ID3D11DepthStencilView> depthStencilView;
	D3D11_VIEWPORT viewport;
	Window& window;

public:
	ComPtr<ID3D11Device> Device;
	ComPtr<ID3D11DeviceContext> Context;

	float clearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	void SetClearColor(Vector3 color);

	RenderDevice(Window& window);
	void PreDraw();
	void PostDraw(float totalTime);
};