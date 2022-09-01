#include "Menu.h"

Buttons createButtons()
{
	Buttons buttons;

	buttons.Play = createButton();
	buttons.Exit = createButton();
	buttons.Settings = createButton();
	buttons.Controls = createButton();

	return buttons;
}

Menu createMenu()
{
	Menu menu{};

	menu.isActive = false;
	menu.title = "Menu";
	menu.titlePos = { 0, 0 };
	menu.btn = createButtons();

	return menu;
}

void mainMenu(GameSettings& gSettings, Menu& mMenu)
{
	if (!mMenu.isActive)
	{
		TakeScreenshot("PauseScreen.png");
		mMenu.bg = LoadTextureFromImage(LoadImage("PauseScreen.png"));
		mMenu.title = "Main Menu";
		mMenu.isActive = true;
		mMenu.btn.Play.text = "Play";
		mMenu.btn.Exit.text = "Exit";
		mMenu.btn.Settings.text = "Settings";
		mMenu.btn.Controls.text = "Controls";
		mMenu.btn.Credits.text = "Credits";
	}

	// Update
	positionTitle(mMenu);
	takeInput(mMenu, gSettings);
	updateButtons(mMenu);

	// draw
	draw(mMenu);
}

void draw(Menu menu)
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
	drawButton(menu.btn.Credits);

	EndDrawing();
}

void positionTitle(Menu& menu)
{
	menu.titlePos.x = (float)MeasureText(menu.title, 50);
	menu.titlePos.x = (float)GetScreenWidth() / 2 - menu.titlePos.x / 2;
	menu.titlePos.y = (float)GetScreenHeight() / 8;
}

void takeInput(Menu& menu, GameSettings& gSettings)
{
	if (isButtonPressed(menu.btn.Controls))
		gSettings.scene = Scene::ControlsMenu;

	if (isButtonPressed(menu.btn.Exit))
		gSettings.scene = Scene::Exit;

	if (isButtonPressed(menu.btn.Settings))
		gSettings.scene = Scene::SettingsMenu;

	if (isButtonPressed(menu.btn.Credits))
		gSettings.scene = Scene::Credits;

	if (isButtonPressed(menu.btn.Play))
	{
		gSettings.scene = Scene::Game;
		menu.isActive = false;
	}
}

void updateButtons(Menu& menu)
{
	const float btnSpacing = 0.0f;

	updateButton(menu.btn.Play, ((float)GetScreenHeight() / 8) * 4);
	updateButton(menu.btn.Exit, (float)GetScreenHeight() - (float)GetScreenHeight() / 8);
	updateButton(menu.btn.Settings, menu.btn.Play.rec.y + menu.btn.Play.rec.height + btnSpacing);
	updateButton(menu.btn.Controls, menu.btn.Settings.rec.y + menu.btn.Settings.rec.height + btnSpacing);
	updateButton(menu.btn.Credits, menu.btn.Controls.rec.y + menu.btn.Controls.rec.height + btnSpacing);
}

void updateButton(Button& btn, float posY)
{
	btn.rec.y = posY;
	btn.rec.x = ((float)GetScreenWidth() / 4);
}

void controlsMenu(GameSettings& gSettings, Menu& ui)
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, (float)GetScreenHeight() / 8 };
	Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, 6 * popInd.y };

	if (!ui.isActive)
	{
		ui.title = "Controls";
		ui.isActive = true;
		ui.btn.Exit.text = "Back";
	}

	// Update
	controlsMenuUpdate(ui, gSettings);

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

void controlsMenuUpdate(Menu& ui, GameSettings& gSettings)
{
	positionTitle(ui);
	updateButtons(ui);

	if (isButtonPressed(ui.btn.Exit))
	{
		ui.isActive = false;
		gSettings.scene = Scene::MainMenu;
	}
}

void settingsMenu(GameSettings& gSettings, Menu& ui)
{
	Vector2 popInd{ (float)GetScreenWidth() / 8, (float)GetScreenHeight() / 8 };
	const Rectangle backImage{ popInd.x, popInd.y,
		6 * popInd.x, 6 * popInd.y };

	if (!ui.isActive)
	{
		ui.title = "Settings";
		ui.isActive = true;
		ui.btn.Exit.text = "Back";
	}

	// Update
	if (WindowShouldClose())
		CloseWindow();
	if (isButtonPressed(ui.btn.Exit))
	{
		ui.isActive = false;
		gSettings.scene = Scene::MainMenu;
	}

	positionTitle(ui);
	updateButtons(ui);

	// Draw
	BeginDrawing();

	DrawRectangleRec(backImage, BLACK);
	drawButton(ui.btn.Exit);
	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);

	EndDrawing();
}

void creditsMenu(GameSettings& gSettings, Menu& ui)
{
	if (!ui.isActive)
	{
		ui.title = "Credits";
		ui.isActive = true;
		ui.btn.Exit.text = "Back";
	}

	// Update
	positionTitle(ui);
	updateButtons(ui);

	if (isButtonPressed(ui.btn.Exit))
		gSettings.scene = Scene::MainMenu;

	// Draw
	BeginDrawing();

	ClearBackground(BLACK);

	DrawText(ui.title, (int)ui.titlePos.x, (int)ui.titlePos.y, 50, WHITE);
	drawButton(ui.btn.Exit);
	DrawText("Mateo Fabbri", GetScreenWidth() / 2 - MeasureText("Mateo Fabbri", 50) / 2, GetScreenHeight() / 2, 50, WHITE);

	EndDrawing();
}