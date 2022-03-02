#pragma once
#include "BaseBonus.h"

class BonusLives : public BaseBonus
{
public:
	BonusLives(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size);
	virtual void handleBonus(Player& player) override;

private:
};
