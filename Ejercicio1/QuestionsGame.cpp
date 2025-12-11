#include "QuestionsGame.h"
#include <iostream>

namespace game
{
	QuestionsGame::QuestionsGame(game::Game::States& currentState) : Minigame(currentState)
	{
	}
	void QuestionsGame::Init()
	{

	}

	void QuestionsGame::Update()
	{
		std::cout << "=== QUESTIONS GAME ===" << std::endl;
		std::cout << "This is where the Questions Game would be played." << std::endl;
		
		system("pause");

		End();
	}

	void QuestionsGame::Play()
	{
		Init();
		Update();
	}
}