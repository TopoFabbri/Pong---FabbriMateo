#pragma once

#include "Topo.h"
#include "Paddle.h"
#include "Ball.h"
#include "Menu.h"

namespace Game
{
	void Play();
	void RestartGame(Paddle& p1, Paddle& p2, Ball& ball);
	void PositionPads(Paddle& p1, Paddle& p2);
	void ResetBall(Ball& ball);
	bool CheckScores(Ball ball, int& p1Score, int& p2Score);
	void BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field);
	void MoveBall(Ball& ball);
	void GetInput(Paddle& p1, Paddle& p2);
}