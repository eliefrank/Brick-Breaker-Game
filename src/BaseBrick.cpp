#include "BaseBrick.h"
#include "BonusBalls.h"
#include "BonusBullet.h"
#include "BonusLives.h"
#include "BonusPoints.h"
#include "BonusSizePlayer.h"
#include "BonusSpeedPlayer.h"

BaseBrick::BaseBrick(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t)
	:GameObj(world, loc, size, t)
{
}

std::unique_ptr<BaseBonus> BaseBrick::getBonus()
{
    return std::move(m_bonus);
}

void BaseBrick::draw(sf::RenderWindow& window) const
{
    BaseImg::draw(window);
    if (m_bonus)
        m_bonus->drawInBrick(window, getSize());
}

void BaseBrick::addBonus(b2World& world)
{
    sf::Vector2f size({ getSize().x, getSize().y*3 / 4 });
	int random = rand() % (NUM_OF_BONUSES*3);
    
    switch (random)
    {
    case 0:
        m_bonus = std::make_unique<BonusBalls>(world, getPosition(), size);
        break;
    case 1:
        m_bonus = std::make_unique<BonusBullet>(world, getPosition(), size);
        break;
    case 2:
        m_bonus = std::make_unique<BonusLives>(world, getPosition(), sf::Vector2f(size.x / 2.5f, size.y));
        break;
    case 3:
        m_bonus = std::make_unique<BonusPoints>(world, getPosition(), size);
        break;
    case 4:
        m_bonus = std::make_unique<BonusSizePlayer>(world, getPosition(), size);
        break;
    case 5:
        m_bonus = std::make_unique<BonusSpeedPlayer>(world, getPosition(), size);
        break;
    }
}
