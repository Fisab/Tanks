#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "World.h"

class Camera
{
public:
	Camera(sf::Vector2f, sf::Vector2f);
	~Camera();

	void update(sf::Vector2f pos);

	int moveWheel = 0;

	sf::Vector2f screenSize;
	sf::Vector2f cameraPos;
	sf::View &getView();

	float zoom = 1;

private:
	sf::View camera;
};

#endif
