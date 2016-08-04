#ifndef WINDOWW_H
#define WINDOWW_H

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
class Windoww
{
public:
	Windoww(const sf::Vector2u& windowSize, const std::string& windowTitle);
	~Windoww();

	bool isRunning() const { return m_window.isOpen(); }

	void beginDraw();
	void draw(sf::Drawable& drawable);
	void endDraw();

	void destroy();
	void update();
	sf::Vector2u GetSize()& { return m_windowSize; }
	sf::RenderWindow& getWindow() { return m_window; }
	sf::FloatRect getViewSpace();

private:
	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_fullScreen;

	void create();
	
	void setup(const sf::Vector2u& windowSize, const std::string& windowTitle);
};
#endif // !WINDOW_H
