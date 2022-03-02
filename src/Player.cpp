#include "Player.h"

Player::Player(std::shared_ptr<b2World> world)
	:MovingObj(*world ,sf::Vector2f(PLAYER_LOC_X, PLAYER_LOC_Y),  sf::Vector2f(PLAYER_W, PLAYER_H), Type::Paddle)
    ,m_world(world)
{
}

void Player::draw(sf::RenderWindow& window)
{
    if (m_clockAni.getElapsedTime().asMilliseconds() > 166)
        updateAnimate();

    BaseImg::draw(window);
}

void Player::move()
{
    sf::Vector2f newLoc = getPosition();
    auto elapsed = m_clock.restart();
    float toMove = ((350.f * elapsed.asSeconds()))*playerVel[(int)m_velocity];

    if (m_dir == Direction::Left)
        newLoc.x -= toMove;
    if (m_dir == Direction::Right)
        newLoc.x += toMove;

    GameObj::setLocation(newLoc);

    if (!inBoardL())
        setLocation({ WALL_W + 0.1f + getSize().x / 2,getPosition().y });
    else if (!inBoardR())
        setLocation({ WIN_W - WALL_W - 0.1f - getSize().x / 2,getPosition().y });
}

void Player::setDir(Direction dir)
{
    m_dir = dir;
}

int Player::getLives() const
{
    return m_lives;
}

int Player::updateLives(int l)
{
    m_lives += l;
    return m_lives;
}

void Player::updateScore(int score)
{
    m_score += score;
}

int Player::getScore() const
{
    return m_score;
}

void Player::addBonus(std::unique_ptr<BaseBonus> bonus)
{
    bonus->start();
    m_bonuses.push_back((std::move(bonus)));
}

void Player::handleBonuses()
{
    for (int i = 0; i < m_bonuses.size(); i++)
    {
        m_bonuses[i]->handleBonus(*this);
        if (m_bonuses[i]->getRemove())
            m_bonuses.erase(m_bonuses.begin() + i--);
    }
    updateSize();
}

void Player::setSize(SizePlayer size)
{
    m_size = size;
}

void Player::setVelocity(VelocityPlayer vel)
{
    m_velocity = vel;
}

b2World* Player::getWorld() const
{
    return m_world.get();
}

void Player::addBreakers(std::unique_ptr<Breaker> breaker)
{
    m_breakers.push_back(std::move(breaker));
}

std::vector<std::unique_ptr<Breaker>> Player::getBreakers()
{
    return std::move(m_breakers);
}

void Player::updateSize()
{
    GameObj::setSize(playerSizes[(int)m_size]);
}

void Player::reset()
{
    setLocation({ PLAYER_LOC_X, PLAYER_LOC_Y });
    setSize(SizePlayer::Regular);
    updateSize();
    setVelocity(VelocityPlayer::Regular);
    m_bonuses.clear();
    setDir(Direction::Stop);
}

int Player::updateNumBalls()
{
    return (--m_numOfBalls);
}

void Player::ResetNumBalls()
{
    m_numOfBalls = NUM_OF_BALLS;
}

void Player::ResetLivesAndScore()
{
    m_lives = INIT_LIVES;
    m_score = 0;
}

int Player::getNumBalls() const
{
    return m_numOfBalls;
}

bool Player::inBoardR() const
{
    return ((getPosition().x + getSize().x / 2) < (WIN_W - WALL_W - 0.1f));
}

bool Player::inBoardL() const
{
    return ((getPosition().x - (getSize().x / 2) > WALL_W + 0.1f));
}

void Player::updateAnimate()
{
    m_clockAni.restart();
    int temp = (int)m_type + 1;
    if (temp - 2 == (int)Type::Paddle)
        temp -= 2;
    m_type = (Type)temp;
    setTexture(m_type);
}
