#include "BonusSpeedPlayer.h"
#include "Player.h"

BonusSpeedPlayer::BonusSpeedPlayer(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
    :BaseBonus(world, loc, size, Type::GiftFast)
{
    int random = rand() % 2;

    switch (random)
    {
    case 0:
        setTexture(Type::GiftSlow);
        m_vel = VelocityPlayer::Slow;
    }
}

void BonusSpeedPlayer::handleBonus(Player& player)
{
    if (getElapesedTime().asSeconds() <= 10)
        player.setVelocity(m_vel);
    else
    {
        setRemove();
        player.setVelocity(VelocityPlayer::Regular);
    }
}
