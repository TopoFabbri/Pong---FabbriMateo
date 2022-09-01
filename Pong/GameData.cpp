#include "GameData.h"

GameData createGameData()
{
	GameData gData;

	gData.mainMenu = createMenu();
	gData.controlsMenu = createMenu();
	gData.settingsMenu = createMenu();
	gData.creditsMenu = createMenu();
	gData.gSettings = createGameSettings();
	gData.field = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
	gData.net = { (float)GetScreenWidth() / 2 - 5, 0, 10, (float)GetScreenHeight() };
	gData.halfField = { 0, (float)GetScreenHeight() / 2 - 2, (float)GetScreenWidth(), 4 };
	gData.padP1 = createPaddle();
	gData.padP2 = createPaddle();
	gData.ball = createBall();
	gData.p1Score = 0;
	gData.p2Score = 0;
	gData.gameShouldReset = true;

	return gData;
}