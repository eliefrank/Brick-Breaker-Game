#include "BrickNoBreak.h"

BrickNoBreak::BrickNoBreak(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
	:BaseBrick(world, loc, size, Type::GrayBrick)
{
}

void BrickNoBreak::handleCollisions()
{
	if (m_trans)
		setCollided(false);
	m_trans = (!m_trans);
	setTransparent(m_trans);	
}
