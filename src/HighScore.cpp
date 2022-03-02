#include "HighScore.h"
#include "BaseImg.h"
#include <fstream>

HighScore::HighScore()
{
	std::fstream file;
	file.open("HighScores.txt");
	if (file.is_open())
	{
		readScores(file);
		file.close();
	}
}

HighScore::~HighScore()
{
	saveScoes();
}

bool HighScore::sortAndDisplay(sf::RenderWindow& window)
{
	sortScores();
	sf::Text nameT;
	sf::Text scoreT;

	int charSize = window.getSize().x / 28;

	nameT.setCharacterSize(charSize);
	nameT.setPosition(sf::Vector2f(270.f, charSize + 170.f));
	nameT.setFont(ResourceManager::instance().getFont());

	scoreT.setCharacterSize(charSize);
	scoreT.setPosition(sf::Vector2f(window.getSize().x / 2 + 100.f, charSize + 170.f));
	scoreT.setFont(ResourceManager::instance().getFont());

	int i = 1;
	for (auto& score : m_scores)
	{
		nameT.setString(nameT.getString() + std::to_string(i++).append(". ") + score.first + "\n");
		scoreT.setString(scoreT.getString() + std::to_string(score.second) + "\n");
	}

	BaseImg img({ WIN_W / 2,WIN_H / 2 }, { WIN_W,WIN_H }, Type::HighScores);

	window.clear();
	img.draw(window);
	window.draw(nameT);
	window.draw(scoreT);
	window.display();

	while (window.isOpen())
	{
		if (auto event = sf::Event{}; window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				return false;
			case sf::Event::MouseButtonReleased:
				return true;
			}
		}
	}
	return true;
}

void HighScore::yourScore(sf::RenderWindow& window, int score)
{
	sf::Text scoreT;
	sf::Text enterName;
	sf::Text nameText;
	auto& font = ResourceManager::instance().getFont();

	scoreT.setFont(font);
	scoreT.setCharacterSize(60);
	scoreT.setString("Your final score is: " + std::to_string(score));
	float x = WIN_W / 2 - scoreT.getGlobalBounds().width / 2;
	scoreT.setFillColor(sf::Color::Red);
	scoreT.setPosition(sf::Vector2f(x, window.getSize().y / 2 - 300.f));

	enterName.setFont(font);
	enterName.setCharacterSize(60);
	enterName.setString("Whats your name?");
	enterName.setFillColor(sf::Color::Green);
	enterName.setPosition(sf::Vector2f(x, window.getSize().y / 2 - 200.f));

	nameText.setFont(font);
	nameText.setCharacterSize(60);
	nameText.setString("");
	nameText.setFillColor(sf::Color::Green);
	nameText.setPosition(sf::Vector2f(x, window.getSize().y / 2 - 100.f));

	std::string name = "";

	BaseImg img({ WIN_W / 2,WIN_H / 2 }, { WIN_W,WIN_H }, Type::Background);

	while (window.isOpen() && name.size() < 10)
	{
		window.clear();
		img.draw(window);
		window.draw(scoreT);
		window.draw(enterName);
		window.draw(nameText);
		window.display();

		if (auto event = sf::Event{}; window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode == 13)
					goto out;
				else if (event.text.unicode == 32);
				else if (event.text.unicode == 8)
				{
					if (name.size() > 0)
						name.pop_back();
					nameText.setString(name);
				}
				else if (event.text.unicode < 128)
				{
					char a = char(event.text.unicode);
					name.append(1, a);
					nameText.setString(name);
				}
			}
		}
	}

out:
	if (name.size() == 0)
		name.append("Nameless");
	
	if (m_scores.size() == AMOUNT_SCORES)
	{
		sortScores();
		m_scores.pop_back();
	}
	m_scores.push_back(std::make_pair(name, score));
}

void HighScore::readScores(std::fstream& file)
{
	std::string name;
	int score;

	int i = 0;
	while (!file.eof() && i++ < AMOUNT_SCORES)
	{
		file >> name >> score;
		if (file.eof())
			break;
		m_scores.push_back(std::make_pair(name, score));
	}
}

void HighScore::saveScoes() const
{
	std::fstream file;
	file.open("HighScores.txt", std::ios::out | std::ios::trunc);
	if (!file.is_open())
		throw std::ios_base::failure("can not open file HighScores.txt\n");

	for (auto& score : m_scores)
	{
		file << score.first << ' ';
		file << score.second;
		file << std::endl;
	}
	file.close();
}

void HighScore::sortScores()
{
	std::sort(m_scores.begin(), m_scores.end(),
		[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool
		{
			return a.first < b.first;
		});
	std::sort(m_scores.begin(), m_scores.end(),
		[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) -> bool
		{
			return a.second > b.second;
		});
}
