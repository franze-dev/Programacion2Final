#include "RandomNumbersGame.h"
#include <iostream>
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
	RandomNumbersGame::RandomNumbersGame(game::Game::States& currentState) : Minigame(currentState)
	{
	}
	void RandomNumbersGame::Init()
	{
	}
	void RandomNumbersGame::Update()
	{
		std::cout << "=== RANDOM NUMBERS GAME ===" << std::endl;

		system("pause");
		End();
	}

	void RandomNumbersGame::Play()
	{
		Init();
		Update();
	}
}