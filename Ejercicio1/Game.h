#pragma once
namespace game
{
	class Game
	{
	public:
		enum class States
		{
			MAINMENU,
			MINIGAME_1,
			MINIGAME_2,
			MINIGAME_3,
			EXIT
		};

		States currentState = States::MAINMENU;
		States previousState = States::MAINMENU;
		void Play();
	};

}


