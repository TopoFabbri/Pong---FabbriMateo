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

	padP1.rec.x = 20;
	padP1.rec.y = 200;
	padP1.color = DARKBLUE;

	padP2.rec.x = screenWidth - 20 - padP2.rec.width;
	padP2.rec.y = 200;
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

		DrawRectangleRec(field, DARKGREEN);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
		DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2, WHITE);
		DrawRectangleRec(padP1.rec, padP1.color);
		DrawRectangleRec(padP2.rec, padP2.color);
		DrawCircleV(ball.pos, ball.radius, ball.color);

		EndDrawing();
	}

	CloseWindow();

	return 0;
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

void GetInput(Paddle& padP1, Paddle& padP2)
{
	if (IsKeyDown(KEY_W))
		padP1.rec.y -= 8.0f;
	else if (IsKeyDown(KEY_S))
		padP1.rec.y += 8.0f;

	if (IsKeyDown(KEY_UP))
		padP2.rec.y -= 8.0f;
	else if (IsKeyDown(KEY_DOWN))
		padP2.rec.y += 8.0f;
}