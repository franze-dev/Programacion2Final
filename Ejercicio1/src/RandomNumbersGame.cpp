#include "RandomNumbersGame.h"
#include "AwesomeLibrary.h"
#include "NumbersSequence.h"

/*
	Se van mostrando valores numéricos pseudoaleatorios por pantalla de forma
	progresiva, indicando también el signo (por ejemplo: +8, -3, etc). Cada vez que
	aparece un valor nuevo, el anterior deja de ser visible. Esta acción se repite una cierta
	cantidad de veces; al finalizar, se le pregunta al jugador que responda el resultado de
	la sumatoria de los valores que acaba de ver de forma secuencial. Si el resultado es
	correcto, se le suma un punto; en caso contrario, no sumará puntos. Luego de repetir
	esto mismo una n cantidad de veces, se le debe informar al jugador cuántos
	resultados del total logró acertar.
	Indicaciones
	● La clase que se encargue de manejar las secuencias numéricas debe ser un
	template que permita trabajar con tipos de datos numéricos únicamente. De
	esta forma, el juego debe permitir la selección de un modo fácil (con números
	enteros) y un modo difícil (con números con punto flotante, limitados a dos
	decimales).
	● Las clases involucradas deben permitir configurar programáticamente valores
	tales como…
		○ Cantidad de resultados a calcular.
		○ Cantidad de valores que aparecen en cada secuencia.
		○ Valores mínimos y máximos de los números pseudoaleatorios que se
		muestran.
		○ Cantidad de tiempo que permanece en pantalla cada valor antes de
		cambiarse por el siguiente.
	● El juego nunca debe mostrar un valor negativo que haga que la suma hasta ese
	punto de la secuencia dé como resultado otro número negativo.
*/

namespace game
{
	RandomNumbersGame::RandomNumbersGame(Game::States& currentState, const RandomNumbersConfig& config) : Minigame(currentState),
		config(config), currentDifficulty(Difficulty::EASY)
	{
	}
	void RandomNumbersGame::Init()
	{
	}
	void RandomNumbersGame::Update()
	{
		clearScreen();
		std::cout << "=== RANDOM NUMBERS GAME ===" << std::endl;

		RequestDifficulty();

		std::cout << "Random numbers will show up and you have to remember their sum." << std::endl;
		std::cout << "You will have " << config.rounds << " rounds." << std::endl;
		std::cout << "Press any key to start..." << std::endl;
		cin.ignore();
		cin.get();

		switch (currentDifficulty)
		{
		case game::RandomNumbersGame::Difficulty::EASY:
			PlayRounds<int>();
			break;
		case game::RandomNumbersGame::Difficulty::HARD:
			PlayRounds<float>();
			break;
		default:
			break;
		}

		ShowResults();

		End();
	}

	template<typename Num>
	void RandomNumbersGame::PlayRounds()
	{
		for (int i = 0; i < config.rounds; i++)
		{
			clearScreen();
			std::cout << "Current round: " << i + 1 << " of " << config.rounds << std::endl;
			miliSleep(config.displayTimeMs / 2);

			//get numbers
			NumbersSequence<Num> numbersSequence(config.numbersPerRound, static_cast<Num>(config.minNumber), static_cast<Num>(config.maxNumber));
			const std::vector<Num>& numbers = numbersSequence.GetSequence();

			//get sum
			Num sum = numbersSequence.GetSum();

			//display numbers
			DisplayNumbers(numbers);

			Num userAnswer = 0;

			clearScreen();

			std::cout << "What is the sum of the displayed numbers? " << std::endl;
			std::cin >> userAnswer;

			bool isEqual = false;

			if constexpr (std::is_floating_point_v<Num>)
			{
				userAnswer = numbersSequence.RoundToDecimals(userAnswer);
				isEqual = numbersSequence.Equals(userAnswer, sum);
			}
			else
				isEqual = (userAnswer == sum);

			if (isEqual)
			{
				std::cout << "Correct!" << std::endl;
				score++;
			}
			else
			{
				std::cout << "Wrong! The correct answer was: " << sum << std::endl;
			}

			std::cout << "Press any key to continue..." << std::endl;
			cin.ignore();
			cin.get();
		}
	}

	void RandomNumbersGame::Play()
	{
		Init();
		Update();
	}

	template<typename Num>
	int RandomNumbersGame::GetSign(const Num& number)
	{
		if (number > Num{ 0 })
			return 1;
		else if (number < Num{ 0 })
			return -1;
		else if (number == Num{ 0 })
			return 0;
	}

	template<typename Num>
	void RandomNumbersGame::DisplayNumbers(const std::vector<Num>& numbers)
	{
		for (const Num& number : numbers)
		{
			clearScreen();
			int sign = GetSign(number);

			if (sign > 0)
				std::cout << "+";

			std::cout << number << std::endl;

			miliSleep(config.displayTimeMs);
		}
	}

	void RandomNumbersGame::ShowResults()
	{
		std::cout << "You scored " << score << " out of " << config.rounds << "!" << std::endl;
		std::cout << "Press any key to return to main menu..." << std::endl;
		cin.get();
	}

	void RandomNumbersGame::RequestDifficulty()
	{
		bool validChoice = false;
		int choice = 0;

		do
		{
			clearScreen();
			std::cout << "Select difficulty:" << std::endl;
			std::cout << "1. Easy (Integers)" << std::endl;
			std::cout << "2. Hard (Floating point numbers)" << std::endl;
			std::cout << "Enter difficulty (1 or 2): ";
			std::cin >> choice;

			if (choice < 1 || choice > static_cast<int>(Difficulty::HARD) + 1)
			{
				std::cout << "Invalid choice. Please try again." << std::endl;
				std::cout << "Press any key to continue..." << std::endl;
				cin.ignore();
				cin.get();
				return;
			}
			else
				validChoice = true;
		} while (!validChoice);

		currentDifficulty = static_cast<Difficulty>(choice - 1);
	}

}