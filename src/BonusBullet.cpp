#include "BonusBullet.h"
#include "Player.h"
#include "Bullet.h"

BonusBullet::BonusBullet(b2World& world, const sf::Vector2f& loc, const sf::Vector2f& size)
	:BaseBonus(world, loc, size, Type::GiftBullets)
{
}

void BonusBullet::handleBonus(Player& player)
{
	ResourceManager::instance().playSFXbullet();
	
	if (getElapesedTime().asSeconds() <= 5){
		if (m_clock.getElapsedTime().asMilliseconds() > 300)
		{
			m_clock.restart();
  			auto loc = player.getPosition();
			player.addBreakers(std::make_unique<Bullet>(*(player.getWorld()), sf::Vector2f(loc.x - (player.getSize().x / 2) + BULLET_W / 2, loc.y - BULLET_H / 2)));
			player.addBreakers(std::make_unique<Bullet>(*(player.getWorld()), sf::Vector2f(loc.x + (player.getSize().x / 2) - BULLET_W / 2, loc.y - BULLET_H / 2)));
		}
	}
	else
		setRemove();
}
