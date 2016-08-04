#include "Windoww.h"



Windoww::Windoww(const sf::Vector2u& windowSize, const std::string& windowTitle)
{
	setup(windowSize, windowTitle);
}

Windoww::~Windoww()
{
}

void Windoww::setup(const sf::Vector2u & windowSize, const std::string & windowTitle)
{
	m_windowTitle = windowTitle;
	m_windowSize = windowSize;
	m_fullScreen = false;
	create();
}

void Windoww::beginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Windoww::draw(sf::Drawable & drawable)
{
	m_window.draw(drawable);
}

void Windoww::endDraw()
{
	m_window.display();
}

void Windoww::update()
{
	//While there are pending events
	while (m_window.pollEvent(m_event))
	{
		//Check the event that has been polled
		switch (m_event.type)
		{
		case sf::Event::Closed:
			destroy();
			break;

			//No differnet events processed
		default:
			break;
		}
	}
}

sf::FloatRect Windoww::getViewSpace()
{
	sf::Vector2f viewCenter = m_window.getView().getCenter();
	sf::Vector2f viewSize = m_window.getView().getSize();
	sf::Vector2f viewSizeHalf(viewSize.x / 2.0f, viewSize.y / 2.0f);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}

void Windoww::create()
{
	auto style = sf::Style::Default;
	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);
}

void Windoww::destroy()
{
	m_window.close();
}
