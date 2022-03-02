#pragma once
#include "MovingObj.h"
#include "BaseBonus.h"
#include "Breaker.h"

class Player : public MovingObj
{
public:
	Player(std::shared_ptr<b2World> world);
	virtual void draw(sf::RenderWindow& window);
	virtual void move() override;
	void setDir(Direction dir);
	int getLives() const;
	int updateLives(int l);
	void updateScore(int score);
	int getScore() const;
	void addBonus(std::unique_ptr<BaseBonus> bonus);
	void handleBonuses();
	void setSize(SizePlayer size);
	void setVelocity(VelocityPlayer vel);
	b2World* getWorld() const;
	void addBreakers(std::unique_ptr<Breaker> breaker);
	std::vector<std::unique_ptr<Breaker>> getBreakers();
	void reset();
	int getNumBalls() const;
	int updateNumBalls();
	void ResetNumBalls();
	void ResetLivesAndScore();

private:
	void updateSize();
	bool inBoardR() const;
	bool inBoardL() const;
	void updateAnimate();

	int m_score = 0;
	int m_numOfBalls = NUM_OF_BALLS;
	int m_lives = INIT_LIVES;

	std::vector<std::unique_ptr<BaseBonus>> m_bonuses;
	std::vector<std::unique_ptr<Breaker>> m_breakers;
	std::shared_ptr<b2World> m_world;

	SizePlayer m_size = SizePlayer::Regular;
	VelocityPlayer m_velocity = VelocityPlayer::Regular;
	Direction m_dir = Direction::Stop;
	Type m_type = Type::Paddle;

	sf::Clock m_clock;
	sf::Clock m_clockAni;
};
