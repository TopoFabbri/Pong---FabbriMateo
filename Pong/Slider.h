#pragma once

#include "Topo.h"

namespace Slider
{
	struct Slider
	{
		Vector2 pos{ 0, 0 };
		int value = 50;
		float length = 100;
		float thickness = 10;
		bool handlePressed = false;
		Circle handle{ {pos.x + length, pos.y + thickness / 2}, thickness + 10 };
		Color fillColor = DARKGRAY;
		Color barColor = LIGHTGRAY;
		Color handleColor = RAYWHITE;
	};

	void drawSlider(Slider slider);
	void updateHandle(Slider& slider);
}