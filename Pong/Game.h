#pragma once

#include "Ball.h"
#include "GameData.h"
#include "Paddle.h"
#include "GameSettings.h"
#include "Menu.h"
#include "Topo.h"

#include <iostream>

void loop();
void resetGame(GameData& gData);
void newScore(Paddle& p1, Paddle& p2, Ball& ball);
void Play(GameData& gData);
void PositionPads(Paddle& p1, Paddle& p2);
void ResetBall(Ball& ball);
bool CheckScores(Ball ball, int& p1Score, int& p2Score);
void BallCollisions(Ball& ball, Paddle pad1, Paddle pad2, Rectangle field);
void GetInput(Paddle& p1, Paddle& p2, Scene& scene);
void winScreen(int player, Button& back);