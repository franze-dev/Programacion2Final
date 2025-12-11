#pragma once
#include "Game.h"

namespace game
{
	class Minigame
	{
	public:
		Minigame(game::Game::States& currentState);
		virtual ~Minigame() = default;
		virtual void Play() = 0;
		virtual void End();

	protected:
		virtual void Init() = 0;
		virtual void Update() = 0;

		game::Game::States* currentState;
	};
}
