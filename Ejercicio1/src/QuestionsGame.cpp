#include "QuestionsGame.h"
#include <iostream>
#include <fstream>

#include "AwesomeLibrary.h"
#include <random>

namespace game
{
	/*
	Se van mostrando preguntas por pantalla, a la vez que una serie de opciones para
elegir. Luego, el jugador debe elegir la opción que piense que responde la pregunta.
Si elige la correcta, suma un punto; en caso contrario, no suma puntos. Luego de
repetir esto una n cantidad de veces, se debe mostrar cuántas preguntas del total
fueron respondidas correctamente
Indicaciones
● Las preguntas, sus posibles opciones y la respuesta correcta deben ser
cargadas desde archivos binarios (que se deben crear de antemano para el
juego). Se deben cargar contemplando posibles excepciones.
● Cada vez que se hace una pregunta, se tiene que mezclar de forma
pseudoaleatoria el orden de las opciones (de forma tal que la respuesta a tal o
cual pregunta no aparezca siempre en la misma posición). Para ello, se debe
utilizar un algoritmo de STL que se considere pertinente.
● El juego debe permitir elegir una temática para las preguntas antes de jugar;
tienen que haber al menos 5 temáticas y 5 preguntas por cada una. Los
archivos binarios tienen que estar almacenados en directorios diferentes
según su temática.
	*/

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
		CreateQuestionFiles();
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


	void QuestionsGame::CreateQuestionFiles()
	{
#pragma region Colors
		Question q1 = {
			"Which of the following is not a color code?",
			{
				"RGB",
				"HSL",
				"GSL"
			},
			2
		};

		Question q2 = {
			"What does K in CMYK stand for?",
			{
				"Black",
				"Key",
				"Kernel"
			},
			1
		};

		Question q3 = {
			"What is the most common color in national flags?",
			{
				"Yellow",
				"White",
				"Red"
			},
			2
		};

		Question q4 = {
			"Which of the following colors is not in the rainbow?",
			{
				"Green",
				"Pink",
				"Indigo"
			},
			1
		};

		Question q5 = {
			"Which of the following colors is not perceived by the human eye in nature?",
			{
				"Black",
				"Purple",
				"Magenta"
			},
			2
		};

		Category colorsCategory = {
			"Colors",
			"questions/Colors/",
			{ q1, q2, q3, q4, q5 }
		};

		CreateCategoryFiles(colorsCategory);

#pragma endregion

#pragma region Animals
		Question q6 = {
			"What is Australia's tallest bird?",
			{
				"Emu",
				"Ostrich",
				"Cassowary"
			},
			0
		};

		Question q7 = {
			"Black eggs called caviar come from which fish?",
			{
				"Salmon",
				"Sturgeon",
				"Pike"
			},
			1
		};

		Question q8 = {
			"Which of the following is the largest animal?",
			{
				"Blue whale",
				"African elephant",
				"Whale shark"
			},
			0
		};

		Question q9 = {
			"Where would you find the world's smallest bird, the male bee hummingbird?",
			{
				"Japan",
				"New Guinea",
				"Cuba"
			},
			2
		};

		Question q10 = {
			"Why do many frogs and toads blow up their chin skin like a balloon?",
			{
				"To help breathe out of water",
				"To frighten adversaries",
				"To make their calls louder"
			},	 
			2
		};

		Category animalsCategory = {
			"Animals",
			"questions/Animals/",
			{ q6, q7, q8, q9, q10 }
		};

		CreateCategoryFiles(animalsCategory);
#pragma endregion

#pragma region Food
		Question q11 = {
			"Pancetta is derived from the meat of what animal?",
			{
				"Chicken",
				"Lamb",
				"Pig"
			},
			2
		};

		Question q12 = {
			"What is the English translation of the name of the Italian dessert tiramisu",
			{
				"Sweet Delight",
				"Heavenly Taste",
				"Make Me Happy"
			},
			2
		};

		Question q13 = {
			"What was the last name of the inventor of potato chips?",
			{
				"Fry",
				"Crisp",
				"Crum"
			},
			2
		};

		Question q14 = {
			"In what country did the Caesar salad originate?",
			{
				"Mexico",
				"Greece",
				"Italy"
			},
			0
		};

		Question q15 = {
			"Which South American grain was referred to as the “mother of all grains” by the Incas?",
			{
				"Millet",
				"Barley",
				"Quinoa"
			},
			2
		};

		Category foodCategory = {
			"Food",
			"questions/Food/",
			{ q11, q12, q13, q14, q15 }
		};

		CreateCategoryFiles(foodCategory);
#pragma endregion

#pragma region Cars
		Question q16 = {
			"Which of these is NOT a Japanese car brand?",
			{
				"Nissan",
				"Hyundai",
				"Daihatsu"
			},
			1
		};

		Question q17 = {
			"What country is the car brand Rolls-Royce from?",
			{
				"USA",
				"UK",
				"Germany"
			},
			1
		};

		Question q18 = {
			"Which of the following athletes is/was a Formula One driver?",
			{
				"Wanderlei Silva",
				"Thierry Henry",
				"Nico Rosberg"
			},
			2
		};

		Question q19 = {
			"Which of these racetracks is the longest?",
			{
				"Indianapolis Motor Speedway",
				"Circuit of Monaco",
				"Laguna Seca"
			},
			0
		};

		Question q20 = {
			"What was the first name of Ferrari's founder?",
			{
				"Fiorano",
				"Enzo",
				"GIorgio"
			},
			1
		};

		Category carsCategory = {
			"Cars",
			"questions/Cars/",
			{ q16, q17, q18, q19, q20 }
		};

		CreateCategoryFiles(carsCategory);
#pragma endregion

#pragma region History
		Question q21 = {
			"Which ancient civilization is known for its pyramids and pharaohs?",
			{
				"Aztec",
				"Egyptian",
				"Roman"
			},
			1
		};

		Question q22 = {
			"In which river valley did the ancient Sumerian civilization emerge?",
			{
				"Nile Valley",
				"Indus Valley",
				"Tigris-Euphrates Valley"
			},
			2
		};

		Question q23 = {
			"Who was the king of the Greek gods in ancient mythology?",
			{
				"Apollo",
				"Zeus",
				"Ares"
			},
			1
		};

		Question q24 = {
			"Which ancient civilization is known for the Trojan War?",
			{
				"Roman",
				"Greek",
				"Egyptian"
			},
			1
		};

		Question q25 = {
			"Which ancient city-state was known for its strict military lifestyle and discipline?",
			{
				"Athens",
				"Sparta",
				"Corinth"
			},
			1
		};

		Category historyCategory = {
			"History",
			"questions/History/",
			{ q21, q22, q23, q24, q25 }
		};

		CreateCategoryFiles(historyCategory);
#pragma endregion

	}

	void QuestionsGame::CreateCategoryFiles(game::QuestionsGame::Category& colorsCategory)
	{
		for (int i = 0; i < QUESTIONS_COUNT; i++)
			CreateQuestionFile(colorsCategory.folderPath + "question" + std::to_string(i + 1) + ".bin", colorsCategory.questions[i]);

	}

	void QuestionsGame::CreateQuestionFile(const std::string& path, const Question& question)
	{
		std::string folderPath = path;

		std::ofstream file(path, std::ios::binary);

		if (!file)
			throw std::runtime_error("Cannot create: " + path);

		file.write(reinterpret_cast<const char*>(&question), sizeof(question));

		file.close();
	}

	void QuestionsGame::ReadQuestionFiles()
	{
		categories = new Category[CATEGORIES_COUNT]
		{
			ReadCategoryQuestionsFiles("Colors"),
			ReadCategoryQuestionsFiles("Animals"),
			ReadCategoryQuestionsFiles("Food"),
			ReadCategoryQuestionsFiles("Cars"),
			ReadCategoryQuestionsFiles("History")
		};
	}

	QuestionsGame::Question QuestionsGame::ReadQuestionFile(const std::string& questionPath)
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

	QuestionsGame::Category QuestionsGame::ReadCategoryQuestionsFiles(const std::string& categoryName)
	{
		std::string categoryPath = questionPath + categoryName + "/";

		std::string questionFilePath = categoryPath + "question";

		Category category{};

		category.name = categoryName;
		category.folderPath = categoryPath;

		for (int i = 0; i < QUESTIONS_COUNT; i++)
		{
			Question q = ReadQuestionFile(questionFilePath + std::to_string(i + 1) + ".bin");

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