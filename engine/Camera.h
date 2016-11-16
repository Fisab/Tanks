#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera(sf::Vector2f, sf::Vector2f);
	~Camera();

	//int screenSize[2];

	void update(sf::Vector2f);


	sf::Vector2f screenSize;
	sf::Vector2f cameraPos;
	sf::View & getView();

	float zoom = 1.5;

private:
	sf::View camera;
};

#endif
