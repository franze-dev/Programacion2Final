#include "QuestionsGame.h"
#include <iostream>
#include <fstream>

#include "AwesomeLibrary.h"
#include <random>

namespace game
{
	QuestionsGame::QuestionsGame(game::Game::States& currentState) : Minigame(currentState)
	{
		categories = nullptr;
	}

	QuestionsGame::~QuestionsGame()
	{
		delete[] categories;
	}

	void QuestionsGame::Init()
	{
		ReadQuestionFiles();
	}

	void QuestionsGame::Update()
	{
		Category currentCategory;
		Question currentQuestion;
		int userAnswerIndex = -1;

		bool validCategorySelected = false;
		int categoryIndex = 0;

		do
		{
			clearScreen();
			std::cout << "=== QUESTIONS GAME ===" << std::endl;

			int exitIndex = CATEGORIES_COUNT + 1;

			std::cout << "Select a category:" << std::endl;
			for (int i = 0; i < CATEGORIES_COUNT; i++)
			{
				Category category = categories[i];

				std::cout << i + 1 << ". " << category.name << std::endl;
			}
			std::cout << exitIndex << ". " << "Exit to Main Menu" << std::endl;

			std::cout << "Your choice (1-" << CATEGORIES_COUNT << "): ";
			std::cin >> categoryIndex;

			if (categoryIndex < 1 || categoryIndex > exitIndex)
			{
				std::cout << "Invalid category selection. Try again" << std::endl;
				validCategorySelected = false;
				system("pause");
			}
			else if (categoryIndex == exitIndex)
			{
				End();
				return;
			}
			else
			{
				currentCategory = categories[categoryIndex - 1];
				validCategorySelected = true;
			}

		} while (!validCategorySelected);

		DoCategoryQuestions(currentQuestion, currentCategory, userAnswerIndex);

		cout << "End of category questions. Returning to main menu." << endl;

		system("pause");

		End();
	}

	void QuestionsGame::DoCategoryQuestions(game::QuestionsGame::Question& currentQuestion, game::QuestionsGame::Category& currentCategory, int& userAnswerIndex)
	{
		for (int j = 0; j < QUESTIONS_COUNT; j++)
		{
			currentQuestion = currentCategory.questions[j];

			ShuffleOptions(currentQuestion);

			std::cout << "Question " << to_string(j + 1) << ": " << currentQuestion.text << std::endl;

			for (int k = 0; k < OPTIONS_COUNT; k++)
				std::cout << k + 1 << ". " << currentQuestion.options[k] << std::endl;

			userAnswerIndex = 0;

			std::cout << "Your answer (1-" << OPTIONS_COUNT << "): ";

			std::cin >> userAnswerIndex;

			if (userAnswerIndex - 1 == currentQuestion.correctOptionIndex)
				std::cout << "Correct!" << std::endl;
			else
				std::cout << "Wrong! The correct answer was: " <<
				currentQuestion.options[currentQuestion.correctOptionIndex] << std::endl;

			system("pause");
		}
	}

	void QuestionsGame::ShuffleOptions(Question& question)
	{
		int indices[OPTIONS_COUNT] = { 0, 1, 2 };

		std::random_device rd;
		static std::mt19937 gen(rd());
		std::shuffle(indices, indices + OPTIONS_COUNT, gen);

		char temp[OPTIONS_COUNT][OPTIONS_LENGTH];
		int newCorrectIndex = -1;

		for (int i = 0; i < OPTIONS_COUNT; i++)
		{
			strncpy_s(temp[i], OPTIONS_LENGTH, question.options[indices[i]], _TRUNCATE);

			if (indices[i] == question.correctOptionIndex)
				newCorrectIndex = i;
		}

		for (int i = 0; i < OPTIONS_COUNT; i++)
			strncpy_s(question.options[i], OPTIONS_LENGTH, temp[i], _TRUNCATE);

		question.correctOptionIndex = newCorrectIndex;
	}

	void QuestionsGame::ReadQuestionFiles()
	{
		categories = new Category[CATEGORIES_COUNT]
		{
			ReadCategoryQuestions("Colors"),
			ReadCategoryQuestions("Animals"),
			ReadCategoryQuestions("Food"),
			ReadCategoryQuestions("Cars"),
			ReadCategoryQuestions("History")
		};
	}

	QuestionsGame::Question QuestionsGame::ReadQuestion(const std::string& questionPath)
	{
		Question question{};

		try
		{
			std::ifstream inFile(questionPath, std::ios::binary);
			if (inFile.good())
				inFile.read(reinterpret_cast<char*>(&question), sizeof(question));
			else
				throw std::runtime_error("Cannot open: " + questionPath);

			if (inFile.is_open())
				inFile.close();
			else
				throw std::runtime_error("Cannot close: " + questionPath);

		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		return question;
	}

	QuestionsGame::Category QuestionsGame::ReadCategoryQuestions(const std::string& categoryName)
	{
		std::string categoryPath = questionPath + categoryName + "/";

		std::string questionFilePath = categoryPath + "question";

		Category category{};

		category.name = categoryName;
		category.folderPath = categoryPath;

		for (int i = 0; i < QUESTIONS_COUNT; i++)
		{
			Question q = ReadQuestion(questionFilePath + std::to_string(i + 1) + ".bin");

			category.questions[i] = q;
		}

		return category;
	}

	void QuestionsGame::Play()
	{
		Init();
		Update();
	}
}