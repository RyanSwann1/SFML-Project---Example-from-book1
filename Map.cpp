#include "Map.h"
#include "StateManager.h"
#include <math.h>

Map::Map(SharedContext* sharedContext, StateBase* stateBase) :
	m_sharedContext(sharedContext),
	m_defaultTile(sharedContext),
	m_maxMapSize(32, 32),
	m_tileCount(0),
	m_tileSetCount(0),
	m_mapGravity(512.f),
	m_loadNextMap(false),
	m_currentState(stateBase)
{
	m_sharedContext->m_gameMap = this;
	//loadTiles("tiles.cfg");
}


Map::~Map()
{
	purgeMap();
	purgeTileSet();
	m_sharedContext->m_gameMap = nullptr;
}

Tile * Map::getTile(unsigned int x, unsigned int y)
{
	auto tile = m_tileMap.find(convertCoords(x, y));
	return (tile != m_tileMap.end() ? tile->second : nullptr);
}

unsigned int Map::convertCoords(unsigned int x, unsigned int y)
{
	return (x * m_maxMapSize.x) + y;
}

void Map::loadTiles(const std::string & path)
{
	std::ifstream file;
	file.open(Utils::GetWorkingDirectory() + path);
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (line[0] == '|') { continue; }
			std::stringstream keyStream(line);
			int tileID;
			keyStream >> tileID;
			if (tileID < 0) { continue; }
			TileInfo* tile = new TileInfo(m_sharedContext, "TileSheet", tileID); //Create new tile
			keyStream >> tile->m_name >> tile->m_friction.x >> tile->m_friction.y >> tile->m_deadly; //Assign properties from file
			if (!m_tileSet.emplace(tileID, tile).second)
			{
				//Duplicate tile detected
				std::cerr << "Duplicate tile detected: " << tile->m_name << "\n";
				delete tile;
				tile = nullptr;
			}
		}
		file.close();
	}
}

void Map::purgeMap()
{
	m_tileCount = 0;
	for (auto &i : m_tileMap) {
		delete i.second;
	}
	m_tileMap.clear();
	//m_sharedContext->entity->purge();
	if (m_backgroundTexture != "")
	{
		m_sharedContext->m_textureManager->releaseResource(m_backgroundTexture);
		m_backgroundTexture = "";
	}
}

void Map::purgeTileSet()
{
	for (auto &i : m_tileSet) {
		delete i.second;
	}
	m_tileSet.clear();
	m_tileSetCount = 0;
}

void Map::update(const float timer)
{
	//If there is another map to load
	if (m_loadNextMap)
	{
		//Get rid of the current map
		purgeMap();
		m_loadNextMap = false;
		if (m_nextMap != "") {
			loadMap("media/maps/" + m_nextMap);
		}
		else {
			m_currentState->getStateManager()->switchTo(GameState::MainMenu);
		}
	}
	//Update current viewpoint of map
	else
	{
		//Set position for the maps background - view
		sf::FloatRect viewSpace = m_sharedContext->m_window->getViewSpace();
		m_background.setPosition(viewSpace.left, viewSpace.top);
	}
}

//Not sure whats going on here
void Map::draw()
{
	sf::RenderWindow* window = &m_sharedContext->m_window->getWindow();
	window->draw(m_background); //Draw the background 

	//Set the view to draw - Features culling
	sf::FloatRect viewSpace = m_sharedContext->m_window->getViewSpace();
	sf::Vector2i tileBegin(floor(viewSpace.left / m_tileSheet.m_tileSize), floor(viewSpace.top / m_tileSheet.m_tileSize));
	sf::Vector2i tileEnd((ceil(viewSpace.left + viewSpace.width) / m_tileSheet.m_tileSize), (ceil(viewSpace.top + viewSpace.height) / m_tileSheet.m_tileSize));

	//Draw in the few selected tiles from the map  that appear within the viewspace
	unsigned int count = 0;
	for (int x = tileBegin.x; x <= tileEnd.x; x++)
	{
		for (int y = tileBegin.y; y <= tileEnd.y; y++)
		{
			if (x < 0 || x < 0) { continue; }
			Tile* tile = getTile(x, y);
			if (!tile) { continue; }
			sf::Sprite* sprite = &tile->m_properties->m_sprite;
			sprite->setPosition(x * m_tileSheet.m_tileSize, y * m_tileSheet.m_tileSize);
			window->draw(*sprite);
			count++;
		}
	}
}
