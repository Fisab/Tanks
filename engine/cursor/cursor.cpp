#include "Cursor.h"

Cursor::Cursor(sf::String fileName) {

	texture.loadFromFile(fileName);
	texture.setSmooth(true);
	cursorSprite.setTexture(texture);

	//sizeCursor.x = texture.getSize().x;
	//sizeCursor.y = texture.getSize().y;

	//cursorSprite.setOrigin(sizeCursor.x / 2, sizeCursor.y / 2);
	//cursorSprite.setTextureRect(sf::IntRect(0, 0, sizeCursor.x, sizeCursor.y));
}

void Cursor::process(sf::RenderWindow& window, sf::Vector2f posMouse) {
	cursorSprite.setPosition(posMouse);
	draw(window);
}

void Cursor::draw(sf::RenderWindow& window) {
	window.draw(cursorSprite);
}
