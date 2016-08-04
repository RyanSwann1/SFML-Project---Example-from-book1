#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <SFML\System\Time.hpp>
class StateManager;
class StateBase
{
	friend StateManager;
public:
	StateBase(StateManager* stateManager) : m_stateManager(stateManager) {}

	virtual void onEnter() {}
	virtual void onExit() {}

	virtual void onCreate() {}
	virtual void onDestroy() {}

	virtual void update(const sf::Time& timer) {}
	virtual void draw() {}

	StateManager* getStateManager() { return m_stateManager; }
	sf::View& getView() { return m_view; }

protected:
	StateManager* m_stateManager;
	sf::View m_view;

private:

};
#endif // !STATE_BASE_H
