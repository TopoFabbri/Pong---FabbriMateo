#pragma once

#include <raylib.h>

struct Paddle
{
	Rectangle rec{ 0, 0, 12, 80 };
	Color color1{};
	Color color2{};
	float initSpeed = 300.0f;
	float speed = initSpeed;
};