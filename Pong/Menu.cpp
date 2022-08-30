#include "Menu.h"

void Menu::mainMenu()
{
	TakeScreenshot("PauseScreen.png");
	Menu ui{};
	ui.bg = LoadTextureFromImage(LoadImage("PauseScreen.png"));
	ui.title = "Main Menu";
	ui.isActive = true;
	ui.btn.Play.text = "Play";
	ui.btn.Exit.text = "Exit";
	ui.btn.Settings.text = "Settings";
	ui.btn.Controls.text = "Controls";

	while (ui.isActive) 
	{
		// Update
		positionTitle(ui);
		takeInput(ui);
		updateButtons(ui);

		// draw
		draw(ui);
	}
}

void Menu::draw(Menu menu)
{
	Rectangle screen = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
	BeginDrawing();

	ClearBackground(BLACK);
	DrawTexture(menu.bg, 0, 0, WHITE);

	DrawText(menu.title, (int)menu.titlePos.x, (int)menu.titlePos.y, 50, WHITE);
	drawButton(menu.btn.Play);
	drawButton(menu.btn.Exit);
	drawButton(menu.btn.Settings);
	drawButton(menu.btn.Controls);

	EndDrawing();
}

void Menu::positionTitle(Menu& menu)
{
	menu.titlePos.x = (float)MeasureText(menu.title, 50);
	menu.titlePos.x = (float)GetScreenWidth() / 2 - menu.titlePos.x / 2;
	menu.titlePos.y = (float)GetScreenHeight() / 8;
}

void Menu::takeInput(Menu& menu)
{
	menu.isActive = !(isButtonPressed(menu.btn.Play));
	if (isButtonPressed(menu.btn.Exit) || WindowShouldClose())
		CloseWindow();

	if (isButtonPressed(menu.btn.Controls))
		controlsMenu();

	if (isButtonPressed(menu.btn.Settings))
		settingsMenu();
}

void Menu::updateButtons(Menu& menu)
{
	const float btnSpacing = 0.0f;

	updateButton(menu.btn.Play, ((float)GetScreenHeight() / 8) * 4);
	updateButton(menu.btn.Exit, (float)GetScreenHeight() - (float)GetScreenHeight() / 8);
	updateButton(menu.btn.Settings, menu.btn.Play.rec.y + menu.btn.Play.rec.height + btnSpacing);
	updateButton(menu.btn.Controls, menu.btn.Settings.rec.y + menu.btn.Settings.rec.height + btnSpacing);
}

void Menu::updateButton(Button& btn, float posY)
{
	btn.rec.y = posY;
	btn.rec.x = ((float)GetScreenWidth() / 4);
}

void Menu::controlsMenu()
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, (float)GetScreenHeight() / 8 };
	Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, 6 * popInd.y };

	Menu ui{};
	ui.title = "Controls";
	ui.isActive = true;
	ui.btn.Exit.text = "Back";

	while (ui.isActive)
	{
		// Update
		controlsMenuUpdate(ui);

		// Draw
		BeginDrawing();

		DrawRectangleRec(backImage, BLACK);
		
		DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
		drawButton(ui.btn.Exit);
		DrawText("Player 1", 300, 200, 75, DARKGRAY);
		DrawText("Player 2", GetScreenWidth() - 650, 200, 75, RED);
		DrawRectangle(350, 300, 50, 50, GRAY);
		DrawRectangle(350, 360, 50, 50, GRAY);
		DrawRectangle(GetScreenWidth() - 600, 300, 50, 50, GRAY);
		DrawRectangle(GetScreenWidth() - 600, 360, 50, 50, GRAY);
		DrawText("Move up", 410, 300, 50, GRAY);
		DrawText("Move down", 410, 360, 50, GRAY);
		DrawText("Move up", GetScreenWidth() - 540, 300, 50, GRAY);
		DrawText("Move down", GetScreenWidth() - 540, 360, 50, GRAY);
		DrawRectangle(GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 200, 50, GRAY);
		DrawText("Menu", GetScreenWidth() / 2 - 90, GetScreenHeight() / 2, 50, RAYWHITE);

		EndDrawing();
	}
}

void Menu::controlsMenuUpdate(Menu& ui)
{
	positionTitle(ui);
	updateButtons(ui);

	if (WindowShouldClose())
		CloseWindow();

	if (isButtonPressed(ui.btn.Exit))
		ui.isActive = false;
}

void Menu::settingsMenu()
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, (float)GetScreenHeight() / 8 };
	const Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, 6 * popInd.y };

	Menu ui{};
	ui.title = "Settings";
	ui.isActive = true;
	ui.btn.Exit.text = "Back";
	ui.sliders.volume.pos = { backImage.x + backImage.width / 4, backImage.y + backImage.height / 4 };

	while (ui.isActive)
	{
		// Update
		if (WindowShouldClose())
			CloseWindow();
		if (isButtonPressed(ui.btn.Exit))
			ui.isActive = false;
		Slider::updateHandle(ui.sliders.volume);
		positionTitle(ui);
		updateButtons(ui);

		// Draw
		BeginDrawing();

		DrawRectangleRec(backImage, BLACK);
		drawButton(ui.btn.Exit);
		DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
		Slider::drawSlider(ui.sliders.volume);

		EndDrawing();
	}
}