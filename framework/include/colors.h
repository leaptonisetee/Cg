#pragma once

#include <d3d.h>
#include <d3d11.h>
#include <SimpleMath.h>

#define DEFCOLOR(name, r, g, b) static DirectX::SimpleMath::Vector3 (name) = DirectX::SimpleMath::Vector3((r), (g), (b))

namespace Colors
{
	DEFCOLOR(Black, 0.0, 0.0, 0.0);
	DEFCOLOR(Blue, 0.0, 0.0, 1.0);
	DEFCOLOR(Brown, 0.63, 0.32, 0.18f);
	DEFCOLOR(Cyan, 0.0, 1.0, 1.0);
	DEFCOLOR(DarkBrown, 0.54, 0.27, 0.07);
	DEFCOLOR(DarkGray, 0.66, 0.66, 0.66f);
	DEFCOLOR(Golden, 0.85, 0.65, 0.13);
	DEFCOLOR(Gray, 0.5, 0.5, 0.5);
	DEFCOLOR(Green, 0.0, 1.0, 0.0);
	DEFCOLOR(LightBrown, 1, 0.87, 0.67f);
	DEFCOLOR(LightGolden, 0.93, 0.87, 0.5);
	DEFCOLOR(LightGray, 0.33, 0.33, 0.33f);
	DEFCOLOR(Purple, 1.0, 0.0, 1.0);
	DEFCOLOR(Red, 1.0, 0.0, 0.0);
	DEFCOLOR(Silver, 0.75, 0.75, 0.75f);
	DEFCOLOR(Yellow, 1.0, 1.0, 0.0);
	DEFCOLOR(White, 1.0, 1.0, 1.0);
}

#undef DEFCOLOR