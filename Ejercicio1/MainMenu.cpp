#include "MainMenu.h"
#include "Minigame.h"
#include <iostream>

namespace game
{
	MainMenu::MainMenu(Game::States& currentState)
	{
		this->currentState = &currentState;
	}

	void MainMenu::Play()
	{
		if (*currentState != Game::States::MAINMENU)
			return;

		Update();
	}

	void MainMenu::Update()
	{
		DisplayMenu();
	}

	void MainMenu::DisplayMenu()
	{
		int option = 0;

		bool validOption = false;

		do
		{
			std::cout << "=== MAIN MENU ===" << std::endl;
			std::cout << "1. Play Questions Game" << std::endl;
			std::cout << "2. Play Words Game" << std::endl;
			std::cout << "3. Play Random Numbers Game" << std::endl;
			std::cout << "4. Exit" << std::endl;
			std::cout << "Select an option: ";
			std::cin >> option;

			if (option < 0 || option > 4)
			{
				std::cout << "Invalid option. Please try again." << std::endl;
				validOption = false;
			}
			else
			{
				Options selectedOption = static_cast<Options>(option - 1);

				switch (selectedOption)
				{
				case game::MainMenu::Options::MINIGAME_1:
					*this->currentState = Game::States::MINIGAME_1;
					validOption = true;
					break;
				case game::MainMenu::Options::MINIGAME_2:
					*this->currentState = Game::States::MINIGAME_2;
					validOption = true;
					break;
				case game::MainMenu::Options::MINIGAME_3:
					*this->currentState = Game::States::MINIGAME_3;
					validOption = true;
					break;
				case game::MainMenu::Options::EXIT:
					*this->currentState = Game::States::EXIT;
					validOption = true;
					break;
				default:
					std::cout << "Invalid option. Please try again." << std::endl;
					validOption = false;
					break;
				}
			}
		} while (!validOption);

	}
}