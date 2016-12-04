#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

# define M_PI           3.141592653589793

class Bullet
{
public:
	Bullet(sf::Vector2f pos_, double a, int color, sf::Texture &texture);
	~Bullet();

	void process(sf::RenderWindow& window, float time);

	int lifeTime = 100;

private:
	double radToDeg(long double a);

	std::map<int, std::string> colors{
		{ 0 , "data/images/Bullets/bulletBeige_outline.png" },
		{ 1 , "data/images/Bullets/bulletBlue_outline.png" },
		{ 2 , "data/images/Bullets/bulletGreen_outline.png" },
		{ 3 , "data/images/Bullets/bulletRed_outline.png" },
		{ 4 , "data/images/Bullets/bulletSilver_outline.png" },
		{ 5 , "data/images/Bullets/bulletYellow_outline.png" }
	};

	double angle;
	const float speed = 0.3;
	float curSpeed;
	const float speedLimit = 0.03;
	const float slip = 0.9;

	sf::Vector2f pos;
	sf::Vector2f vel;

	sf::Texture texture;
	sf::Sprite sprite;

	void draw(sf::RenderWindow &window);

};

#endif
