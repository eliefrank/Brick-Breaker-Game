#include "LevelController.h"

LevelController::LevelController(sf::RenderWindow& window, std::shared_ptr<b2World> world, std::shared_ptr<Player> player)
    :m_window(window), m_world(world),m_board(world, player), m_listener(m_board)
{
    m_world->SetContactListener(&m_listener);
}

bool LevelController::startLevel()
{  
    ResourceManager::instance().setSong(Sound::Game);

    while (m_window.isOpen())
    {
        handleDisplay();
        handleEvents();
        if (m_board.noBricksLeft())
            return true;

        m_board.updateBoard();
        if (m_start)
        {
            m_board.move();
            m_world->Step(TIMESTEP, VELITER, POSITER);
            if (!handleDisqualified())
                return false;
        }
    }
    return false;
}

void LevelController::setLevel(const Level& level)
{
    m_start = false;
    m_board.setLevel(level);
    m_board.fullResetLevel();
}

void LevelController::handleDisplay() const
{
    m_window.clear();
    m_board.draw(m_window);
    m_window.display();
}

void LevelController::handleEvents()
{
    if (auto event = sf::Event{}; m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            handleKeyboardEvent(event);
            break;
        case sf::Event::KeyReleased:
            m_board.setPlayerDir(Direction::Stop);
            break;
        }
    }
}

void LevelController::handleKeyboardEvent(const sf::Event& event)
{
    switch (event.key.code)
    {
    case(sf::Keyboard::Left):
        if(m_start)
            m_board.setPlayerDir(Direction::Left);
        break;
    case(sf::Keyboard::Right):
        if (m_start)
            m_board.setPlayerDir(Direction::Right);
        break;
    case(sf::Keyboard::Up):
        m_start = true;
        break;
    case(sf::Keyboard::Space):
        handlePaused();
        break;
    }
}

bool LevelController::handleDisqualified()
{
    if (m_board.noBallsLeft())
    {
        m_start = false;
        if (m_board.updateNumBalls())
            m_board.resetLevel();
        else if (m_board.updateLives())
            handleResetBeginLevel();
        else
            return false;
        for (auto event = sf::Event{}; m_window.pollEvent(event););
    }
    return true;
}

void LevelController::handleResetBeginLevel()
{
    printMsg();
    m_board.fullResetLevel();
}

void LevelController::printMsg()
{
    auto& font = ResourceManager::instance().getFont();
    sf::Text text("Out of Balls!", font, 120);
    text.setPosition({ WIN_W / 2 - (text.getGlobalBounds().width) / 2, WIN_H / 2 - 120});
    sf::RectangleShape rs({ text.getGlobalBounds().width + 5 , text.getGlobalBounds().height + 30 });
    rs.setPosition(text.getPosition());
    rs.setFillColor(sf::Color::Red);
    
    sf::Clock clock;
    clock.restart();
    while (clock.getElapsedTime().asSeconds() < 2)
    {
        m_window.clear();
        continueWorld();
        m_window.draw(rs);
        m_window.draw(text);
        m_window.display();
    }  
}

void LevelController::handlePaused()
{
    auto& font = ResourceManager::instance().getFont();
    sf::Text text("Paused", font, 120);
    text.setPosition({ WIN_W / 2 - (text.getGlobalBounds().width) / 2, WIN_H / 2 - 120 });

    m_window.draw(text);
    m_window.display();

    while (1)
    {
        if (auto event = sf::Event{}; m_window.pollEvent(event))
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                    return;
    }
}

void LevelController::continueWorld()
{
    m_world->Step(TIMESTEP, VELITER, POSITER);
    m_board.move();
    m_board.draw(m_window);
}
