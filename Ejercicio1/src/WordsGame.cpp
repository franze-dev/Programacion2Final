#include "WordsGame.h"

#include <iostream>
#include <string>
#include <thread> 
#include <chrono> 

#include "AwesomeLibrary.h"

/*
	Se van mostrando definiciones de palabras por pantalla; por cada definición, el
jugador debe escribir la palabra que piensa que corresponde a esa definición. Si
anota la correcta, suma un punto; en caso contrario, no suma puntos. Las palabras
cuyas definiciones aparecen son aleatorias. Luego de repetir esta dinámica n veces,
se le debe mostrar al jugador cuántas palabras del total logró anotar.

	Indicaciones
	● Las palabras y las definiciones deben ser consultadas por el propio programa
	en el momento mediante Internet. Es decir, se deben obtener mediante web
	requests. Al hacer estas consultas, se debe implementar multithreading para que
	nunca se quede bloqueado el main thread. Queda a libre elección las librerías y
	APIs a utilizar, aunque se recomiendan…
		○ Librería para web requests: https://github.com/microsoft/cpprestsdk
		○ API para obtener palabras aleatorias:
		https://random-word-api.herokuapp.com/home
		○ API para obtener definiciones de palabras:
		https://github.com/meetDeveloper/freeDictionaryAPI
	● Mientras se cargan las palabras, debe ejecutarse algún tipo de animación de
	carga en el main thread.
	● El juego debe permitir elegir en qué idioma se muestran las palabras y
	definiciones.
*/

namespace game
{
	using namespace utility;
	using namespace web;
	using namespace web::http;
	using namespace web::http::client;
	using namespace concurrency::streams;

	WordsGame::WordsGame(game::Game::States& currentState) : Minigame(currentState)
	{
	}

	void WordsGame::Init()
	{
	}

	void WordsGame::Update()
	{
		int currentWord = 0;

		do
		{
			std::cout << "=== WORDS GAME ===" << std::endl;

			Word word = GetWord();

			std::cout << "Guess the word for the following definition:" << std::endl;

			std::cout << "Definition: " << word.definition << std::endl;

			std::cout << "Your answer: ";

			std::string userAnswer;

			std::cin.ignore();
			std::cin >> userAnswer;

			if (userAnswer == word.word)
			{
				std::cout << "Correct!" << std::endl;
				score++;
			}
			else
				std::cout << "Wrong! The correct word was: " << word.word << std::endl;

			currentWord++;
			system("pause");

		} while (totalWords);

		clearScreen();

		std::cout << "Game Over! Your total score is: " << score << std::endl;
		system("pause");

		End();
	}

	void WordsGame::Play()
	{
		Init();
		Update();
	}

	WordsGame::Word WordsGame::GetWord()
	{
		Word myWord;

		auto randomWordTask = GetRandomWord().
			then([&](std::string entry)
				{
					myWord.word = entry;
					return GetDefinition(entry);
				});

		std::cout << "Loading word";

		while (!randomWordTask.is_done())
		{
			std::cout << ".";
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		std::cout << "\n";

		try
		{
			myWord.definition = randomWordTask.get();
			return myWord;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return myWord;
		}
	}

	pplx::task<std::string> WordsGame::GetRandomWord()
	{
		utility::string_t path = U("/word?number=1");

		http_client client(U("http://random-word-api.herokuapp.com"));

		return client.request(methods::GET, path)
			.then([](http_response response) {
			return response.extract_json();
				})
			.then([](web::json::value json) {
			auto arr = json.as_array();
			return conversions::to_utf8string(arr[0].as_string());
				});
	}

	pplx::task<std::string> WordsGame::GetDefinition(const std::string& word)
	{
		http_client client(U("https://api.dictionaryapi.dev"));

		utility::string_t path = U("/api/v2/entries/")
			+ conversions::to_string_t(lang) + U("/")
			+ conversions::to_string_t(word);

		return client.request(methods::GET, path)
			.then([](http_response response)
				{
					return response.extract_json();
				})
			.then([word](json::value jsonValue) -> std::string
				{
					try
					{
						auto meanings = jsonValue.as_array()[0][U("meanings")].as_array();
						auto allDef = meanings[0][U("definitions")].as_array();
						auto mainDef = allDef[0][U("definition")].as_string();

						return conversions::to_utf8string(mainDef);
					}
					catch (...)
					{
						return std::string("No definition found for: ") + word;
					}
				});
	}
}