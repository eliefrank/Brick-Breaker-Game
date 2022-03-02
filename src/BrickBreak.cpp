#include "BrickBreak.h"

BrickBreak::BrickBreak(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type color)
	:BaseBrick(world, loc, size, Type::GrayBrick), m_color(color)
{
    addBonus(world);
	setTexture(m_color);
	if (m_color >= Type::BrownBrick)
		m_lives++;
	if (m_color >= Type::DBlueBrick)
		m_lives++;
}

void BrickBreak::handleCollisions()
{
	if (m_lives)
	{
		int type = (int)m_color + 1;
		m_color = (Type)type;
		setTexture(m_color);
		setCollided(false);
		m_lives--;
	}
	else
		setRemove();
}
