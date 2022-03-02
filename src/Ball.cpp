#include "Ball.h"

Ball::Ball(b2World& world, const sf::Vector2f& loc, const b2Vec2& force)
	:Breaker(world, loc, sf::Vector2f(BALL_W, BALL_H), Type::Ball)
{
	GameObj::applyForce(force);
}

Ball::Ball(b2World& world)
	:Ball(world, sf::Vector2f(BALL_LOC_X, BALL_LOC_Y), b2Vec2(0, -1))
{
}

void Ball::move()
{
	GameObj::checkVelocity();
	updateLoc();
}
