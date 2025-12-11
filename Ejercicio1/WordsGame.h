#pragma once
#include "Minigame.h"

namespace game
{
	class WordsGame : Minigame
	{
	public:
		WordsGame(game::Game::States& currentState);
		void Init() override;
		void Update() override;
		void Play() override;
	};
}

