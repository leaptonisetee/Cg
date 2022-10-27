#include "pch.h"

Window::Window(int width, int height, LPCWSTR applicationName, WNDPROC messageHandler) 
	: ClientWidth(width), ClientHeight(height), ApplicationName(applicationName), hWnd(nullptr)
{
	hInstance = GetModuleHandle(nullptr);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = messageHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	RECT windowRect = { 0, 0, static_cast<LONG>(ClientWidth), static_cast<LONG>(ClientHeight) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	int posX = (GetSystemMetrics(SM_CXSCREEN) - ClientWidth) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - ClientHeight) / 2;

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, ApplicationName, ApplicationName,
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_THICKFRAME,
		posX, posY,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr, nullptr, hInstance, reinterpret_cast<LPVOID>(this));

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	ShowCursor();
}

LRESULT Window::HandleMessage(UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_SIZE:
		ClientWidth = LOWORD(lparam);
		ClientHeight = LOWORD(lparam);
		return 0;

	case WM_INPUT:
		if (Input != nullptr) Input->OnInput(lparam);
		break;

	case WM_ACTIVATE:
		if (!cursorEnabled)
		{
			if (wparam & WA_ACTIVE)
			{
				ConfineCursor();
				HideCursor();
			}
			else
			{
				FreeCursor();
				ShowCursor();
			}
		}
		break;
	}

	return DefWindowProc(hWnd, umessage, wparam, lparam);
}

void Window::Close(int exitCode)
{
	PostQuitMessage(exitCode);
}

void Window::EnableCursor()
{
	cursorEnabled = true;

	ShowCursor();
	FreeCursor();
}

void Window::DisableCursor()
{
	cursorEnabled = false;

	HideCursor();
	ConfineCursor();
}

void Window::ShowCursor()
{
	while (::ShowCursor(TRUE) < 0);
}

void Window::HideCursor()
{
	while (::ShowCursor(FALSE) >= 0);
}

void Window::ConfineCursor()
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	MapWindowPoints(hWnd, nullptr, reinterpret_cast<POINT*>(&rect), 2);
	ClipCursor(&rect);
}

void Window::FreeCursor()
{
	ClipCursor(nullptr);
}

Vector2 Window::PixelToViewportPos(Vector2 pos)
{
	return pos / Vector2(ClientWidth, ClientHeight);
}

float Window::GetAspectRatio()
{
	return static_cast<float>(ClientWidth) / ClientHeight;
}