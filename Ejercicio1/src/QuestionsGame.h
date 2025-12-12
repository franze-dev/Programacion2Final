#pragma once
#include "Minigame.h"
#include <string>

namespace game
{
	class QuestionsGame : public Minigame
	{
	public:
		QuestionsGame(game::Game::States& currentState);
		~QuestionsGame();
		void Play() override;

	private:

		static const int QUESTIONS_COUNT = 5;
		static const int OPTIONS_COUNT = 3;
		static const int OPTIONS_LENGTH = 128;
		static const int QUESTION_LENGTH = 256;
		static const int CATEGORIES_COUNT = 5;

		const char* questionPath = "questions/";

		struct Question
		{
			char text[QUESTION_LENGTH];
			char options[OPTIONS_COUNT][OPTIONS_LENGTH];
			int correctOptionIndex;
		};

		struct Category
		{
			std::string name;
			std::string folderPath;
			Question questions[QUESTIONS_COUNT];
		};

		Category* categories;

		void Init() override;
		void Update() override;

		void DoCategoryQuestions(game::QuestionsGame::Question& currentQuestion, game::QuestionsGame::Category& currentCategory, int& userAnswerIndex);

		void ShuffleOptions(Question& question);

		void ReadQuestionFiles();
		QuestionsGame::Question ReadQuestion(const std::string& questionPath);
		QuestionsGame::Category ReadCategoryQuestions(const std::string& categoryName);
	};
}
