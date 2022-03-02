#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
	:m_window(window), m_background({ WIN_W/2,WIN_H/2 }, { WIN_W,WIN_H }, Type::Menu)
{
	buildTexts();
}


bool Menu::run()
{
	ResourceManager::instance().setSong(Sound::Menu);

	while (m_window.isOpen())
	{
		handleDisplay();
		if (auto event = sf::Event{}; m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				return false;
			case sf::Event::MouseButtonReleased:
			{
				auto loc = m_window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				if(clickedOn(m_options[PLAY], loc))
					return true;
				if(clickedOn(m_options[EXIT], loc))
					return false;
				if (clickedOn(m_options[HELP], loc))
					handleHelp();
				if (clickedOn(m_options[HIGH_SCORE], loc))
					if (!m_highScore.sortAndDisplay(m_window))
						return false;
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case(sf::Keyboard::Escape):
					return false;
				case(sf::Keyboard::Enter):
					return true;
				}
				break;
			}
			}
		}
	}
	return false;
}

void Menu::buildTexts()
{
	auto& font = ResourceManager::instance().getFont();
	m_options.push_back(sf::Text("PLAY", font, 100));
	m_options.push_back(sf::Text("EXIT", font, 100));
	m_options.push_back(sf::Text("Help", font, 80));
	m_options.push_back(sf::Text("HighScores", font, 80));

	m_options[PLAY].setPosition({ WIN_W / 2 - (m_options[PLAY].getGlobalBounds().width) / 2, WIN_H / 2 - 180 });
	m_options[EXIT].setPosition({ WIN_W / 2 - (m_options[EXIT].getGlobalBounds().width) / 2, WIN_H / 2 - 50 });
	m_options[HELP].setPosition({ WIN_W / 2 - (m_options[HELP].getGlobalBounds().width) / 2, WIN_H / 2 + 80 });
	m_options[HIGH_SCORE].setPosition({ WIN_W / 2 - (m_options[HIGH_SCORE].getGlobalBounds().width) / 2, WIN_H / 2 + 190 });
}

void Menu::draw()
{
	m_background.draw(m_window);
	for(auto& option : m_options)
		m_window.draw(option);
}

void Menu::addScore(int score)
{
	m_highScore.yourScore(m_window, score);
}

bool clickedOn(const sf::Text& t, sf::Vector2f loc)
{
	return t.getGlobalBounds().contains(loc);
}

void Menu::handleDisplay()
{
	m_window.clear();
	draw();
	m_window.display();
}

void Menu::handleHelp()
{
	BaseImg background({ WIN_W / 2,WIN_H / 2 }, { WIN_W,WIN_H }, Type::Background);

	std::string texts[]{ "You need to break all the bricks on the board!\n",
						 "Note: Some bricks do not break\n",
						 "Be careful that the ball does not fall\n",
						 "Try to grab good bonuses\n\n",
						 "Keyboard actions:\n",
						 "^ - Start moving the ball\n",
						 "< > - Move the Paddle to the sides\n",
						 "Space - Stop the game\n\n",
						 "Try to complete all levels...\n",
						 "Be one of the top five...\n",
						 "Enjoy and good luck!!!\n\n",
						 "Press to return" };

	auto& font = ResourceManager::instance().getFont();
	sf::Text text("", font, 40);
	text.setPosition({ 10,10 });

	for (auto& s : texts)
		text.setString(text.getString() + s);

	while (m_window.isOpen())
	{
		m_window.clear();
		background.draw(m_window);
		m_window.draw(text);
		m_window.display();

		if (auto event = sf::Event{}; m_window.pollEvent(event))
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Enter)
					return;
				break;
			case sf::Event::MouseButtonReleased:
				return;
			}
	}
}
