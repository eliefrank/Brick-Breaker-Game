#include "Board.h"

Board::Board(std::shared_ptr<b2World> world, std::shared_ptr<Player> player)
	:m_world(world), m_player(player), m_background({ WIN_W / 2,WIN_H / 2 }, { WIN_W,WIN_H }, Type::Background)
{
	addWalls();
}

void Board::draw(sf::RenderWindow& window) const
{
	m_background.draw(window);
	for (auto& wall : m_walls)
		wall->draw(window);
	for (auto& brick : m_bricks)
		brick->draw(window);
	for (auto& bonus : m_bonuses)
		bonus->draw(window);
	for (auto& breaker : m_breakers)
		breaker->draw(window);
	m_player->draw(window);
	m_stats.draw(window);
}

void Board::move()
{
	m_player->move();
	for (auto& breaker : m_breakers)
		breaker->move();
	for (auto& bonus : m_bonuses)
		bonus->move();
}

void Board::setPlayerDir(Direction d)
{
	m_player->setDir(d);
}

GameObj* Board::getObjWithId(const int obj)
{
	for (auto& brick : m_bricks)
		if (brick->getID() == obj)
			return brick.get();

	for (auto& breaker : m_breakers)
		if (breaker->getID() == obj)
			return breaker.get();

	if (m_player->getID() == obj)
		return m_player.get();

	for (auto& wall : m_walls)
		if (wall->getID() == obj)
			return wall.get();

	for (auto& bonus : m_bonuses)
		if (bonus->getID() == obj)
			return bonus.get();

	return nullptr;
}

void Board::processCollision(GameObj& obj1, GameObj& obj2)
{
	m_collisions.processCollision(obj1, obj2);
}

void Board::updateBoard()
{
	checkOutOfBoard();
	handleCollisions();
	clean();
	m_player->handleBonuses();
	getBreakersFromPlayer();
	updateStats();
}

bool Board::noBallsLeft() const
{
	return (!m_breakers.size());
}

bool Board::noBricksLeft() const
{
	return (!(m_bricks.size() - m_numNoBreak));
}

void Board::resetLevel()
{
	m_breakers.clear();
	m_bonuses.clear();
	m_player->reset();
	m_breakers.push_back(std::make_unique<Ball>(*m_world));
}

void Board::fullResetLevel()
{
	resetLevel();
	m_player->ResetNumBalls();
	buildBricks();
}

void Board::setLevel(const Level& level)
{
	m_currLevel = &level;
}

int Board::updateLives()
{
	return m_player->updateLives(-1);
}

int Board::updateNumBalls()
{
	return m_player->updateNumBalls();
}

void Board::addWalls()
{
	m_walls.push_back(std::make_unique<GameObj>(*(m_world.get()), sf::Vector2f(WIN_W / 2, 9), sf::Vector2f(WIN_W, WALL_W),Type::GrayBrick));
	m_walls.push_back(std::make_unique<GameObj>(*(m_world.get()), sf::Vector2f(9, WIN_H / 2), sf::Vector2f(WALL_W, WIN_H), Type::GrayBrick));
	m_walls.push_back(std::make_unique<GameObj>(*(m_world.get()), sf::Vector2f(WIN_W - 9, WIN_H / 2), sf::Vector2f(WALL_W, WIN_W), Type::GrayBrick));
}

void Board::getBreakersFromPlayer()
{
	auto breakers = m_player->getBreakers();
	for (auto& breaker : breakers)
		m_breakers.push_back(std::move(breaker));
}

void Board::handleCollisions()
{
	for (auto& brick : m_bricks)
		if (brick->getCollided())
			brick->handleCollisions();

	for (int i = 0; i < m_bonuses.size(); i++)
		if (m_bonuses[i]->getCollided())
		{
			m_player->addBonus(std::move(m_bonuses[i]));
			m_bonuses.erase(m_bonuses.begin() + i--);
		}
}

void Board::clean()
{
	for (int i = 0; i < m_bricks.size(); i++)
		if (m_bricks[i]->getRemove()){
			getBonus(i);
			m_player->updateScore(POINTS_BREAK*m_currLevel->getLevelNum());
			m_bricks.erase(m_bricks.begin() + i--);
		}

	for (int i = 0; i < m_breakers.size(); i++)
		if (m_breakers[i]->getRemove())
			m_breakers.erase(m_breakers.begin() + i--);

	for (int i = 0; i < m_bonuses.size(); i++)
		if (m_bonuses[i]->getRemove())
			m_bonuses.erase(m_bonuses.begin() + i--);
}

void Board::checkOutOfBoard()
{
	for (auto& breaker : m_breakers)
		if (breaker->isOut())
			breaker->setRemove();

	for (auto& bonus : m_bonuses)
		if (bonus->isOut())
			bonus->setRemove();
}

void Board::getBonus(int i)
{
	auto bonus = m_bricks[i]->getBonus();
	if (bonus) {
		bonus->applyForce({ 0,1 });
		m_bonuses.push_back(std::move(bonus));
	}
}

void Board::buildBricks()
{
	m_bricks.clear();
	auto& world = *(m_world.get());
	auto& size = m_currLevel->getSize();
	auto& bricks = m_currLevel->getBricks();
	m_numNoBreak = 0;

	for (auto& brick : bricks)
	{
		auto& loc = brick.first;
		switch (brick.second)
		{
		case 'A':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::BGreenBrick));
			break;
		case 'B':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::LBlueBrick));
			break;
		case 'C':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::PurpleBrick));
			break;
		case 'D':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::OrangeBrick));
			break;
		case 'E':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::BrownBrick));
			break;
		case 'F':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::RedBrick));
			break;
		case 'G':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::YellowBrick));
			break;
		case 'H':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::DBlueBrick));
			break;
		case 'I':
			m_bricks.push_back(std::make_unique<BrickBreak>(world, loc, size, Type::DGreenBrick));
			break;
		case 'J':
			m_bricks.push_back(std::make_unique<BrickNoBreak>(world, loc, size));
			m_numNoBreak++;
			break;
		}
	}
}

void Board::updateStats()
{
	m_stats.setBrickLeft((int)m_bricks.size() - m_numNoBreak);
	m_stats.setLevel(m_currLevel->getLevelNum());
	m_stats.setLives(m_player->getLives());
	m_stats.setScore(m_player->getScore());
	m_stats.setBalls(m_player->getNumBalls());
	m_stats.updateStatsTexts();
}
