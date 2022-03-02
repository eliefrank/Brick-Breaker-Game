#pragma once
#include "BaseImg.h"

class Stats
{
public:
	Stats();
	void draw(sf::RenderWindow&) const;
	void setLives(int);
	void setLevel(int);
	void setScore(int);
	void setBalls(int);
	void setBrickLeft(int);
	void updateStatsTexts();

private:
	void buildStats();
	void setLocStats();

	int m_lives = INIT_LIVES;
	int m_brickLeft = 0;
	int m_level = 0;
	int m_score = 0;
	int m_balls = NUM_OF_BALLS;
	std::vector <sf::Text> m_texts;
	std::vector <BaseImg> m_images;
};
