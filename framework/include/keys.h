#pragma once

enum class Key {
	LeftButton = 0,
	RightButton = 1,
	MiddleButton = 3,
	Backspace = 8,
	Tab = 9,
	Enter = 13,
	CapsLock = 20,
	Esc = 27,
	LeftShift = 16,
	RightShift = 17,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,
	Key0 = 48,
	Key1 = 49,
	Key2 = 50,
	Key3 = 51,
	Key4 = 52,
	Key5 = 53,
	Key6 = 54,
	Key7 = 55,
	Key8 = 56,
	Key9 = 57,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90
};

inline const char* ToString(Key key)
{
	switch (key)
	{
		case Key::LeftButton:	return "LeftButton";
		case Key::RightButton:	return "RightButton";
		case Key::MiddleButton:	return "MiddleButton";
		case Key::Backspace:    return "Backspace";
		case Key::Tab:			return "Tab";
		case Key::Enter:        return "Enter";
		case Key::CapsLock:     return "CapsLock";
		case Key::Esc:			return "Esc";
		case Key::LeftShift:    return "LeftShift";
		case Key::RightShift:   return "RightShift";
		case Key::Space:        return "Space";
		case Key::Left:			return "Left";
		case Key::Up:			return "Up";
		case Key::Right:        return "Right";
		case Key::Down:			return "Down";
		case Key::Key0: return "0";
		case Key::Key1: return "1";
		case Key::Key2: return "2";
		case Key::Key3: return "3";
		case Key::Key4: return "4";
		case Key::Key5: return "5";
		case Key::Key6: return "6";
		case Key::Key7: return "7";
		case Key::Key8: return "8";
		case Key::Key9: return "9";
		case Key::A:    return "A";
		case Key::B:    return "B";
		case Key::C:    return "C";
		case Key::D:    return "D";
		case Key::E:    return "E";
		case Key::F:    return "F";
		case Key::G:    return "G";
		case Key::H:    return "H";
		case Key::I:    return "I";
		case Key::J:    return "J";
		case Key::K:    return "K";
		case Key::L:    return "L";
		case Key::M:    return "M";
		case Key::N:    return "N";
		case Key::O:    return "O";
		case Key::P:    return "P";
		case Key::Q:    return "Q";
		case Key::R:    return "R";
		case Key::S:    return "S";
		case Key::T:    return "T";
		case Key::U:    return "U";
		case Key::V:    return "V";
		case Key::W:    return "W";
		case Key::X:    return "X";
		case Key::Y:    return "Y";
		case Key::Z:    return "Z";
		default:		return "Unknown key";
	}
}