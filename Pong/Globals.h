#pragma once

#include "raylib.h"
#include <iostream>
#include <ctime>
#include <sstream>

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

void RestartGame(Paddle& p1, Paddle& p2, Ball& ball);
void PositionPads(Paddle& p1, Paddle& p2);
void ResetBall(Ball& ball);
bool GameEnd(Ball ball);
void BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field);
void MoveBall(Ball& ball);
void GetInput(Paddle& p1, Paddle& p2);