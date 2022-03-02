#include "BonusSizePlayer.h"
#include "Player.h"

BonusSizePlayer::BonusSizePlayer(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
	:BaseBonus(world, loc, size, Type::GiftWidePaddle)
{
    int random = rand() % 2;

    switch (random)
    {
    case 0:
        setTexture(Type::GiftNarrowPaddle);
        m_size = SizePlayer::Small;
    }
}

void BonusSizePlayer::handleBonus(Player& player)
{
    if (getElapesedTime().asSeconds() <= 10)
        player.setSize(m_size);
    else
    {
        setRemove();
        player.setSize(SizePlayer::Regular);
    }
}
