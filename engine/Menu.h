#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "cursor/Cursor.h"
#include "../Update.h"
#include <string>
#include <cstdlib>

class Menu {
public:
	Menu(sf::RenderWindow& window, sf::Vector2i& windowSize);

	void process();
	void draw();

private:
	sf::RenderWindow *menu_window;

	sf::Texture textureBG;
	sf::Sprite spriteBG;

	sf::Font font;
	sf::Text play, settings, exit;

	sf::Texture green_btn, green_prsd_btn, blue_btn, blue_prsd_btn, orange_btn, orange_prsd_btn, yellow_btn, yellow_prsd_btn, back_btn;
	sf::Sprite spr_green_btn, spr_blue_btn, spr_orange_btn, spr_yellow_btn, back;

	Cursor *cursor;
	sf::Vector2i size;

	sf::Text inp_window_size;

	bool homeB = true;
	bool settingsB = false;
};


#endif
