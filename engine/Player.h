#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::Vector2f);
	void process();

	sf::Vector2f pos;
	sf::Vector2f vel;

private:
	void gravity();
	void move();
	void draw();
	bool checkCollision();

	const int speed = 10;
};

#endif
