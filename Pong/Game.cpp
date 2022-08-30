#include "Game.h"

using namespace Game;

void Game::Play()
{
	const float screenWidth = (float)GetScreenWidth();
	const float screenHeight = (float)GetScreenHeight();
	Rectangle field{ 0, 0, screenWidth, screenHeight };
	Rectangle net{ screenWidth / 2 - 5, 0, 10, screenHeight };
	Rectangle netIn{ screenWidth / 2 - 3, 0, 6, screenHeight };
	Rectangle halfField{ 0, screenHeight / 2 - 2, screenWidth, 4 };
	Paddle padP1;
	Paddle padP2;
	Ball ball;
	int p1Score{};
	int p2Score{};

	// Place paddles
	RestartGame(padP1, padP2, ball);
	PositionPads(padP1, padP2);
	padP1.color1 = BLACK;
	padP1.color2 = RED;
	padP2.color1 = RED;
	padP2.color2 = BLACK;

	ClearBackground(BLACK);
	Menu::mainMenu();

	// Main game loop
	while (!WindowShouldClose())
	{
		// Update
		GetInput(padP1, padP2);
		BallCollisions(ball, padP1, padP2, field);
		MoveBall(ball);

		// draw
		BeginDrawing();
		ClearBackground(BLACK);

		DrawRectangleRec(field, DARKBLUE);
		DrawRectangleRec(halfField, WHITE);
		DrawRectangleRec(net, WHITE);
		DrawRectangleRec(netIn, BLACK);
		DrawRectangle(padP1.rec.x, padP1.rec.y, padP1.rec.width, padP1.rec.height / 2, padP1.color1);
		DrawRectangle(padP1.rec.x, padP1.rec.y + padP1.rec.height / 2, padP1.rec.width, padP1.rec.height / 2, padP1.color2);
		DrawRectangle(padP2.rec.x, padP2.rec.y, padP2.rec.width, padP2.rec.height / 2, padP2.color1);
		DrawRectangle(padP2.rec.x, padP2.rec.y + padP2.rec.height / 2, padP2.rec.width, padP2.rec.height / 2, padP2.color2);
		DrawCircleV(ball.pos, ball.radius, ball.color);
		DrawText(TextFormat("%i", p1Score), GetScreenWidth() / 2 - 50, 0, 80, padP1.color1);
		DrawText(TextFormat("%i", p2Score), GetScreenWidth() / 2 + 10, 0, 80, padP2.color1);

		EndDrawing();

		// Check score conditions
		if (CheckScores(ball, p1Score, p2Score))
		{
			RestartGame(padP1, padP2, ball);
		}
	}

	CloseWindow();
}

void Game::RestartGame(Paddle& p1, Paddle& p2, Ball& ball)
{
	ResetBall(ball);
	PositionPads(p1, p2);
}

void Game::PositionPads(Paddle& p1, Paddle& p2)
{
	const float paddleSpace = (float)GetScreenWidth() / 40.0f;

	p1.rec.height = (float)GetScreenHeight() / 10;
	p1.rec.width = (float)GetScreenWidth() / 100;
	p2.rec.height = (float)GetScreenHeight() / 10;
	p2.rec.width = (float)GetScreenWidth() / 100;

	p1.rec.x = paddleSpace;
	p1.rec.y = (float)GetScreenHeight() / 2 - p1.rec.height / 2;

	p2.rec.x = (float)GetScreenWidth() - paddleSpace - p2.rec.width;
	p2.rec.y = (float)GetScreenHeight() / 2 - p2.rec.height / 2;
}

void Game::ResetBall(Ball& ball)
{
	ball.radius = (float)GetScreenWidth() / 200.0f;
	ball.speed = (float)GetScreenWidth() / 5.0f;
	ball.pos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };

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

	default:
		break;
	}
}

bool Game::CheckScores(Ball ball, int& p1Score, int& p2Score)
{
	if (ball.pos.x < 0)
	{
		p2Score++;
		return true;
	}
	else if (ball.pos.x > (float)GetScreenWidth())
	{
		p1Score++;
		return true;
	}

	return false;
}

void Game::BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field)
{
	const Vector2 lPadCollisionPos = getCircleRecCollisionPos(pad1.rec, { ball.pos, ball.radius });
	const Vector2 rPadCollisionPos = getCircleRecCollisionPos(pad2.rec, { ball.pos, ball.radius });

	const float deviationMultiplier = 10.0f;

	if (!compareVectors(lPadCollisionPos, { 0, 0 }))
	{
		BeginDrawing();
		DrawCircleV(lPadCollisionPos, 10, WHITE);
		EndDrawing();

		float deviation = lPadCollisionPos.y - (pad1.rec.y + pad1.rec.height / 2);

		ball.vel.y = deviation * deviationMultiplier;

		ball.vel.x = ball.speed;
	}
	else if (!compareVectors(rPadCollisionPos, { 0, 0 }))
	{
		BeginDrawing();
		DrawCircleV(rPadCollisionPos, 10, WHITE);
		EndDrawing();

		float deviation = rPadCollisionPos.y - (pad2.rec.y + pad2.rec.height / 2);

		ball.vel.y = deviation * deviationMultiplier;

		ball.vel.x = -ball.speed;
	}

	const Vector2 downColl = { ball.pos.x, ball.pos.y + ball.radius };
	const Vector2 upColl = { ball.pos.x, ball.pos.y - ball.radius };

	if (!CheckCollisionPointRec(downColl, field) || !CheckCollisionPointRec(upColl, field))
		ball.vel.y *= -1;
}

void Game::MoveBall(Ball& ball)
{
	Vector2 nextPos = { (ball.pos.x + ball.vel.x * GetFrameTime()),
		(ball.pos.y + ball.vel.y * GetFrameTime()) };

	ball.pos = nextPos;
}

void Game::GetInput(Paddle& p1, Paddle& p2)
{
	if (IsKeyDown(KEY_W) && p1.rec.y >= 0)
	{
		p1.rec.y -= (p1.speed * GetFrameTime());
		p1.speed += 10.0f;
	}
	else if (IsKeyDown(KEY_S) && p1.rec.y <= GetScreenHeight() - p1.rec.height)
	{
		p1.rec.y += (p1.speed * GetFrameTime());
		p1.speed += 10.0f;
	}
	else
	{
		p1.speed = p1.initSpeed;
	}

	if (IsKeyDown(KEY_UP) && p2.rec.y >= 0)
	{
		p2.rec.y -= (p2.speed * GetFrameTime());
		p2.speed += 10.0f;
	}
	else if (IsKeyDown(KEY_DOWN) && p2.rec.y <= GetScreenHeight() - p2.rec.height)
	{
		p2.rec.y += (p2.speed * GetFrameTime());
		p2.speed += 10.0f;
	}
	else
	{
		p2.speed = p2.initSpeed;
	}

	if (IsKeyPressed(KEY_SPACE))
		Menu::mainMenu();
}