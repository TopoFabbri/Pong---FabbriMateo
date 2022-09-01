#include "Game.h"
#include <ctime>

void RunProgram();
void Defaults();

void main()
{
	RunProgram();
}

void RunProgram()
{
	Defaults();
	loop();
}

void Defaults()
{
	srand(time(nullptr));

	const int screenWidth = 1920;// 800 
	const int screenHeight = 1080;// 450 

	InitWindow(screenWidth, screenHeight, "PONG - FabbriMateo");
	MaximizeWindow();

	SetTargetFPS(140);
}