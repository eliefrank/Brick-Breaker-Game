#pragma once
#include "MovingObj.h"

class Player;

class BaseBonus : public MovingObj
{
public:
	BaseBonus(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size, Type t);
	void move();
	virtual void handleBonus(Player& player) = 0;
	void start();
	sf::Time getElapesedTime() const;
	void drawInBrick(sf::RenderWindow& window, const sf::Vector2f& size);

private:
	sf::Clock m_clock;
	BaseImg m_gift;
};
