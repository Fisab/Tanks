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

	towerTexture.loadFromFile("data/images/Tanks/barrelGreen_outline.png");
	towerTexture.setSmooth(true);
	towerSprite.setTexture(towerTexture);
	towerSprite.setOrigin(towerTexture.getSize().x / 2, towerTexture.getSize().y);
	towerSprite.setScale(0.5, 0.5);
	towerSprite.setPosition(pos);
	towerSprite.setRotation(startAngle);

	trailTexture.loadFromFile("data/images/Tanks/tracksLarge.png");
	trailTexture.setSmooth(true);
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
	if (towerAngle > 360) towerAngle = 0;
	else if (towerAngle < 0) towerAngle = 360;

	if (angle > 360) angle = 0;
	else if (angle < 0) angle = 360;

	rotateTower(window.mapPixelToCoords(sf::Mouse::getPosition(window)), time);
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
		//towerSprite.setRotation(angle + startAngle + towerAngle);
		//towerAngle -= rotateSpeed * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += rotateSpeed * time;
		playerSprite.setRotation(angle + startAngle);
		//towerSprite.setRotation(angle + startAngle + towerAngle);
		//towerAngle += rotateSpeed * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
		if (curSpeed < speedLimit) {
			vel.x += speed * cos(angle / 180 * 3.14);
			vel.y += speed * sin(angle / 180 * 3.14);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
		if (curSpeed < speedLimit / 2) {
			vel.x -= speed / 3 * cos(angle / 180 * 3.14);
			vel.y -= speed / 3 * sin(angle / 180 * 3.14);
		}
	}
}

void Player::rotateTower(sf::Vector2f posMouse, float time) {
	//std::cout << angle << std::endl;
	double a1 = atan2(pos.y, pos.x);// -angle;
	double a2 = atan2(posMouse.y - pos.y, posMouse.x - pos.x);

	double a3 = a2 * 180 / 3.14 - towerAngle;

	if (a3 > 180) a3 -= 360;
	else if (a3 < -180) a3 += 360;

	int dir = 0;
	if (a3 - a1 > -1 && a3 - a1 < 1) return;
	if (a3 - a1 < 0) dir = -1;
	if (a3 - a1 > 0) dir = 1;

	towerAngle += rotateTowerSpeed * time * dir;

	towerSprite.setRotation(startAngle + towerAngle);
	//towerSprite.setRotation(angle + startAngle + towerAngle);
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
	towerSprite.setPosition(pos);
	window.draw(playerSprite);
	window.draw(towerSprite);
}
