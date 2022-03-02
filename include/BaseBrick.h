#pragma once
#include "GameObj.h"
#include "BaseBonus.h"

class BaseBrick : public GameObj
{
public:
	BaseBrick(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t);
	std::unique_ptr<BaseBonus> getBonus();
	virtual void draw(sf::RenderWindow& window) const;
	virtual void handleCollisions() = 0;
	void addBonus(b2World& world);

private:
	std::unique_ptr<BaseBonus> m_bonus;
};
