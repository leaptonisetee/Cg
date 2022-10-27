#include "pch.h"

#include <iostream>

InputDevice::InputDevice(Game* game) : game(game)
{
	game->Window.Input = this;

	RAWINPUTDEVICE rid[2];

	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x02;
	rid[0].dwFlags = 0;   // adds HID mouse and also ignores legacy mouse messages
	rid[0].hwndTarget = game->Window.hWnd;

	rid[1].usUsagePage = 0x01;
	rid[1].usUsage = 0x06;
	rid[1].dwFlags = 0;   // adds HID keyboard and also ignores legacy keyboard messages
	rid[1].hwndTarget = game->Window.hWnd;

	if (!RegisterRawInputDevices(rid, 2, sizeof(rid[0]))) {
		auto errorCode = GetLastError();
		std::cout << "ERROR: " << errorCode << std::endl;
	}
}

void InputDevice::AddPressedKey(Key keycode)
{
	pressedKeys.insert(keycode);
	KeyPressedEvent.Broadcast(keycode);
}

void InputDevice::RemovePressedKey(Key keycode)
{
	pressedKeys.erase(keycode);
	KeyReleasedEvent.Broadcast(keycode);
}

bool InputDevice::IsKeyDown(Key keycode)
{
	return pressedKeys.contains(keycode);
}

void InputDevice::OnInput(LPARAM lparam)
{
	UINT dwSize = 0;
	GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
	LPBYTE lpb = new BYTE[dwSize];
	if (lpb == nullptr)
		return;

	if (GetRawInputData((HRAWINPUT)lparam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
		OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));

	RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);
	HandleRawInput(raw);

	delete[] lpb;
}

void InputDevice::HandleRawInput(RAWINPUT* raw)
{
	auto type = raw->header.dwType;
	auto data = raw->data;

	switch (type) 
	{
	case RIM_TYPEKEYBOARD:
		return OnKeyDown({
			data.keyboard.MakeCode,
			data.keyboard.Flags,
			data.keyboard.VKey,
			data.keyboard.Message
		});

	case RIM_TYPEMOUSE:
		return OnMouseMove({
			data.mouse.usFlags,
			data.mouse.usButtonFlags,
			static_cast<int>(data.mouse.ulExtraInformation),
			static_cast<int>(data.mouse.ulRawButtons),
			static_cast<short>(data.mouse.usButtonData),
			data.mouse.lLastX,
			data.mouse.lLastY
		});
	}
}

void InputDevice::OnKeyDown(KeyboardArgs args)
{
	auto key = static_cast<Key>(args.VKey);
	bool breakFlag = args.Flags & 0x01;

	if (args.MakeCode == 42) key = Key::LeftShift;
	if (args.MakeCode == 54) key = Key::RightShift;

	if (breakFlag && IsKeyDown(key))
	{
		RemovePressedKey(key);
	}
	else if (!breakFlag && !IsKeyDown(key))
	{
		AddPressedKey(key);
	}
}

void InputDevice::OnMouseMove(RawMouseArgs args)
{
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::LeftButtonDown))
		AddPressedKey(Key::LeftButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::LeftButtonUp))
		RemovePressedKey(Key::LeftButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::RightButtonDown))
		AddPressedKey(Key::RightButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::RightButtonUp))
		RemovePressedKey(Key::RightButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::MiddleButtonDown))
		AddPressedKey(Key::MiddleButton);
	if (args.ButtonFlags & static_cast<int>(MouseButtonFlags::MiddleButtonUp))
		RemovePressedKey(Key::MiddleButton);

	POINT p;
	GetCursorPos(&p);
	ScreenToClient(game->Window.hWnd, &p);

	MousePosition = Vector2(p.x, p.y);
	MouseOffset = Vector2(args.X, args.Y);
	MouseWheelDelta = args.WheelDelta;

	MouseMoveEvent.Broadcast({ MousePosition, MouseOffset, MouseWheelDelta });
}