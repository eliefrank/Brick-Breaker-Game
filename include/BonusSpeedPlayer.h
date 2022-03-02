#pragma once
#include "BaseBonus.h"

class BonusSpeedPlayer : public BaseBonus
{
public:
	BonusSpeedPlayer(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size);
	virtual void handleBonus(Player& player) override;

private:
	VelocityPlayer m_vel = VelocityPlayer::Fast;
};
