#include "RandomNumbersGame.h"
#include <iostream>

namespace game
{
	RandomNumbersGame::RandomNumbersGame(game::Game::States& currentState) : Minigame(currentState)
	{
	}
	void RandomNumbersGame::Init()
	{
	}

	void RandomNumbersGame::Update()
	{
		std::cout << "=== RANDOM NUMBERS GAME ===" << std::endl;
		std::cout << "This is where the Random Numbers Game would be played." << std::endl;
		system("pause");
		End();
	}

	void RandomNumbersGame::Play()
	{
		Init();
		Update();
	}
}