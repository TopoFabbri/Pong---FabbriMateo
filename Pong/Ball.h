#pragma once

#include <raylib.h>

struct Ball
{
	float speed = 15.0f;
	Vector2 vel{ speed, speed };
	Vector2 pos{ 400, 225 };
	float radius = 7.0f;
	Color color = ORANGE;
};