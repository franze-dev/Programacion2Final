#pragma once
#include "Minigame.h"

namespace game
{
	class RandomNumbersGame : public Minigame
	{
	public:
		RandomNumbersGame(game::Game::States& currentState);
		void Init() override;
		void Update() override;
		void Play() override;
	};
}

