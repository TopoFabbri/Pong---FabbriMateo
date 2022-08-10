#include "Globals.h"

int main()
{
	srand(time(nullptr));
	const int screenWidth = 800;
	const int screenHeight = 450;
	Rectangle field{ 0, 0, screenWidth, screenHeight };
	Paddle padP1;
	Paddle padP2;
	Ball ball;

	InitWindow(screenWidth, screenHeight, "PONG - FabbriMateo");
	MaximizeWindow();

	SetTargetFPS(60);

	// Place paddles
	PositionPads(padP1, padP2);
	padP1.color = DARKGRAY;
	padP2.color = RED;

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update
		GetInput(padP1, padP2);
		BallCollisions(ball, padP1, padP2, field);
		MoveBall(ball);

		// Draw
		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangleRec(field, DARKBLUE);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2, WHITE);
		DrawRectangleRec(padP1.rec, padP1.color);
		DrawRectangleRec(padP2.rec, padP2.color);
		DrawCircleV(ball.pos, ball.radius, ball.color);
		DrawFPS(10, 10);

		EndDrawing();

		// Check win/lose conditions
		if (GameEnd(ball))
		{
			RestartGame(padP1, padP2, ball);
			WaitTime(1000);
		}
	}

	CloseWindow();

	return 0;
}

void RestartGame(Paddle& p1, Paddle& p2, Ball& ball)
{
	ResetBall(ball);
	PositionPads(p1, p2);
}

void PositionPads(Paddle& p1, Paddle& p2)
{
	p1.rec.x = 20;
	p1.rec.y = 200;

	p2.rec.x = GetScreenWidth() - 20 - p2.rec.width;
	p2.rec.y = 200;
}

void ResetBall(Ball& ball)
{
	ball.pos = { 400, 225 };

	switch (rand() % 4)
	{
	case 0:
		ball.vel.x = -ball.speed;
		ball.vel.y = -ball.speed;
		break;

	case 1:
		ball.vel.x = ball.speed;
		ball.vel.y = -ball.speed;
		break;

	case 2:
		ball.vel.x = -ball.speed;
		ball.vel.y = ball.speed;
		break;

	case 3:
		ball.vel.x = ball.speed;
		ball.vel.y = ball.speed;
		break;
}
}

bool GameEnd(Ball ball)
{
	if (ball.pos.x < 0)
	{
		BeginDrawing();
		DrawText("RED WINS!", 100, 50, 100, BLACK);
		EndDrawing();

		return true;
	}
	else if (ball.pos.x > GetScreenWidth())
	{
		BeginDrawing();
		DrawText("BLACK WINS!", 100, 50, 100, BLACK);
		EndDrawing();

		return true;
	}

	return false;
}

void BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field)
{
	if (CheckCollisionCircleRec(ball.pos, ball.radius, pad1.rec))
		ball.vel.x = ball.speed;
	else if (CheckCollisionCircleRec(ball.pos, ball.radius, pad2.rec))
		ball.vel.x = -ball.speed;

	const Vector2 downColl = { ball.pos.x, ball.pos.y + ball.radius };
	const Vector2 upColl = { ball.pos.x, ball.pos.y - ball.radius };

	if (!CheckCollisionPointRec(downColl, field) || !CheckCollisionPointRec(upColl, field))
		ball.vel.y *= -1;
}

void MoveBall(Ball& ball)
{
	ball.pos.x += ball.vel.x;
	ball.pos.y += ball.vel.y;
}

void GetInput(Paddle& p1, Paddle& p2)
{
	if (IsKeyDown(KEY_W) && p1.rec.y >= 8)
		p1.rec.y -= 8.0f;
	else if (IsKeyDown(KEY_S) && p1.rec.y <= GetScreenHeight() - p1.rec.height)
		p1.rec.y += 8.0f;

	if (IsKeyDown(KEY_UP) && p2.rec.y >= 8)
		p2.rec.y -= 8.0f;
	else if (IsKeyDown(KEY_DOWN) && p2.rec.y <= GetScreenHeight() - p2.rec.height)
		p2.rec.y += 8.0f;
}