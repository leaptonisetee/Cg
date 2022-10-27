#include "pch.h"

#include <iostream>

RenderDevice::RenderDevice(Window& window) : window(window), Context(nullptr), rastState(nullptr), renderView(nullptr)
{
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = window.ClientWidth;
	swapDesc.BufferDesc.Height = window.ClientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = window.hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;

	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };
	auto res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		swapChain.GetAddressOf(),
		Device.GetAddressOf(),
		nullptr,
		Context.GetAddressOf()
	);

	if (FAILED(res))
	{
		std::cout << "D3D11CreateDeviceAndSwapChain failed!" << std::endl;
		std::exit(1);
		return;
	}

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) backBuffer.GetAddressOf());
	Device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderView.GetAddressOf());

	CD3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID; // wireframe или solid

	Device->CreateRasterizerState(&rastDesc, rastState.GetAddressOf());

	viewport = {};
	viewport.Width = window.ClientWidth;
	viewport.Height = window.ClientHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1.0f;
}

void RenderDevice::SetClearColor(Vector3 color)
{
	clearColor[0] = color.x;
	clearColor[1] = color.y;
	clearColor[2] = color.z;
}

void RenderDevice::PreDraw()
{
	Context->ClearState();
	Context->RSSetState(rastState.Get());
	Context->RSSetViewports(1, &viewport);
	Context->OMSetRenderTargets(1, renderView.GetAddressOf(), nullptr);
	Context->ClearRenderTargetView(renderView.Get(), clearColor);
}

void RenderDevice::PostDraw(float totalTime)
{
	swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
}