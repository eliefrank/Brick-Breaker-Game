#pragma once
#include "BaseBrick.h"

class BrickNoBreak :public BaseBrick
{
public:
	BrickNoBreak(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size);
	virtual void handleCollisions() override;

private:
	bool m_trans = false;
};
