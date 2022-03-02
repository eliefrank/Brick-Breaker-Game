#pragma once
#include <vector>
#include "Menu.h"
#include "LevelController.h"

class GameController
{
public:
	GameController();
	void run();

private:
	void readLevels();
	void levelWon();
	void TextsLevelWon(std::vector <sf::Text>& texts);
	void TextsGameOver(std::vector <sf::Text>& options);
	void gameLost();
	void completeAllLevels();
	void gameOver(Type t);

	sf::RenderWindow m_window;
	std::shared_ptr<b2World> m_world;
	Menu m_menu;
	std::vector<Level> m_levels;
	std::shared_ptr<Player> m_player;
	int m_currLevel = 1;
};
