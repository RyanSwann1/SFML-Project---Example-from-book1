#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H
#include "Windoww.h"
#include "TextureManager.h"
#include "Map.h"
struct SharedContext
{
	SharedContext() :
		m_window(nullptr),
		m_textureManager(nullptr),
		m_gameMap(nullptr) {}

	
	Windoww* m_window;
	TextureManager* m_textureManager;
	Map* m_gameMap;
};
#endif // !SHARED_CONTEXT_H

