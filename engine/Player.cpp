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
	trailSprite.setTextureRect(sf::IntRect(0, 0, trailSize.x, 15));//30
	trailSprite.setOrigin(trailTexture.getSize().x / 2, trailTexture.getSize().y / 2 - 15);
	trailSprite.setRotation(radToDeg(startAngle));
	trailSprite.setColor(sf::Color(169, 169, 169, 255));

	smokeTexture0.loadFromFile("data/images/Smoke/smokeGrey0.png");
	smokeTexture1.loadFromFile("data/images/Smoke/smokeGrey4.png");
	smokeTexture2.loadFromFile("data/images/Smoke/smokeGrey5.png");
	smokeTexture0.setSmooth(true);
	smokeTexture1.setSmooth(true);
	smokeTexture2.setSmooth(true);
	smokeSprite.setTexture(smokeTexture0);
	smokeSprite.setColor(sf::Color(217, 217, 217, 255));
	smokeSprite.setOrigin(smokeTexture0.getSize().x / 2, smokeTexture0.getSize().y / 2);
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
	//if (towerAngle > M_PI) towerAngle = -M_PI;
	//else if (towerAngle < -M_PI) towerAngle = M_PI;

	//if (angle > M_PI * 2) angle = 0;
	//else if (angle < 0) angle = M_PI * 2;

	rotateTower(window.mapPixelToCoords(sf::Mouse::getPosition(window)), time);
	Player::move(time);
	Player::bulletsProcess(window, time);
	Player::shoot(time);
	Player::processSmoke();
	Player::draw(window);
	pos.x += vel.x;
	pos.y += vel.y;
	
	vel.x *= slip;
	vel.y *= slip;

	intervalTrail += curSpeed;
	if (curSpeed != 0 && intervalTrail >= 7) {
		Player::makeTrail();
		intervalTrail = 0;
	}
	curSpeed = 0;
}

void Player::bulletsProcess(sf::RenderWindow& window, float time) {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->process(window, time);
	}
	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (bullets[i]->lifeTime <= 0) {
			bullets.erase(bullets.begin() + i);
		}
	}
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

void Player::shoot(float time) {
	if (time > 20 && shootTick > 0) shootTick -= 1;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTick == 0) {
		smokeSprite.setPosition(pos);
		smokes.push_back(smoke());
		smokes[smokes.size() - 1].sprite = smokeSprite;
		smokes[smokes.size() - 1].scale += 0.1;
		smokes[smokes.size() - 1].sprite.setScale(smokes[smokes.size() - 1].scale, smokes[smokes.size() - 1].scale);

		bullets.push_back(new Bullet(pos, towerAngle + angle, 2));

		shootTick = 20;
	}
}

void Player::rotateTower(sf::Vector2f posMouse, float time) {
	/*
	double needAngle = atan2(posMouse.y - pos.y, posMouse.x - pos.x);
	double a = fmod(towerAngle - needAngle - angle, M_PI * 2);

	int asign = getSign(a);
	a = abs(a);

	towerAngle -= getMin(rotateTowerSpeed, a) * (a > M_PI ? -asign : asign) * time;
	*/

	double needAngle = atan2(posMouse.y - pos.y, posMouse.x - pos.x);
	//double curAngle = towerAngle + angle;

	//if(needAngle > M_PI) needAngle -= M_PI*2;
	//if(needAngle < -M_PI) needAngle += M_PI*2;

	//std::cout << needAngle - curAngle << " " << needAngle << " " << curAngle << std::endl;

	//std::cout << curAngle << " " << needAngle << std::endl;

	//int dir = 0;

	//if (needAngle - curAngle < 0) dir = -1;
	//if (needAngle - curAngle > 0) dir = 1;

	//towerAngle += rotateTowerSpeed * time * dir;

	towerAngle = needAngle - angle;

	towerSprite.setRotation(radToDeg(angle + startAngle + towerAngle));
}

void Player::makeTrail(){
	trailSprite.setPosition(pos);
	trailSprite.setRotation(radToDeg(angle + startAngle));
	trails.push_back(trail());
	trails[trails.size() - 1].spriteTrail = trailSprite;

}

void Player::processSmoke() {
	for (int i = smokes.size() - 1; i >= 0; i--) {
		if (smokes[i].opacity <= 0 || smokes[i].scale > 1) {
			smokes.erase(smokes.begin() + i);
		}
		else if (smokes[i].opacity == 165) {
			smokes[i].sprite.setTexture(smokeTexture1);
			smokes[i].sprite.setScale(smokes[i].scale, smokes[i].scale);
			smokes[i].sprite.setTextureRect(sf::IntRect(0, 0, smokeTexture1.getSize().x, smokeTexture1.getSize().y));
			smokes[i].sprite.setOrigin(smokeTexture1.getSize().x / 2, smokeTexture1.getSize().y / 2);
		}
		else if (smokes[i].opacity == 85) {
			smokes[i].sprite.setTexture(smokeTexture2);
			smokes[i].sprite.setScale(smokes[i].scale, smokes[i].scale);
			smokes[i].sprite.setTextureRect(sf::IntRect(0, 0, smokeTexture2.getSize().x, smokeTexture2.getSize().y));
			smokes[i].sprite.setOrigin(smokeTexture2.getSize().x / 2, smokeTexture2.getSize().y / 2);
		}
	}
}

void Player::draw(sf::RenderWindow &window) {
	for (int i = 0; i < trails.size(); i++) {
		trails[i].spriteTrail.setColor(sf::Color(169, 169, 169, trails[i].opacity));
		trails[i].opacity--;
		window.draw(trails[i].spriteTrail);
	}

	for (int i = trails.size() - 1; i >= 0; i--) {
		if (trails[i].opacity == 0) {
			trails.erase(trails.begin() + i);
		}
	}

	playerSprite.setPosition(pos);
	towerSprite.setPosition(pos);

	window.draw(playerSprite);

	for (int i = 0; i < smokes.size(); i++) {
		smokes[i].sprite.setColor(sf::Color(169, 169, 169, smokes[i].opacity));
		smokes[i].opacity--;
		smokes[i].scale += 0.0025;
		smokes[i].sprite.setScale(smokes[i].scale, smokes[i].scale);
		window.draw(smokes[i].sprite);
	}


	window.draw(towerSprite);
}
