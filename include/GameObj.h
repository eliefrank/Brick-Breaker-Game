#pragma once
#include "BaseImg.h"
#include "PhysicsObj.h"

static int ID = 0;

class GameObj : public BaseImg
{
public:
	GameObj(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t);
	void updateLoc();
	void setLocation(const sf::Vector2f& loc);
	void applyForce(const b2Vec2& force);
	int getID() const;
	void setRemove();
	bool getRemove() const;
	bool isOut() const;
	void checkVelocity();
	void updateVelocity();
	void setSensor();
	void setSize(const sf::Vector2f& size);
	void setCollided(bool collided);
	bool getCollided() const;

private:
	PhysicsObj m_phyObj;
	int m_ID;
	bool m_remove = false;
	bool m_collided = false;
};
