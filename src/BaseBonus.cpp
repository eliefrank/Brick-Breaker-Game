#include "BaseBonus.h"

BaseBonus::BaseBonus(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t)
	:MovingObj(world, loc, size, t), m_gift(loc, size, Type::Star)
{
	GameObj::setSensor();
}

void BaseBonus::move()
{
	updateLoc();
}

void BaseBonus::start()
{
	m_clock.restart();
}

sf::Time BaseBonus::getElapesedTime() const
{
	return m_clock.getElapsedTime();
}

void BaseBonus::drawInBrick(sf::RenderWindow& window, const sf::Vector2f& size)
{
	m_gift.setSize({ size.x / 3, size.y / 2 });
	m_gift.draw(window);
}
