#include "Game.h"
#include "MainMenu.h"
#include "QuestionsGame.h"
#include "WordsGame.h"
#include "RandomNumbersGame.h"
#include "AwesomeLibrary.h"

namespace game
{
	void Game::Play()
	{
		MainMenu mainMenu = MainMenu(currentState);
		QuestionsGame questionsGame = QuestionsGame(currentState);
		WordsGame wordsGame = WordsGame(currentState);
		RandomNumbersGame randomNumbersGame = RandomNumbersGame(currentState);

		do
		{
			switch (currentState)
			{
			case game::Game::States::MAINMENU:
				mainMenu.Play();
				break;
			case game::Game::States::MINIGAME_1:
				questionsGame.Play();
				break;
			case game::Game::States::MINIGAME_2:
				wordsGame.Play();
				break;
			case game::Game::States::MINIGAME_3:
				randomNumbersGame.Play();
				break;
			default:
				break;
			}

			if (previousState != currentState)
			{
				previousState = currentState;
				clearScreen();
			}

		} while (currentState != States::EXIT);
	}
}

