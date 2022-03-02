#include "Level.h"

Level::Level(int levelNum)
	:m_levelNum(levelNum)
{
	readLevel();
}

const std::vector<std::pair<sf::Vector2f, char>>& Level::getBricks() const
{
	return m_bricks;
}

const sf::Vector2f& Level::getSize() const
{
	return m_size;
}

int Level::getLevelNum() const
{
	return m_levelNum;
}

void Level::readLevel()
{
	int rows, cols;
	char c;

	std::ifstream file;
	openFile(file);
	file >> rows >> cols;

	if (rows < 1 || cols < 1)
		throw std::invalid_argument("worng input value for rows or cols in level " + std::to_string(m_levelNum) + "\n");

	m_size.x = (WIN_W - WALL_W * 2) / cols;
	m_size.y = ((WIN_H - WALL_W - STATS_H)*0.6f) / rows;

	for (size_t i = 0; i < rows; i++)
	{
		if(file.get() != '\n')
			throw std::invalid_argument("the level " + std::to_string(m_levelNum) + " has more than " + std::to_string(cols) + " columns\n");

		for (size_t j = 0; j < cols; j++)
		{
			c = (char)file.get();
			if(file.eof())
				throw std::invalid_argument("the level " + std::to_string(m_levelNum) + " is incomplete\n");
			if((c < 'A' || c > 'J') && c != ' ')
				throw std::invalid_argument("in level " + std::to_string(m_levelNum) + " thre is an unaccepted value\n");
			sf::Vector2f loc(j * m_size.x + WALL_W + m_size.x /2, i * m_size.y + WALL_W + m_size.y/2);
			m_bricks.push_back(std::make_pair(loc, c));
		}
	}
	file.close();
}

void Level::openFile(std::ifstream& file) const
{
	std::string name = "level" + std::to_string(m_levelNum) + ".txt";
	file.open(name);

	if (!file.is_open())
		throw std::ios_base::failure("can not open file" + name + "\n");
}
