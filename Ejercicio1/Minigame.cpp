#include "Minigame.h"

namespace game
{
	Minigame::Minigame(Game::States& currentState)
	{
		this->currentState = &currentState;
	}

	void Minigame::End()
	{
		*this->currentState = Game::States::MAINMENU;
	}
}