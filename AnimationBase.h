#ifndef ANIMATION_BASE_H
#define ANIMATION_BASE_H

#include "SpriteManager.h"
#include <SFML\Graphics.hpp>
class AnimationBase
{
	friend class SpriteManager;
public:
	AnimationBase();
	virtual ~AnimationBase();

	void play() { m_playing = true; }
	void pause() { m_playing = false; }
	void stop() { m_playing = false; reset(); }
	void reset();

	void setSpriteManager(SpriteManager* spriteManager) { m_spriteManager = spriteManager; }
	void setFrame(const unsigned int frame);
	void setName(const std::string& name) { m_name = name; }
	bool isInAction();
	
	virtual void update(const float timer);

	//To make it easier to load in animations from files
	friend std::stringstream& operator >> (std::stringstream& stream, AnimationBase& animationBase)
	{
		animationBase.readIn(stream);
		return stream;
	}

protected:
	virtual void frameStep() = 0;
	virtual void cropSprite() = 0;
	virtual void readIn(const std::stringstream& stream) = 0;

	unsigned int m_currentFrame;
	unsigned int m_frameStart;
	unsigned int m_frameEnd;
	unsigned int m_frameRow;

	int m_frameActionStart; //Frame When a specific action begins
	int m_frameActionEnd; //Frame When a specific action ends

	float m_frameTime;
	float m_elaspedTime;
	bool m_loop;
	bool m_playing;
	std::string m_name;
	SpriteManager* m_spriteManager;

private:

};
#endif // !ANIMATION_BASE_H