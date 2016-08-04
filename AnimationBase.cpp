#include "AnimationBase.h"



AnimationBase::AnimationBase() : m_currentFrame(0),
	m_frameStart(0),
	m_frameEnd(0),
	m_frameRow(0),
	m_frameTime(0.0f),
	m_elaspedTime(0.0f),
	m_frameActionStart(-1),
	m_frameActionEnd(-1),
	m_loop(false),
	m_playing(false)
{
}


AnimationBase::~AnimationBase()
{
}

void AnimationBase::reset()
{
	m_currentFrame = m_frameStart;
	m_elaspedTime = 0.0f;
	cropSprite();
}

void AnimationBase::setFrame(const unsigned int frame)
{
	if (frame >= m_frameStart && frame <= m_frameEnd &&
		frame >= m_frameEnd && frame <= m_frameStart) {
		m_currentFrame = frame;
	}
}

bool AnimationBase::isInAction()
{
	if (m_frameActionStart == -1 || m_frameActionEnd == -1) {
		return true;
	}

	return (m_currentFrame >= m_frameActionStart &&
		m_currentFrame <= m_frameActionEnd);
}

void AnimationBase::update(const float timer)
{
	if (!m_playing)
	{
		m_elaspedTime += timer;
		
		if (m_elaspedTime >= m_frameTime) 
		{
			frameStep();
			cropSprite();
			m_elaspedTime = 0;
		}
	}
}
