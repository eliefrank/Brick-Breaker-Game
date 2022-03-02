#pragma once
#include "Breaker.h"

class Bullet : public Breaker
{
public:
	Bullet(b2World& world ,const sf::Vector2f& loc);
	virtual void move() override;

private:
};
