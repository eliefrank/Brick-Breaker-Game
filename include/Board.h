#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "Ball.h"
#include "Bullet.h"
#include "BrickBreak.h"
#include "BrickNoBreak.h"
#include "Collisions.h"
#include "BaseBonus.h"
#include "Level.h"
#include "Stats.h"

class Board
{
public:
	Board(std::shared_ptr<b2World> world, std::shared_ptr<Player> player);
	void draw(sf::RenderWindow& window) const;
	void move();
	void setPlayerDir(Direction d);
	GameObj* getObjWithId(const int obj);
	void processCollision(GameObj& obj1, GameObj& obj2);
	void updateBoard();
	bool noBallsLeft() const;
	bool noBricksLeft() const;
	void resetLevel();
	void fullResetLevel();
	void setLevel(const Level& level);
	int updateLives();
	int updateNumBalls();

private:
	void addWalls();
	void getBreakersFromPlayer();
	void handleCollisions();
	void clean();
	void checkOutOfBoard();
	void getBonus(int i);
	void buildBricks();
	void updateStats();

	std::vector<std::unique_ptr<BaseBrick>> m_bricks;
	std::vector<std::unique_ptr<Breaker>> m_breakers;
	std::vector<std::unique_ptr<GameObj>> m_walls;
	std::vector<std::unique_ptr<BaseBonus>> m_bonuses;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<b2World> m_world;
	Collisions m_collisions;
	const Level* m_currLevel = NULL;
	int m_numNoBreak = 0;
	Stats m_stats;
	BaseImg m_background;
};
