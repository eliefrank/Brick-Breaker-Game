#pragma once
#include "BaseBonus.h"

class BonusSizePlayer : public BaseBonus
{
public:
	BonusSizePlayer(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size);
	virtual void handleBonus(Player& player) override;

private:
	SizePlayer m_size = SizePlayer::Big;
};
