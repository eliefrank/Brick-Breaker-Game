#pragma once
#include "BaseBrick.h"

class BrickBreak : public BaseBrick
{
public:
	BrickBreak(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type color);
	virtual void handleCollisions() override;

private:
	int m_lives = 0;
	Type m_color;
};
	