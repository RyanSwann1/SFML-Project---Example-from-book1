#include "SpriteManager.h"
#include "TextureManager.h"
#include "AnimationBase.h"
#include "AnimationDirectional.h"


SpriteManager::SpriteManager(TextureManager* textureManager)
	: m_textureManager(textureManager),
	m_currentAnimation(nullptr),
	m_spriteScale(1.0f, 1.0f),
	m_direction(Direction::RIGHT)
{
}

SpriteManager::~SpriteManager()
{
	m_textureManager->releaseResource(m_textureName);
	m_textureManager = nullptr;
	m_currentAnimation = nullptr;
	for (auto iter = m_animations.begin(); iter != m_animations.end();)
	{
		delete iter->second;
		iter = m_animations.erase(iter);
	}
}

bool SpriteManager::loadSheet(const std::string& file)
{
	//std::fstream stream;
	//stream.open(Utils::GetWorkingDirectory() + file);
	//if (stream.is_open())
	//{
	//	std::string line;
	//	while (std::getline(stream, line))
	//	{
	//		if (line[0] == '|') {
	//			continue;
	//		}
	//		std::stringstream keyStream;
	//		std::string type;
	//		keyStream >> type;

	//		if (type == "Texture")
	//		{
	//			//Check to see if a spritesheet hasn't already been initialized - to avoid duplicate entries
	//			if (m_textureName != "")
	//			{
	//				std::cerr << "Duplicate texture entries in: " << file << "\n";
	//				continue;
	//			}
	//			else
	//			{
	//				std::string texture;
	//				keyStream >> texture;
	//				//If could not get the texture
	//				if (!m_textureManager->requireResource(texture))
	//				{
	//					std::cerr << "Could not set up texture: " << texture << "\n";
	//					continue;
	//				}
	//				//Get the texture
	//				else
	//				{
	//					m_textureName = texture; //Assign to new texture
	//					m_sprite.setTexture(*m_textureManager->getResource(m_textureName));
	//				}
	//			}
	//		}
	//		else if (type == "Size") 
	//		{
	//			keyStream >> m_spriteSize.x >> m_spriteSize.y;
	//			setSpriteSize(m_spriteSize);
	//		}
	//		else if (type == "Scale")
	//		{
	//			keyStream >> m_spriteScale.x >> m_spriteScale.y;
	//			m_sprite.setScale(m_spriteScale);
	//		}
	//		else if (type == "AnimationType") {
	//			keyStream >> m_animationType;
	//		}
	//		else if (type == "Animation")
	//		{
	//			std::string name;
	//			keyStream >> name;
	//			if (m_animations.find(name) != m_animations.end())
	//			{
	//				std::cerr << "Duplicate animation: " << name << "\n";
	//				continue;
	//			}
	//			//Create new animation
	//			AnimationBase* animation = nullptr;
	//			if (m_animationType == "Directional") {
	//				animation = new AnimationDirectional();
	//			}
	//			else
	//			{
	//				std::cerr << "Unknown animation type." << "\n";
	//				continue;
	//			}

	//			keyStream >> *animation; //Not sure what this does
	//			animation->setSpriteManager(this);
	//			animation->setName(name);
	//			animation->reset();
	//			m_animations.emplace(name, animation);

	//			if (m_currentAnimation) { continue; }
	//			m_currentAnimation = animation;
	//			m_currentAnimation->play();
	//		}

	//	}
	//	stream.close();
	//	return true;
	//}
	return false;
}

void SpriteManager::releaseSheet()
{
	//Clear current sheet from resources
	m_textureManager->releaseResource(m_textureName); 
	m_currentAnimation = nullptr;
	//Clear all associated animations
	for (auto iter = m_animations.begin(); iter != m_animations.end();)
	{
		delete iter->second;
		iter->second = nullptr;
		iter = m_animations.erase(iter);
	}
}

void SpriteManager::setSpriteSize(const sf::Vector2f & spriteSize)
{
	m_spriteSize = spriteSize;
	m_sprite.setOrigin(m_spriteSize.x / 2.0f, m_spriteSize.y / 2.0f);
}


void SpriteManager::setDirection(const Direction direction)
{
	if (m_direction != direction)
	{
		m_direction = direction;
		//m_animBase->cropSprite();
	}
}

void SpriteManager::cropSprite(const sf::IntRect & rect)
{
	m_sprite.setTextureRect(rect);
}

AnimationBase * SpriteManager::getCurrentAnimation()
{
	return m_currentAnimation;
}

bool SpriteManager::setAnimation(const std::string & name, const bool play, const bool loop)
{
	auto iter = m_animations.find(name);
	if (iter != m_animations.end() && iter->second != m_currentAnimation)
	{
		//Stop the current animation
		if (m_currentAnimation) {
			//m_currentAnimation->stop();
		}
		m_currentAnimation = iter->second;
		//m_currentAnimation->setLooping(loop);
		//if (play) { m_currentAnimation->setPlay(); }
		//m_currentAnimation->cropSprite();
		return true;
	}
	return false;
}


void SpriteManager::update(const sf::Time & timer)
{
	//m_currentAnimation->update(timer);
}

void SpriteManager::draw(const sf::RenderWindow & window)
{
	//window.draw(m_sprite);
}
