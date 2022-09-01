#pragma once
#include "Button.h"
#include "GameSettings.h"

struct Buttons
{
	Button Play;
	Button Exit;
	Button Settings;
	Button Controls;
	Button Credits;
};

struct Menu
{
	Texture2D bg;
	bool isActive;
	const char* title;
	Vector2 titlePos;
	Buttons btn;
};

Buttons createButtons();
Menu createMenu();
void mainMenu(GameSettings& gSettings, Menu& mMenu);
void draw(Menu menu);
void positionTitle(Menu& menu);
void takeInput(Menu& menu, GameSettings& gSettings);
void updateButtons(Menu& menu);
void updateButton(Button& btn, float posY);
void controlsMenu(GameSettings& gSettings, Menu& ui);
void controlsMenuUpdate(Menu& ui, GameSettings& gSettings);
void settingsMenu(GameSettings& gSettings, Menu& ui);
void creditsMenu(GameSettings& gSettings, Menu& ui);