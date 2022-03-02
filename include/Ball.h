#pragma once
#include "Breaker.h"

class Ball : public Breaker
{
public:
	Ball(b2World& world, const sf::Vector2f& loc, const b2Vec2& force);
	Ball(b2World& world);
	virtual void move() override;

private:
};
