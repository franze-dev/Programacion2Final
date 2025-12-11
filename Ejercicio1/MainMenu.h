#pragma once
#include "Game.h"

namespace game
{
	class MainMenu
	{
	public:
		MainMenu(game::Game::States& currentState);
		void Play();

	private:
		enum class Options
		{
			MINIGAME_1,
			MINIGAME_2,
			MINIGAME_3,
			EXIT
		};

		void Update();
		void DisplayMenu();
		game::Game::States* currentState;
	};
}
