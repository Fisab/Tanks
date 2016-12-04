#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos_, double a, int color, sf::Texture &texture)
{
	pos = pos_;
	angle = a;

	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.setScale(0.5, 0.5);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setRotation(radToDeg(angle + M_PI / 2));
}

Bullet::~Bullet() {}

double Bullet::radToDeg(long double a) {
	return a * 180 / M_PI;
}

void Bullet::process(sf::RenderWindow& window, float time) {
	curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
	if (curSpeed < speedLimit) {
		vel.x += speed * cos(angle);
		vel.y += speed * sin(angle);
	}

	pos.x += vel.x * time;
	pos.y += vel.y * time;

	sprite.setPosition(pos);
	draw(window);

	lifeTime -= 1;
}

void Bullet::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}
