#include "Camera.h"

#include <iostream>

Camera::Camera(sf::Vector2f screenSize_, sf::Vector2f cameraPos_) {
	screenSize = screenSize_;
	cameraPos = cameraPos_;
	camera.reset(sf::FloatRect(0, 0, zoom*screenSize.x, zoom*screenSize.y));
}

void Camera::update(sf::Vector2f pos) {
	cameraPos = pos;
	int x = pos.x - zoom*screenSize.x/2;
	//int x = pos.x;

	if (x < 0) {
		cameraPos.x += -1 * x;
	}
	std::cout << cameraPos.x << std::endl;
	camera.setCenter(cameraPos.x, cameraPos.y);
}

sf::View& Camera::getView() {
	return Camera::camera;
}

Camera::~Camera() {}
