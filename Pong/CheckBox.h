#pragma once

#include <raylib.h>

	struct CheckBox
	{
		Vector2 pos{ 0, 0 };
		int size = 25;
		bool checked = false;
		Color out = LIGHTGRAY;
		Color empty = RAYWHITE;
		Color fill = DARKGRAY;
	};

	void draw(CheckBox check);
