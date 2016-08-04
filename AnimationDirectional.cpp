#include "AnimationDirectional.h"



void AnimationDirectional::frameStep()
{
	//Check in which direction we should roll the frames in
	if (m_frameStart < m_frameEnd) {
		m_currentFrame++;
	}
	else {
		m_currentFrame--;
	}

	//Then check if the frame is out of bounds
	if (m_frameStart < m_frameEnd && m_currentFrame > m_frameEnd ||
		m_frameStart > m_frameEnd && m_currentFrame < m_frameEnd)
	{
		//Check to see if looping
		if (m_loop) 
		{
			m_currentFrame = m_frameStart;
			return;
		}

		m_currentFrame = m_frameEnd;
		pause();
	}
}

void AnimationDirectional::cropSprite()
{	
	int a = 52;
	sf::FloatRect rect;
	rect.left = m_spriteManager->getSpriteSize().x * m_currentFrame; //Get position of the sprite on the x axis
	rect.top = m_spriteManager->getSpriteSize().y * (m_frameRow + (short)m_spriteManager->getDirection()); //Get position of the sprite on the y axis
	rect.width = m_spriteManager->getSpriteSize().x;
	rect.height = m_spriteManager->getSpriteSize().y;

	
}

void AnimationDirectional::readIn(const std::stringstream& stream)
{
	//unsigned int m_currentFrame;
	//unsigned int m_frameStart;
	//unsigned int m_frameEnd;
	//unsigned int m_frameRow;

	//int m_frameActionStart; //Frame When a specific action begins
	//int m_frameActionEnd; //Frame When a specific action ends

	//Responsible for reading in data from files
	//stream >> m_frameStart >> m_frameEnd >> m_frameRow >> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}
