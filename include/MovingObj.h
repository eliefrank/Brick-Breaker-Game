#pragma once
#include "GameObj.h"

class MovingObj : public GameObj
{
public:
	MovingObj(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t);
	virtual void move() = 0;

private:
};
