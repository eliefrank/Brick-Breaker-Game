#include "MovingObj.h"

MovingObj::MovingObj(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t)
	:GameObj(world, loc, size, t)
{
}
