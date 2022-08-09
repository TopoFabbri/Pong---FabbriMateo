#pragma once

#include "raylib.h"
#include <iostream>
#include <ctime>

struct Paddle
{
	Rectangle rec{ 0, 0, 15, 80 };
	Color color{};
};

struct Ball
{
	float speed = 4.0f;
	Vector2 vel{speed, speed };
	Vector2 pos{ 400, 225 };
	float radius = 10.0f;
	Color color = ORANGE;


};

void BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field);
void MoveBall(Ball& ball);
void GetInput(Paddle& padP1, Paddle& padP2);