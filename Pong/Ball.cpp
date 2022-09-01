#include "Ball.h"

Ball createBall()
{
	Ball ball;

	ball.speed = 15.0f;
	ball.vel = { ball.speed, ball.speed };
	ball.pos = { 400, 225 };
	ball.radius = 7.0f;
	ball.color = ORANGE;

	return ball;
}

void MoveBall(Ball& ball)
{
	Vector2 nextPos = { (ball.pos.x + ball.vel.x * GetFrameTime()),
		(ball.pos.y + ball.vel.y * GetFrameTime()) };

	ball.pos = nextPos;
}