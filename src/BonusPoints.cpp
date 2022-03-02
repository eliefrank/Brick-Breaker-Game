#include "BonusPoints.h"
#include "Player.h"

BonusPoints::BonusPoints(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
	:BaseBonus(world, loc, size, Type::GiftPoint50)
{
    int random = rand() % 7;

    switch (random)
    {
    case 0:
        setTexture(Type::GiftPoint100);
        m_points = 100;
        break;
    case 1:
        setTexture(Type::GiftPoint250);
        m_points = 250;
        break;
    case 2:
        setTexture(Type::GiftPoint500);
        m_points = 500;
        break;
    }
}

void BonusPoints::handleBonus(Player& player)
{
    player.updateScore(m_points);
    setRemove();
}
