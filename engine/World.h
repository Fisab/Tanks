#ifndef WORLD_H
#define WORLD_H
#pragma comment(lib, "pugixmld.lib")

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class World
{
public:
	World();
	~World();

	int getWidthMap();
	int getHeightMap();

	bool loadMap(char* mapName);
	void drawMap(sf::RenderWindow&);

	struct Tileset {
		int firstGid;
		int tileCount;
		sf::Vector2f tileSize;

		sf::Texture texture;
	};

	struct Layer {
		int width, height;

		vector<int> layer;
	};

private:
	int MAP_HEIGHT;
	int MAP_WIDTH;

	int countTiles;

	vector<Tileset> tilesets;
	map<int, sf::Sprite> sprites;

	void setTextureTiles();

	vector<Layer> layers;

	int x, y;
};

#endif
