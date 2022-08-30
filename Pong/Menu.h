#pragma once

#include "Button.h"
#include "Slider.h"
#include "Topo.h"

namespace Menu
{
	struct Buttons
	{
		Button Play;
		Button Exit;
		Button Settings;
		Button Controls;
	};

	struct Sliders
	{
		Slider::Slider volume;
	};

	struct Menu
	{
		Texture2D bg;
		bool isActive{};
		const char* title{};
		Vector2 titlePos{};
		Buttons btn{};
		Sliders sliders{};
	};

	void mainMenu();
	void draw(Menu menu);
	void positionTitle(Menu& menu);
	void takeInput(Menu& menu);
	void updateButtons(Menu& menu);
	void updateButton(Button& btn, float posY);
	void controlsMenu();
	void controlsMenuUpdate(Menu& ui);
	void settingsMenu();
}