#pragma once

	enum class Scene
	{
		Exit,
		Game,
		MainMenu,
		ControlsMenu,
		SettingsMenu,
		Credits,
	};

	struct GameSettings
	{
		Scene scene;
		bool drawFps;
	};

	GameSettings createGameSettings();
