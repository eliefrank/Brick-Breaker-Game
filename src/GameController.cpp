#include "GameController.h"

GameController::GameController()
    :m_window(sf::VideoMode(WIN_W, WIN_H), "Brick_Breaker"),
     m_world(std::make_shared<b2World>(b2Vec2(0.f, 0.f))),
     m_player(std::make_shared<Player>(m_world)),
     m_menu(m_window)
{
    m_window.setFramerateLimit(60);
    srand((int)time(NULL));
    readLevels();
}

void GameController::run()
{
    LevelController levCon(m_window, m_world, m_player);

    while(m_window.isOpen() && m_menu.run())
    {
        m_player->ResetLivesAndScore();
        for (auto& level : m_levels)
        {
            m_currLevel = level.getLevelNum();
            levCon.setLevel(level);
            if (!levCon.startLevel()){
                gameLost();
                break;
            }
            levelWon();
        }
        if (m_player->getLives())
            completeAllLevels();
    }
}

void GameController::readLevels()
{
    for (int i = 0; i < NUM_OF_LEVELS; i++)
        m_levels.push_back(Level(i + 1));
}

void GameController::levelWon()
{
    ResourceManager::instance().playSFXnextLevel();
    BaseImg youWin({ WIN_W / 2,WIN_H / 2 }, { WIN_W,WIN_H }, Type::YouWin);
    std::vector <sf::Text> texts;
    TextsLevelWon(texts);
    
    while (m_window.isOpen())
    {
        m_window.clear();
        youWin.draw(m_window);
        for(auto& text : texts)
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
			}
    }
}

void GameController::TextsLevelWon(std::vector <sf::Text>& texts)
{
    auto& font = ResourceManager::instance().getFont();
    texts.push_back(sf::Text("Level " + std::to_string(m_currLevel) + " is complete", font, 70));
    texts.push_back(sf::Text("Press Enter to continue", font, 70));
    texts[0].setPosition({ WIN_W / 2 - (texts[0].getGlobalBounds().width)/2 , WIN_H / 2 - 300 });
    texts[1].setPosition({ WIN_W / 2 - (texts[1].getGlobalBounds().width) / 2, WIN_H / 2 + 200 });
}

void GameController::TextsGameOver(std::vector<sf::Text>& options)
{
    auto& font = ResourceManager::instance().getFont();
    options.push_back(sf::Text("SaveYourScore", font, 50));
    options.push_back(sf::Text("MENU", font, 50));
    options[SAVE_SCORE].setPosition({ WIN_W / 2 - (options[SAVE_SCORE].getGlobalBounds().width) / 2, WIN_H / 2 + 250 });
    options[MENU].setPosition({ WIN_W / 2 - (options[MENU].getGlobalBounds().width) / 2, WIN_H / 2 + 330 });
}

void GameController::gameLost()
{
    ResourceManager::instance().playSFXlost();
    gameOver(Type::GameOver);
}

void GameController::completeAllLevels()
{
    gameOver(Type::EndOfGame);
}

void GameController::gameOver(Type t)
{
    BaseImg img({ WIN_W / 2,WIN_H / 2 }, { WIN_W,WIN_H }, t);
    std::vector <sf::Text> options;
    TextsGameOver(options);

    while (m_window.isOpen())
    {
        m_window.clear();
        img.draw(m_window);
        for (auto& option : options)
            m_window.draw(option);
        m_window.display();

        if (auto event = sf::Event{}; m_window.pollEvent(event))
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
            {
                auto loc = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (clickedOn(options[SAVE_SCORE], loc))
                {
                    m_menu.addScore(m_player->getScore());
                    return;
                }
                if (clickedOn(options[MENU], loc))
                    return;
                break;
            }
            }
    }
}
