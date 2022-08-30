#pragma once

#include "Topo.h"

struct Button
{
	Rectangle rec{0, 0, 200, 50};
	Color normal = WHITE;
	Color hovered = GRAY;
	Color txtColor = BLACK;
	float size = 30;
	float txtSpacing = 1;
	const char* text = "Button";
	float indent = 10;
	Font font = GetFontDefault();
};

void drawButton(Button& btn);
bool isButtonPressed(Button btn);