#ifndef MAP_H
#define MAP_H

#include "TextureManager.h"
#include "SharedContext.h"
#include "StateBase.h"
#include <SFML\Graphics.hpp>
#include <string>
#include <map>

//Size properties of the tile sheet - keep as const throughout runtime
struct TileSheet
{
	const unsigned int m_tileSize = 32;
	const unsigned int m_tileSheetWidth = 256;
	const unsigned int m_tileSheetHeight = 256;
};

struct TileInfo
{
	TileInfo(SharedContext* sharedContext,
		const std::string& texture = "", unsigned int ID = 0)
		: m_texture(texture), m_tileID(0), m_deadly(false)
	{
		TextureManager* textureManager = m_sharedContext->m_textureManager;
		if (texture == "") { m_tileID = ID; return; } //If Tile has no ID
		if (!textureManager->requireResource(texture)) { return; } //IF cannot locate the tile
		m_texture = texture;
		m_tileID = ID;
		m_sprite.setTexture(*textureManager->getResource(texture));
		//Set the tile boundary
		sf::IntRect tileBoundaries;
		tileBoundaries.left = m_tileID % (m_tileSheet.m_tileSheetHeight / m_tileSheet.m_tileSize) * m_tileSheet.m_tileSize;
		tileBoundaries.top = m_tileID / (m_tileSheet.m_tileSheetWidth / m_tileSheet.m_tileSize) * m_tileSheet.m_tileSize;
		tileBoundaries.height = m_tileSheet.m_tileSize;
		tileBoundaries.width = m_tileSheet.m_tileSize;
		m_sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo()
	{
		//Get rid of the used resource - if used
		if (m_texture != "") {
			//m_sharedContext->m_textureManager->removeResource(m_texture);
		}
	}

	sf::Sprite m_sprite;
	unsigned int m_tileID;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;

	TileSheet m_tileSheet;
	SharedContext* m_sharedContext;
	std::string m_texture;
};

struct Tile
{
	TileInfo* m_properties;
	bool m_warp; //Is the tile a warp?
	//Other flags unique to each tile
};

class Map
{
public:
	Map(SharedContext* sharedContext, StateBase* currentState);
	~Map();

	Tile* getTile(unsigned int x, unsigned int y);
	TileInfo* getDefaultTile();
	float getGravity() const;
	unsigned int getTileSize() const;
	sf::Vector2u& getMapSize() const;
	const sf::Vector2f& getPlayerStart() const;

	void loadMap(const std::string& path);
	void loadNext();
	void update(const float timer);
	void draw();

private:
	//Method for converting 2D coordinates to 1D units
	unsigned int convertCoords(unsigned int x, unsigned int y);
	void loadTiles(const std::string& path);
	void purgeMap();
	void purgeTileSet();

	std::map<unsigned int, TileInfo*> m_tileSet; //All of the different types of tiles that the map will use
	std::map<unsigned int, Tile*> m_tileMap; //Stores the map 

	sf::Sprite m_background;
	TileInfo m_defaultTile;
	TileSheet m_tileSheet;
	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	unsigned int m_tileCount; //How many tiles
	unsigned int m_tileSetCount; //How many unique tiles
	float m_mapGravity;
	std::string m_nextMap;
	bool m_loadNextMap;
	std::string m_backgroundTexture;
	StateBase* m_currentState;
	SharedContext* m_sharedContext;

};
#endif // !MAP_H
