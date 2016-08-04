#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "SharedContext.h"
#include "StateBase.h"
#include "StateIntro.h"
#include "StateGame.h"

#include <map>
#include <vector>

enum class GameState{ Intro, MainMenu, Game, Credits };
class StateBase;
class StateIntro;
class StateGame;
class StateManager
{
public:
	StateManager(SharedContext& sharedContext);
	~StateManager();

	void switchTo(const GameState state);
	void remove(const GameState state);
	void update(const sf::Time& timer);
	void draw();

	template <class T>
	void registerState(const GameState state);
	
private:
	std::map<GameState, StateBase*> m_stateFactory;
	std::vector<std::pair<GameState, StateBase*>> m_states;

	SharedContext m_sharedContext;

	void createState(const GameState state);
	void clearStates();
};


template<class T>
inline void StateManager::registerState(const GameState state)
{
	auto newState = m_stateFactory.find(state);
	if (newState == m_stateFactory.end())
	{
		m_stateFactory[state] = new T(this);
	}
}
#endif // !STATE_MANAGER_H