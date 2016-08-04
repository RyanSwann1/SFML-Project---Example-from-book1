#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "Windoww.h"
#include "SharedContext.h"
#include "StateManager.h"
class Game
{
public:
	Game(const sf::Vector2u& windowSize, const std::string& windowTitle);
	~Game();
	bool isRunning() { return m_window.isRunning(); }

	void update();
	void render();
	void lateUpdate();

private:
	SharedContext m_sharedContext;
	StateManager m_stateManager;
	Windoww m_window;
	sf::Clock m_clock;
	sf::Time m_timeElasped;

	void restartClock() { m_timeElasped += m_clock.restart(); }
};
#endif // !GAME_H
