#include "Breaker.h"

Breaker::Breaker(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t)
	:MovingObj(world, loc, size, t)
{
}
