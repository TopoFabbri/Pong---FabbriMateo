#include "GameSettings.h"

GameSettings createGameSettings()
{
	GameSettings gs{};

	gs.drawFps = false;
	gs.scene = Scene::MainMenu;

	return gs;
}