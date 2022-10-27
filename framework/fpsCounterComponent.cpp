#include "pch.h"

#include <stdio.h>
#include <Windows.h>

FpsCounterComponent::FpsCounterComponent(Game& game) : GameComponent(game)
{

}

void FpsCounterComponent::Update(float deltaTime)
{
	totalTime += deltaTime;
	frameCount++;

	if (totalTime > 1.0f)
	{
		fps = frameCount / totalTime;
		totalTime -= 1.0f;
		frameCount = 0;
	}

	WCHAR text[256];
	swprintf_s(text, TEXT("FPS: %f"), fps);
	SetWindowText(game.Window.hWnd, text);
}