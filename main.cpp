#include <SFML/Graphics.hpp>
#include "engine/World.h"
#include "engine/Player.h"
#include "engine/cursor/Cursor.h"
#include "engine/Menu.h"
#include "engine/Settings.h"
#include "engine/Camera.h"

#include <iostream>

int main(int argc, char *argv[])
{
	int screenSize[] = { 640, 640 };
	int fps = 60;

	sf::Clock clock;

	Settings *settings = new Settings;
	settings->getData(screenSize[0], screenSize[1], fps);
	delete settings;

	sf::RenderWindow window(sf::VideoMode(screenSize[0], screenSize[1]), "Tanks");
	window.setActive(true);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(fps);

	Menu *menu = new Menu(window, sf::Vector2i(screenSize[0], screenSize[1]));
	menu->process();
	delete menu;

	World *map = new World;
	map->loadMap("data/maps/test.tmx");
	
	Camera camera(sf::Vector2f(screenSize[0], screenSize[1]), sf::Vector2f(100, 100));

	Cursor cursor("data/images/Cursor/cursor_pointer3D_shadow.png");

	Player tank(sf::Vector2f(100, 100));

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseWheelMoved) {
				camera.moveWheel = event.mouseWheel.delta;
			}
		}

		camera.update(tank.pos);
		window.setView(camera.getView());

		window.clear(sf::Color(119, 192, 200));

		map->drawMap(window);

		tank.process(window, time, &event);
		cursor.process(window, window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		window.display();
	}

	return 0;
}
