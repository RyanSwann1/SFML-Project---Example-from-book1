#include "StateManager.h"

StateManager::StateManager(SharedContext & sharedContext) : m_sharedContext(sharedContext)
{
	registerState<StateIntro>(GameState::Intro);
	registerState<StateGame>(GameState::Game);
}

StateManager::~StateManager()
{
	clearStates();
}

void StateManager::switchTo(const GameState state)
{
	for (auto cIter = m_states.begin(); cIter != m_states.cend(); cIter++)
	{
		if (cIter->first == state)
		{
			m_states.back().second->onExit();
			GameState gameState = cIter->first;
			StateBase* tempState = cIter->second;
			m_states.erase(cIter);
			m_states.emplace_back(gameState, tempState);
			m_states.back().second->onEnter();
			m_sharedContext.m_window->getWindow().setView(tempState->getView());
			return;
		}
	}

	createState(state);
	m_states.back().second->onEnter();
	m_sharedContext.m_window->getWindow().setView(m_states.back().second->getView());
}

void StateManager::remove(const GameState state)
{
	for (auto Iter = m_states.begin(); Iter != m_states.end(); Iter++)
	{
		if (Iter->first == state)
		{
			delete Iter->second;
			Iter->second = nullptr;
			m_states.erase(Iter);
			return;
		}
	}
}

void StateManager::update(const sf::Time & timer)
{
	for(auto cIter = m_states.cbegin(); cIter != m_states.cend(); cIter++)
	{ 
		cIter->second->update(timer);
	}
}

void StateManager::draw()
{
	for (auto cIter = m_states.cbegin(); cIter != m_states.cend(); cIter++)
	{
		m_sharedContext.m_window->getWindow().setView(cIter->second->getView()); // To Draw every state so it is in the exact same position for the views
		cIter->second->draw();
	}
}

void StateManager::createState(const GameState state)
{
	auto tempState = m_stateFactory.find(state);
	if (tempState != m_stateFactory.cend())
	{
		m_states.emplace_back(tempState->first, tempState->second);
		tempState->second->m_view = m_sharedContext.m_window->getWindow().getDefaultView(); 
		m_states.back().second->onCreate();
	}
}

void StateManager::clearStates()
{
	//Clear State Factory
	for (auto iter = m_stateFactory.begin(); iter != m_stateFactory.end();)
	{
		delete iter->second;
		iter->second = nullptr;
		iter = m_stateFactory.erase(iter);
	}

	//Clear States
	for (auto iter = m_states.begin(); iter != m_states.end();)
	{
		delete iter->second;
		iter->second = nullptr;
		m_states.erase(iter);
	}
}
