#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Player
{
public:

	Player(sf::Vector2f pos_);
	void process(sf::RenderWindow& window, float time, sf::Event *event);

	sf::Vector2f pos;
	sf::Vector2f vel;
	void draw(sf::RenderWindow &window);

private:
	const int startAngle = 90;
	float angle = 0;
	float towerAngle = 0;
	float curSpeed;

	void move(float time);
	//bool checkCollision();

	const float rotateSpeed = 0.03;
	const float rotateTowerSpeed = 0.06;
	const float speed = 2;
	const int speedLimit = 2;
	const float slip = 0.9;

	void makeTrail();
	float intervalTrail = 0;

	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	sf::Texture trailTexture;
	sf::Sprite trailSprite;

	sf::Texture towerTexture;
	sf::Sprite towerSprite;

	void rotateTower(sf::Vector2f posMouse, float time);

	struct trail
	{
		sf::Sprite spriteTrail;
		int opacity = 255;
	};

	sf::Vector2u trailSize;

	std::vector<trail> trails;

};

#endif
