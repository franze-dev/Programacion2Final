#pragma once
#include "Minigame.h"
#include <iostream>
#include <pplx/pplxtasks.h>  
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

namespace game
{

	class WordsGame : Minigame
	{
	public:
		WordsGame(game::Game::States& currentState);
		void Play() override;
	private:
		struct Word
		{
			std::string word;
			std::string definition;
		};

		void Init() override;
		void Update() override;

		void LanguageSelector();
		WordsGame::Word GetWord();
		pplx::task<std::string> GetRandomWord();
		pplx::task<std::string> GetDefinition(const std::string& word);

		int score = 0;
		int totalWords = 5;
		std::string lang = "en";
	};
}

