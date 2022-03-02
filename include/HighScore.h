#pragma once
#include "ResourceManager.h"

class HighScore
{
public:
	HighScore();
	~HighScore();
	bool sortAndDisplay(sf::RenderWindow& window);
	void yourScore(sf::RenderWindow& window, int score);

private:
	void readScores(std::fstream& file);
	void saveScoes() const;
	void sortScores();

	std::vector<std::pair<std::string, int>> m_scores;
};
