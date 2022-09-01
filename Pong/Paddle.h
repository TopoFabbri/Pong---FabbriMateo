#pragma once

#include <raylib.h>

	struct Paddle
	{
		Rectangle rec;
		Color color1;
		Color color2;
		float initSpeed;
		float speed;
	};

	Paddle createPaddle();
