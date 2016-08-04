#include "Game.h"

#include <iostream>

Game::Game(const sf::Vector2u& windowSize, const std::string& windowTitle) : m_window(windowSize, windowTitle), m_stateManager(m_sharedContext)
{
	m_timeElasped.Zero;
	m_sharedContext.m_window = &m_window;
}

Game::~Game()
{
}

void Game::update()
{
	//float frameTime = 1;
	//if (m_timeElasped.asSeconds() > frameTime)
	//{
	//	m_timeElasped = sf::Time::Zero;
	//	std::cout << "Move" << "\n";

	m_window.update();
	m_stateManager.update(m_timeElasped);
}

void Game::render()
{
	m_window.beginDraw();
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::lateUpdate()
{
	restartClock();
}