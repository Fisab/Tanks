#include "Player.h"

Player::Player(sf::Vector2f pos_)
{
	pos = pos_;
	playerTexture.loadFromFile("data/images/Tanks/tankGreen_outline.png");
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(pos);
	playerSprite.setScale(0.5, 0.5);
	playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
	playerSprite.setRotation(startAngle);

	trailTexture.loadFromFile("data/images/Tanks/tracksLarge.png");
	//trailTexture.setSmooth(true);
	trailSize = trailTexture.getSize();

	trailSprite.setPosition(pos);
	trailSprite.setScale(0.5, 0.5);
	trailSprite.setTexture(trailTexture);
	trailSprite.setTextureRect(sf::IntRect(0, 0, trailSize.x, 30));
	trailSprite.setOrigin(trailTexture.getSize().x / 2, trailTexture.getSize().y / 2 - 15);
	trailSprite.setRotation(startAngle);
	trailSprite.setColor(sf::Color(169, 169, 169, 255));
}


void Player::process(sf::RenderWindow& window, float time, sf::Event *event) {
	Player::move(time);
	Player::draw(window);
	pos.x += vel.x;
	pos.y += vel.y;
	
	vel.x *= slip;
	vel.y *= slip;

	intervalTrail += curSpeed;
	if (curSpeed != 0 && intervalTrail >= 14) {
		Player::makeTrail();
		intervalTrail = 0;
	}
	curSpeed = 0;
}

void Player::move(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= rotateSpeed * time;
		playerSprite.setRotation(angle + startAngle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += rotateSpeed * time;
		playerSprite.setRotation(angle + startAngle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
		if (curSpeed < speedLimit) {
			vel.x += speed * cos(angle/180 * 3.14);
			vel.y += speed * sin(angle/180 * 3.14);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
		if (curSpeed < speedLimit/2) {
			vel.x -= speed/3 * cos(angle/180 * 3.14);
			vel.y -= speed/3 * sin(angle/180 * 3.14);
		}
	}
}

void Player::makeTrail(){
	trailSprite.setPosition(pos);
	trailSprite.setRotation(angle + startAngle);
	trails.push_back(trail());
	trails[trails.size() - 1].spriteTrail = trailSprite;

}

void Player::draw(sf::RenderWindow &window) {
	for (int i = 0; i < trails.size(); i++) {
		trails[i].spriteTrail.setColor(sf::Color(169, 169, 169, trails[i].opacity));
		trails[i].opacity--;
		window.draw(trails[i].spriteTrail);
	}

	for (int i = trails.size()-1; i >= 0; i--) {
		if (trails[i].opacity == 0) {
			trails.erase(trails.begin() + i);
		}
	}

	playerSprite.setPosition(pos);
	window.draw(playerSprite);
}
