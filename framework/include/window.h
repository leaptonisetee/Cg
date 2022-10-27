#pragma once

#include "input.h"

#include <SimpleMath.h>
#include <windows.h>
#include <WinUser.h>

class Window
{
private:
	HINSTANCE hInstance;
	WNDCLASSEX wc;
	bool cursorEnabled = true;

	void ShowCursor();
	void HideCursor();

	void ConfineCursor();
	void FreeCursor();

public:
	LPCWSTR ApplicationName;
	int ClientHeight;
	int ClientWidth;
	HWND hWnd;
	InputDevice* Input = nullptr;

	Window(int width, int height, LPCWSTR applicationName, WNDPROC messageHandler);
	LRESULT HandleMessage(UINT umessage, WPARAM wparam, LPARAM lparam);
	void Close(int exitCode);

	void EnableCursor();
	void DisableCursor();

	Vector2 PixelToViewportPos(Vector2 pos);
	float GetAspectRatio();
};