#include "pch.h"

#include <d3dcompiler.h>
#include <directxmath.h>
#include <iostream>

static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (window != nullptr) 
	{
		return window->HandleMessage(umessage, wparam, lparam);
	}

	return DefWindowProc(hwnd, umessage, wparam, lparam);
}

Game::Game(LPCWSTR gameName) : Window(800, 800, gameName, WndProc), Camera(Window), Render(Window), Input(this)
{

}

Game::Game(LPCWSTR gameName, WNDPROC messageHandler) : Window(800, 800, gameName, messageHandler), Camera(Window), Render(Window), Input(this)
{

}

void Game::Init()
{

}

void Game::Run()
{
	Init();

	auto prevTime = std::chrono::steady_clock::now();
	float totalTime = 0;
	unsigned int frameCount = 0;

	MSG msg = {};
	bool exitRequested = false;
	while (!exitRequested) 
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) 
		{
			exitRequested = true;
		}

		auto curTime = std::chrono::steady_clock::now();
		float deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
		prevTime = curTime;

		Update(deltaTime);

		Render.PreDraw();
		Draw();
		Render.PostDraw(totalTime);
	}

	Destroy();
}

std::vector<GameComponent*>::iterator Game::DeleteComponent(std::vector<GameComponent*>::iterator it)
{
	GameComponent* current = *it;
	auto next = this->components.erase(it);

	current->Destroy();
	current->DestroyChildren();
	delete current;

	return next;
}

void Game::DeleteComponent(GameComponent* component)
{
	utils::remove_by_value(components, component);

	component->Destroy();
	component->DestroyChildren();
	delete component;
}

void Game::Update(float deltaTime)
{
	for (auto component : components) 
	{
		component->Update(deltaTime);
		component->UpdateChildren(deltaTime);
	}

	if (boxColliders.size() > 1)
	{
		for (auto a = std::begin(boxColliders); a != std::end(boxColliders) - 1; a++)
		{
			for (auto b = a + 1; b != std::end(boxColliders); b++)
			{
				(*a)->CheckCollision(*b);
			}
		}
	}
}

void Game::Draw()
{
	for (auto component : components) 
	{
		component->Draw();
		component->DrawChildren();
	}
}

void Game::Destroy()
{
	auto it = components.begin();
	while (it != components.end())
	{
		it = DeleteComponent(it);
	}
}