#include "GameController.h"
#include <iostream>

int main()
{
	try
	{
		GameController game;
		game.run();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}
