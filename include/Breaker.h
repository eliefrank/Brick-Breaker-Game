#pragma once
#include "MovingObj.h"

class Breaker :public MovingObj
{
public:
	Breaker(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t);

private:
};
