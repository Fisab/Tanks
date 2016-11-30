#ifndef WORLD_H
#define WORLD_H
#pragma comment(lib, "pugixml.lib")

#include "pugixml.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>

#include <iostream>

using std::string;
using std::vector;
using std::map;

class World
{
public:
	World();
	~World();

	int MAP_HEIGHT;
	int MAP_WIDTH;

	bool loadMap(char* mapName);
	void drawMap(sf::RenderWindow &window);

	struct Tileset {
		int firstGid;
		int tileCount;
		sf::Vector2f tileSize;

		sf::Texture texture;
	};

	struct Layer {
		int width, height;
		string name;

		vector<int> layer;
	};

private:

	int countTiles;

	vector<Tileset> tilesets;
	map<int, sf::Sprite> sprites;

	void setTextureTiles();

	vector<Layer> layers;

	int cellsLimit = 10;
	void drawLimitScreen(sf::RenderWindow &window);
};

#endif
