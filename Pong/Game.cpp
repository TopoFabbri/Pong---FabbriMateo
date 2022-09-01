#include "Game.h"

void loop()
{
	GameData gData = createGameData();

	ClearBackground(BLACK);

	while (!WindowShouldClose() && gData.gSettings.scene != Scene::Exit)
	{
		switch (gData.gSettings.scene)
		{
		case Scene::Exit: break;

		case Scene::Game:
			Play(gData);
			break;

		case Scene::MainMenu:
			mainMenu(gData.gSettings, gData.mainMenu);
			break;

		case Scene::ControlsMenu:
			controlsMenu(gData.gSettings, gData.controlsMenu);
			break;

		case Scene::SettingsMenu:
			settingsMenu(gData.gSettings, gData.settingsMenu);
			break;

		case Scene::Credits:
			creditsMenu(gData.gSettings, gData.creditsMenu);
			break;

		default:;
		}
	}

	CloseWindow();
}

void Play(GameData& gData)
{
	// Check Winning conditions
	if (gData.p1Score >= 1 || gData.p2Score >= 1)
	{
		Button back = createButton();

		winScreen(gData.p1Score >= 10 ? 1 : 2, back);

		if (isButtonPressed(back))
		{
			gData.gSettings.scene = Scene::MainMenu;
			gData.gameShouldReset = true;
		}
		else
		{
			return;
		}
	}

	if (gData.gameShouldReset)
	{
		ClearBackground(BLACK);

		// Place paddles
		newScore(gData.padP1, gData.padP2, gData.ball);
		PositionPads(gData.padP1, gData.padP2);
		gData.padP1.color1 = BLACK;
		gData.padP1.color2 = RED;
		gData.padP2.color1 = RED;
		gData.padP2.color2 = BLACK;
		gData.p1Score = 0;
		gData.p2Score = 0;
		gData.gameShouldReset = false;
	}

	// -------------------- Game loop --------------------
	// Update
	GetInput(gData.padP1, gData.padP2, gData.gSettings.scene);
	BallCollisions(gData.ball, gData.padP1, gData.padP2, gData.field);
	MoveBall(gData.ball);

	// Check score conditions
	if (CheckScores(gData.ball, gData.p1Score, gData.p2Score))
		newScore(gData.padP1, gData.padP2, gData.ball);

	// draw
	BeginDrawing();
	ClearBackground(BLACK);

	DrawRectangleRec(gData.field, DARKBLUE);
	DrawRectangleRec(gData.halfField, WHITE);
	DrawRectangleRec(gData.net, WHITE);
	DrawRectangleLinesEx(gData.net, 2, BLACK);
	DrawRectangle((int)gData.padP1.rec.x, (int)gData.padP1.rec.y, (int)gData.padP1.rec.width, (int)gData.padP1.rec.height / 2, gData.padP1.color1);
	DrawRectangle((int)gData.padP1.rec.x, (int)(gData.padP1.rec.y + gData.padP1.rec.height / 2), (int)gData.padP1.rec.width, (int)gData.padP1.rec.height / 2, gData.padP1.color2);
	DrawRectangle((int)gData.padP2.rec.x, (int)gData.padP2.rec.y, (int)gData.padP2.rec.width, (int)gData.padP2.rec.height / 2, gData.padP2.color1);
	DrawRectangle((int)gData.padP2.rec.x, (int)(gData.padP2.rec.y + gData.padP2.rec.height / 2), (int)gData.padP2.rec.width, (int)gData.padP2.rec.height / 2, gData.padP2.color2);
	DrawFPS(5, 5);
	DrawCircleV(gData.ball.pos, gData.ball.radius, gData.ball.color);
	DrawText(TextFormat("%i", gData.p1Score), GetScreenWidth() / 2 - 50, 0, 80, gData.padP1.color1);
	DrawText(TextFormat("%i", gData.p2Score), GetScreenWidth() / 2 + 10, 0, 80, gData.padP2.color1);

	EndDrawing();
}

void resetGame(GameData& gData)
{
	ResetBall(gData.ball);
	PositionPads(gData.padP1, gData.padP2);

}

void newScore(Paddle& p1, Paddle& p2, Ball& ball)
{
	ResetBall(ball);
	PositionPads(p1, p2);
}

void PositionPads(Paddle& p1, Paddle& p2)
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

void ResetBall(Ball& ball)
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

bool CheckScores(Ball ball, int& p1Score, int& p2Score)
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

void BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field)
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

		ball.pos.x = pad1.rec.x + pad1.rec.width + ball.radius;
	}
	else if (!compareVectors(rPadCollisionPos, { 0, 0 }))
	{
		BeginDrawing();
		DrawCircleV(rPadCollisionPos, 10, WHITE);
		EndDrawing();

		float deviation = rPadCollisionPos.y - (pad2.rec.y + pad2.rec.height / 2);

		ball.vel.y = deviation * deviationMultiplier;

		ball.vel.x = -ball.speed;

		ball.pos.x = pad2.rec.x - ball.radius;
	}

	const Vector2 downColl = { ball.pos.x, ball.pos.y + ball.radius };
	const Vector2 upColl = { ball.pos.x, ball.pos.y - ball.radius };

	if (!CheckCollisionPointRec(downColl, field) || !CheckCollisionPointRec(upColl, field))
		ball.vel.y *= -1;
}

void GetInput(Paddle& p1, Paddle& p2, Scene& scene)
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
		scene = Scene::MainMenu;
}

void winScreen(int player, Button& backBtn)
{
	const char* txt = TextFormat("Player %i wins!", player);
	int posX = GetScreenWidth() / 2 - MeasureText(txt, 100) / 2;
	int posY = GetScreenHeight() / 2;

	backBtn.text = "Return to menu";
	backBtn.rec.x = 5;
	backBtn.rec.y = 5;

	BeginDrawing();
	DrawText(txt, posX, posY, 100, BLACK);
	drawButton(backBtn);
	EndDrawing();
}