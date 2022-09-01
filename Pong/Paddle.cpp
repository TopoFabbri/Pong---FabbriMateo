#include "Paddle.h"

	Paddle createPaddle()
	{
		Paddle pad{};

		pad.rec = { 0, 0, 12, 80 };
		pad.color1 = DARKGRAY;
		pad.color2 = RED;
		pad.initSpeed = 300.0f;
		pad.speed = pad.initSpeed;

		return pad;
	}
