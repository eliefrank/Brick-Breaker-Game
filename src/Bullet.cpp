#include "Bullet.h"

Bullet::Bullet(b2World& world, const sf::Vector2f& loc)
	:Breaker(world, loc, sf::Vector2f(BULLET_W, BULLET_H), Type::Bullet)
{
	GameObj::applyForce({ 0,-1});
	GameObj::setSensor();
}

void Bullet::move()
{
	updateLoc();
}
