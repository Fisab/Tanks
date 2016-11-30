#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Graphics.hpp>

class Cursor {
public:
	Cursor(sf::String fileName);

	void process(sf::RenderWindow& window, sf::Vector2f posMouse);

private:
	//sf::Vector2i sizeCursor;

	sf::Texture texture;
	sf::Sprite cursorSprite;

	void draw(sf::RenderWindow& window);

};

#endif
