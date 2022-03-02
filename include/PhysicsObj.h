#pragma once
#include <Box2D/box2d.h>
#include "ResourceManager.h"

class PhysicsObj
{
public:
	PhysicsObj(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t);
	~PhysicsObj();
	void setPosition(const sf::Vector2f pos);
	b2Vec2 getPosition() const;
	void applyForce(const b2Vec2& force);
	void setID(int id);
	void setSensor();
	void checkVelocity();
	void updateVelocity();
	void setSize(const sf::Vector2f size);

private:
	b2Body* m_body;
	b2FixtureDef m_fixtureDef;
	b2Fixture* m_fixture;
	Type m_t;
};
