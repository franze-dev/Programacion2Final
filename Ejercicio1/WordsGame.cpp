#include "WordsGame.h"
#include <iostream>

namespace game
{
	WordsGame::WordsGame(game::Game::States& currentState) : Minigame(currentState)
	{
	}

	void WordsGame::Init()
	{
	}

	void WordsGame::Update()
	{
		std::cout << "=== WORDS GAME ===" << std::endl;
		std::cout << "This is where the words Game would be played." << std::endl;

		system("pause");

		End();
	}

	void WordsGame::Play()
	{
		Init();
		Update();
	}
}