#include "BonusBalls.h"
#include "Player.h"
#include "Ball.h"

BonusBalls::BonusBalls(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
	:BaseBonus(world, loc, size, Type::GiftBall)
{
}

void BonusBalls::handleBonus(Player& player)
{
	setRemove();
	auto loc = player.getPosition();
	
	player.addBreakers(std::make_unique<Ball>(*(player.getWorld()), sf::Vector2f(loc.x, loc.y - BALL_H - 1), b2Vec2(0, -1)));
	player.addBreakers(std::make_unique<Ball>(*(player.getWorld()), sf::Vector2f(loc.x + BALL_W + 2, loc.y - BALL_H - 1), b2Vec2(1, -1)));
	player.addBreakers(std::make_unique<Ball>(*(player.getWorld()), sf::Vector2f(loc.x - BALL_W - 2, loc.y - BALL_H - 1), b2Vec2(-1, -1)));
}
