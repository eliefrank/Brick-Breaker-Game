#include "BonusLives.h"
#include "Player.h"

BonusLives::BonusLives(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
	:BaseBonus(world, loc, size, Type::Heart)
{
}

void BonusLives::handleBonus(Player& player)
{
	player.updateLives(1);
	setRemove();
}
