#pragma once
#include <raylib.h>

#include "Ball.h"
#include "GameSettings.h"
#include "Menu.h"
#include "Paddle.h"

struct GameData
{
	Menu mainMenu;
	Menu controlsMenu;
	Menu settingsMenu;
	Menu creditsMenu;
	GameSettings gSettings;
	Rectangle field;
	Rectangle net;
	Rectangle halfField;
	Paddle padP1;
	Paddle padP2;
	Ball ball;
	int p1Score;
	int p2Score;
	bool gameShouldReset;
};

GameData createGameData();