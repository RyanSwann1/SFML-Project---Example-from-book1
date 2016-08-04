#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "Utilities.h"
#include "Direction.h"
#include <SFML\Graphics.hpp>
#include <map>
#include <fstream>

#include <sstream>
#include <string>

class AnimationBase;
class AnimationDirectional;
class TextureManager;
class SpriteManager
{
public:
	SpriteManager(TextureManager* textureManager);
	~SpriteManager();

	bool loadSheet(const std::string& file);
	void releaseSheet();
	
	inline void setSpriteSize(const sf::Vector2f& spriteSize);
	void setSpritePos(const sf::Vector2f& spritePos) { m_sprite.setPosition(spritePos); }
	inline void setDirection(const Direction direction);
	void cropSprite(const sf::IntRect& rect);

	sf::Vector2f getSpriteSize() const { return m_spriteSize; }
	Direction getDirection() const { return m_direction; }
	AnimationBase* getCurrentAnimation();
	bool setAnimation(const std::string& name, 
		const bool play = false, 
		const bool loop = false);


	void update(const sf::Time& timer);
	void draw(const sf::RenderWindow& window);
private:
	TextureManager* m_textureManager;
	AnimationBase* m_currentAnimation;
	Direction m_direction; 
	std::string m_textureName;
	std::string m_animationType;
	sf::Sprite m_sprite;
	sf::Vector2f m_spriteScale;
	sf::Vector2f m_spriteSize;

	std::map<std::string, AnimationBase*> m_animations;
};
#endif // !SPRITE_MANAGER_H
