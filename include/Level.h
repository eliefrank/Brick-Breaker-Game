#pragma once
#include <vector>
#include <fstream>
#include "Macros.h"

using brick_info = std::pair<sf::Vector2f, char>;

class Level
{
public:
	Level(int levelNum);
	const std::vector<brick_info>& getBricks() const;
	const sf::Vector2f& getSize() const;
	int getLevelNum() const;

private:
	void readLevel();
	void openFile(std::ifstream& file) const;

	std::vector<brick_info> m_bricks;
	sf::Vector2f m_size;
	int m_levelNum;
};
