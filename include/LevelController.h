#pragma once
#include "Board.h"
#include "MyListener.h"

class LevelController
{
public:
	LevelController(sf::RenderWindow& window, std::shared_ptr<b2World> world, std::shared_ptr<Player> player);
	bool startLevel();
	void setLevel(const Level& level);

private:
	void handleDisplay() const;
	void handleEvents();
	void handleKeyboardEvent(const sf::Event& event);
	bool handleDisqualified();
	void handleResetBeginLevel();
	void continueWorld();
	void printMsg();
	void handlePaused();

	sf::RenderWindow& m_window;
	std::shared_ptr<b2World> m_world;
	Board m_board;
	MyListener m_listener;
	bool m_start = false;
};
