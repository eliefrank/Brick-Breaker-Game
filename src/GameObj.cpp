#include "GameObj.h"

GameObj::GameObj(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t)
	:BaseImg(loc, size, t), m_phyObj(world, loc, size, t), m_ID(ID++)
{
	m_phyObj.setID(m_ID);
}

void GameObj::updateLoc()
{
	auto pos = m_phyObj.getPosition();
	BaseImg::setPosition(sf::Vector2f(pos.x * PPM, pos.y * PPM));
}

void GameObj::setLocation(const sf::Vector2f& loc)
{
	m_phyObj.setPosition(loc);
	updateLoc();
}

void GameObj::applyForce(const b2Vec2& force)
{
	m_phyObj.applyForce(force);
}

int GameObj::getID() const
{
	return m_ID;
}

void GameObj::setRemove()
{
	m_remove = true;
}

bool GameObj::getRemove() const
{
	return m_remove;
}

bool GameObj::isOut() const
{
	return (getPosition().y > WIN_H || getPosition().y < 0 || getPosition().x > WIN_W || getPosition().x < 0);
}

void GameObj::updateVelocity()
{
	m_phyObj.updateVelocity();
}

void GameObj::setSensor()
{
	m_phyObj.setSensor();
}

void GameObj::setSize(const sf::Vector2f& size)
{
	BaseImg::setSize(size);
	m_phyObj.setSize(size);
}

void GameObj::setCollided(bool collided)
{
	m_collided = collided;
}

bool GameObj::getCollided() const
{
	return m_collided;
}

void GameObj::checkVelocity()
{
	m_phyObj.checkVelocity();
}
