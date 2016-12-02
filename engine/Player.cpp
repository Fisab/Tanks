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
	playerSprite.setRotation(radToDeg(startAngle));

	towerTexture.loadFromFile("data/images/Tanks/barrelGreen_outline.png");
	towerTexture.setSmooth(true);
	towerSprite.setTexture(towerTexture);
	towerSprite.setOrigin(towerTexture.getSize().x / 2, towerTexture.getSize().y);
	towerSprite.setScale(0.5, 0.5);
	towerSprite.setPosition(pos);
	towerSprite.setRotation(radToDeg(startAngle));

	trailTexture.loadFromFile("data/images/Tanks/tracksLarge.png");
	trailTexture.setSmooth(true);
	trailSize = trailTexture.getSize();

	trailSprite.setPosition(pos);
	trailSprite.setScale(0.5, 0.5);
	trailSprite.setTexture(trailTexture);
	trailSprite.setTextureRect(sf::IntRect(0, 0, trailSize.x, 30));
	trailSprite.setOrigin(trailTexture.getSize().x / 2, trailTexture.getSize().y / 2 - 15);
	trailSprite.setRotation(radToDeg(startAngle));
	trailSprite.setColor(sf::Color(169, 169, 169, 255));
}

int Player::getSign(int a) {
	if (a < 0) return -1;
	else return 1;
}

long double Player::radToDeg(long double a) {
	return a * 180 / M_PI;
}

long double Player::abs(long double a) {
	if (a < 0) return a * -1;
	else return a;
}

long double Player::getMin(long double a, long double b) {
	if (a > b) return b;
	else return a;
}

void Player::process(sf::RenderWindow& window, float time, sf::Event *event) {
	//if (towerAngle > M_PI * 2) towerAngle = 0;
	//else if (towerAngle < 0) towerAngle = M_PI * 2;

	//if (angle > M_PI * 2) angle = 0;
	//else if (angle < 0) angle = M_PI * 2;

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
		playerSprite.setRotation(radToDeg(angle + startAngle));
		towerSprite.setRotation(radToDeg(angle + startAngle + towerAngle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += rotateSpeed * time;
		playerSprite.setRotation(radToDeg(angle + startAngle));
		towerSprite.setRotation(radToDeg(angle + startAngle + towerAngle));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
		if (curSpeed < speedLimit) {
			vel.x += speed * cos(angle);
			vel.y += speed * sin(angle);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		curSpeed = sqrt(vel.x*vel.x + vel.y*vel.y);
		if (curSpeed < speedLimit / 2) {
			vel.x -= speed / 3 * cos(angle);
			vel.y -= speed / 3 * sin(angle);
		}
	}
}

void Player::rotateTower(sf::Vector2f posMouse, float time) {
	double needAngle = atan2(posMouse.y - pos.y, posMouse.x - pos.x);

	double a = fmod(towerAngle - needAngle - angle, M_PI * 2);

	int asign = getSign(a);
	a = abs(a);

	towerAngle -= getMin(rotateTowerSpeed, a) * (a > M_PI ? -asign : asign);

	towerSprite.setRotation(radToDeg(angle + startAngle + towerAngle));
}

void Player::makeTrail(){
	trailSprite.setPosition(pos);
	trailSprite.setRotation(radToDeg(angle + startAngle));
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
