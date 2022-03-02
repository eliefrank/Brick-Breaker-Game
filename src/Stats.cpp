#include "Stats.h"

Stats::Stats()
{
	buildStats();
}

void Stats::buildStats()
{
	std::string statsTexts[]{ "Level: ", "0", " Lives:  *", "0",
							   " Balls: ", "   ", "Brick left: ", "0"," Score: ", "0" };
	auto& font = ResourceManager::instance().getFont();

	for (auto& str : statsTexts)
		m_texts.push_back(sf::Text(str, font, 30));

	m_images.push_back({ { 0,0 }, { 30,27 }, Type::Heart });
	for (int i = 0; i < NUM_OF_BALLS; i++)
		m_images.push_back({ { 0,0 }, { 30, 30 }, Type::Ball });
}

void Stats::draw(sf::RenderWindow& window) const
{
	for (auto i = 0; i < m_texts.size(); i++)
		window.draw(m_texts[i]);

	for (int i = 0; i < m_balls + 1; i++)
		m_images[i].draw(window);
}

void Stats::setLocStats()
{
	float sum = 0;

	for (auto& text : m_texts)
	{
		text.setPosition(sf::Vector2f(25 + sum, WIN_H - (STATS_H / 2)));
		sum += text.getGlobalBounds().width;
	}

	m_images[0].setPosition({ m_texts[3].getPosition().x - 43 ,WIN_H - 32 });
	for(int i = 0; i < NUM_OF_BALLS; i++)
		m_images[i+1].setPosition({ m_texts[5].getPosition().x + (31*i) ,WIN_H - 32 });
}

void Stats::setLives(int lives)
{
	m_lives = lives;
}

void Stats::setLevel(int level)
{
	m_level = level;
}

void Stats::setBrickLeft(int brick)
{
	m_brickLeft = brick;
}

void Stats::setBalls(int balls)
{
	m_balls = balls;
}

void Stats::setScore(int score)
{
	m_score = score;
}

void Stats::updateStatsTexts()
{
	m_texts[1].setString(std::to_string(m_level));
	m_texts[3].setString(std::to_string(m_lives));
	m_texts[7].setString(std::to_string(m_brickLeft));
	m_texts[9].setString(std::to_string(m_score));
	setLocStats();
}
