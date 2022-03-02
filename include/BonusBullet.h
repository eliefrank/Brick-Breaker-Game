#pragma once
#include "BaseBonus.h"

class BonusBullet : public BaseBonus
{
public:
	BonusBullet(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size);
	virtual void handleBonus(Player& player) override;

private:	
	sf::Clock m_clock;
};
