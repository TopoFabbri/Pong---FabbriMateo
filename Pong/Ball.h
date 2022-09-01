#pragma once

#include <raylib.h>

struct Ball
{
	float speed;
	Vector2 vel;
	Vector2 pos;
	float radius;
	Color color;
};

Ball createBall();
void MoveBall(Ball& ball);