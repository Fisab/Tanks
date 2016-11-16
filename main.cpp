
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "engine/World.h"
#include "engine/Player.h"
#include "engine/Camera.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	Player player1(sf::Vector2f(100,1));

	World *map = new World;
	map->loadMap("maps/vanilla.tmx");

	Camera camera(sf::Vector2f(1280, 780), sf::Vector2f(100, 100));

	sf::RenderWindow window(sf::VideoMode(camera.screenSize.x, camera.screenSize.y), "Fisab");
	window.setFramerateLimit(60);

	while (window.isOpen())	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		player1.process();
		camera.update(player1.pos);

		window.setView(camera.getView());
		window.clear(sf::Color(135, 206, 235));

		map->drawMap(window);

		window.display();
	}
	return 0;
}
