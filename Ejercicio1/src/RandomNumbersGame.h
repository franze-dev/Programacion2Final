#pragma once
#include "Minigame.h"
#include <iostream>
#include <vector>
#include <concepts>

namespace game
{
	class RandomNumbersGame : public Minigame
	{
	public:
		struct RandomNumbersConfig
		{
			int minNumber = -10;
			int maxNumber = 10;
			int numbersPerRound = 5;
			int rounds = 5;
			int displayTimeMs = 2000;
		};

		RandomNumbersGame(game::Game::States& currentState, RandomNumbersConfig config =
			{
				.minNumber = -10,
				.maxNumber = 10,
				.numbersPerRound = 5,
				.rounds = 5,
				.displayTimeMs = 2000
			});

		void Play() override;

	private:

		enum class Difficulty
		{
			EASY,
			HARD
		};

		RandomNumbersConfig config;
		Difficulty currentDifficulty;
		int score = 0;

		void Init() override;
		void Update() override;
		template<typename Num>
		int GetSign(const Num& number);
		void ShowResults();
		void RequestDifficulty();
		template<typename Num>
		void DisplayNumbers(const std::vector<Num>& numbers);
		template<typename Num>
		void PlayRounds();
	};
}

