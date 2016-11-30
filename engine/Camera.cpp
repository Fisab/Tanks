#include "Camera.h"

Camera::Camera(sf::Vector2f screenSize_, sf::Vector2f cameraPos_) {
	screenSize = screenSize_;
	cameraPos = cameraPos_;
	camera.reset(sf::FloatRect(0, 0, zoom*screenSize.x, zoom*screenSize.y));
}

void Camera::update(sf::Vector2f pos) {
	if (moveWheel == 1 && zoom < 1.5) {
		zoom += 0.05;
		camera.reset(sf::FloatRect(0, 0, zoom*screenSize.x, zoom*screenSize.y));
		moveWheel = 0;
	}
	else if (moveWheel == -1 && zoom > 0.5) {
		zoom -= 0.05;
		camera.reset(sf::FloatRect(0, 0, zoom*screenSize.x, zoom*screenSize.y));
		moveWheel = 0;
	}
	cameraPos = pos;
	camera.setCenter(cameraPos.x, cameraPos.y);
}

sf::View& Camera::getView() {
	return Camera::camera;
}

Camera::~Camera() {}
