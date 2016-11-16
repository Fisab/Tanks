#include "Player.h"


Player::Player(sf::Vector2f pos_)
{
	shape.setRadius(100);
	shape.setFillColor(sf::Color::Green);

	pos = pos_;
}


void Player::process() {
	Player::move();
}

void Player::move() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		pos.x -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		pos.x += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		pos.y -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		pos.y += speed;
	}
}

void Player::draw(sf::RenderWindow &window) {
	shape.setPosition(pos.x, pos.y);


}
