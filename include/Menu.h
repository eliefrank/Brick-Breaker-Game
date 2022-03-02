#pragma once
#include <vector>
#include "BaseImg.h"
#include "HighScore.h"

class Menu
{
public:
	Menu(sf::RenderWindow&);
	bool run();
	void draw();
	void addScore(int score);

private:
	void buildTexts();
	void handleDisplay();
	void handleHelp();
	
	sf::RenderWindow& m_window;
	std::vector <sf::Text> m_options;
	BaseImg m_background;
	HighScore m_highScore;
};

bool clickedOn(const sf::Text& t, sf::Vector2f loc);
