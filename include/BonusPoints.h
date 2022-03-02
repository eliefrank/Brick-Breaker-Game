#pragma once
#include "BaseBonus.h"

class BonusPoints : public BaseBonus
{
public:
	BonusPoints(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size);
	virtual void handleBonus(Player& player) override;

private:
	int m_points = 50;
};
