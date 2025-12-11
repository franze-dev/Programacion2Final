#pragma once
#include "Minigame.h"

namespace game
{
	class QuestionsGame : public Minigame
	{
	public:
		QuestionsGame(game::Game::States& currentState);
		void Init() override;
		void Update() override;
		void Play() override;
	};
}
