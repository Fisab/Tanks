#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, sf::Vector2i& windowSize)
{
	menu_window = &window;

	size.x = menu_window->getSize().x;
	size.y = menu_window->getSize().y;

	cursor = new Cursor("data/images/Cursor/cursor_pointer3D_shadow.png");

	yellow_btn.loadFromFile("data/images/Gui/yellow_btn.png");
	yellow_prsd_btn.loadFromFile("data/images/Gui/yellow_prsd_btn.png");
	green_btn.loadFromFile("data/images/Gui/green_btn.png");
	green_prsd_btn.loadFromFile("data/images/Gui/green_prsd_btn.png");
	blue_btn.loadFromFile("data/images/Gui/blue_btn.png");
	blue_prsd_btn.loadFromFile("data/images/Gui/blue_prsd_btn.png");
	orange_btn.loadFromFile("data/images/Gui/orange_btn.png");
	orange_prsd_btn.loadFromFile("data/images/Gui/orange_prsd_btn.png");
	back_btn.loadFromFile("data/images/Gui/back.png");

	yellow_btn.setSmooth(true);
	yellow_prsd_btn.setSmooth(true);
	green_btn.setSmooth(true);
	green_prsd_btn.setSmooth(true);
	blue_btn.setSmooth(true);
	blue_prsd_btn.setSmooth(true);
	orange_btn.setSmooth(true);
	orange_prsd_btn.setSmooth(true);
	back_btn.setSmooth(true);

	spr_green_btn.setTexture(green_btn);
	spr_blue_btn.setTexture(blue_btn);
	spr_orange_btn.setTexture(orange_btn);
	spr_yellow_btn.setTexture(yellow_btn);
	back.setTexture(back_btn);

	spr_green_btn.setOrigin(green_btn.getSize().x / 2, green_btn.getSize().y / 2);
	spr_blue_btn.setOrigin(blue_btn.getSize().x / 2, blue_btn.getSize().y / 2);
	spr_orange_btn.setOrigin(orange_btn.getSize().x / 2, orange_btn.getSize().y / 2);
	spr_yellow_btn.setOrigin(yellow_btn.getSize().x / 2, yellow_btn.getSize().y / 2);
	back.setOrigin(back_btn.getSize().x / 2, back_btn.getSize().y / 2);

	spr_green_btn.setPosition(size.x / 2, size.y / 4 + 100);
	spr_blue_btn.setPosition(size.x / 2, size.y / 4 + 180);
	spr_orange_btn.setPosition(size.x / 2, size.y / 4 + 260);
	spr_yellow_btn.setPosition(size.x - 50, size.y - 50);
	back.setPosition(50, size.y - 50);

	spr_green_btn.setScale(1.3, 1.3);
	spr_blue_btn.setScale(1.2, 1.2);

	font.loadFromFile("data/fonts/kenvector_future.ttf");

	play.setString("Play");
	settings.setString("Settings");
	exit.setString("Exit");

	play.setFont(font);
	settings.setFont(font);
	exit.setFont(font);

	play.setPosition(size.x / 2 - 50, size.y / 4 + 80);
	settings.setPosition(size.x / 2 - 90, size.y / 4 + 160);
	exit.setPosition(size.x / 2 - 40, size.y / 4 + 240);

	inp_window_size.setPosition(size.x/2-70, size.y/3);
	inp_window_size.setFont(font);
	inp_window_size.setString(std::to_string(windowSize.x)+" "+std::to_string(windowSize.y));
}

void Menu::process() {
	while (menu_window->isOpen()) {
		sf::Event event;
		while (menu_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				menu_window->close();
			//GREEN BTN
			if (homeB && spr_green_btn.getGlobalBounds().contains(menu_window->mapPixelToCoords(sf::Mouse::getPosition(*menu_window)))) {
				spr_green_btn.setTexture(green_prsd_btn);
				spr_green_btn.setTextureRect(sf::IntRect(0, 0, 190, 45));
				spr_green_btn.setPosition(size.x / 2, size.y / 4 + 105);
				play.setPosition(size.x / 2 - 50, size.y / 4 + 85);
				if (event.key.code == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					return;
				}
			}
			else if(homeB){
				play.setPosition(size.x / 2 - 50, size.y / 4 + 80);
				spr_green_btn.setTexture(green_btn);
				spr_green_btn.setTextureRect(sf::IntRect(0, 0, 190, 50));
				spr_green_btn.setPosition(size.x / 2, size.y / 4 + 100);
			}
			//BLUE BTN
			if (homeB && spr_blue_btn.getGlobalBounds().contains(menu_window->mapPixelToCoords(sf::Mouse::getPosition(*menu_window)))) {
				spr_blue_btn.setTexture(blue_prsd_btn);
				spr_blue_btn.setTextureRect(sf::IntRect(0, 0, 190, 45));
				spr_blue_btn.setPosition(size.x / 2, size.y / 4 + 185);
				settings.setPosition(size.x / 2 - 90, size.y / 4 + 165);
				if (event.key.code == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					homeB = false;
					settingsB = true;
				}
			}
			else if(homeB){
				spr_blue_btn.setPosition(size.x / 2, size.y / 4 + 180);
				spr_blue_btn.setTexture(blue_btn);
				settings.setPosition(size.x / 2 - 90, size.y / 4 + 160);
				spr_blue_btn.setTextureRect(sf::IntRect(0, 0, 190, 50));
			}
			//ORANGE BTN
			if (homeB && spr_orange_btn.getGlobalBounds().contains(menu_window->mapPixelToCoords(sf::Mouse::getPosition(*menu_window)))) {
				spr_orange_btn.setTexture(orange_prsd_btn);
				spr_orange_btn.setTextureRect(sf::IntRect(0, 0, 190, 45));
				spr_orange_btn.setPosition(size.x / 2, size.y / 4 + 265);
				exit.setPosition(size.x / 2 - 40, size.y / 4 + 245);
				if (event.key.code == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					menu_window->close();
				}
			}
			else if(homeB) {
				spr_orange_btn.setTexture(orange_btn);
				spr_orange_btn.setPosition(size.x / 2, size.y / 4 + 260);
				exit.setPosition(size.x / 2 - 40, size.y / 4 + 240);
				spr_orange_btn.setTextureRect(sf::IntRect(0, 0, 190, 50));
			}
			//YELLOW BTN
			if (spr_yellow_btn.getGlobalBounds().contains(menu_window->mapPixelToCoords(sf::Mouse::getPosition(*menu_window)))) {
				spr_yellow_btn.setTexture(yellow_prsd_btn);
				spr_yellow_btn.setTextureRect(sf::IntRect(0, 0, 49, 45));
				spr_yellow_btn.setPosition(size.x - 50, size.y - 45);
				if (event.key.code == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					Update *upd = new Update();
					upd->checkVersion();
					delete upd;
					//if (update) {
						//menu_window->close();
						//system("update.bat");
					//}
				}
			}
			else{
				spr_yellow_btn.setTexture(yellow_btn);
				spr_yellow_btn.setPosition(size.x - 50, size.y - 50);
				spr_yellow_btn.setTextureRect(sf::IntRect(0, 0, 49, 50));
			}
			//BACK BTN
			if (settingsB && back.getGlobalBounds().contains(menu_window->mapPixelToCoords(sf::Mouse::getPosition(*menu_window)))) {
				if (event.key.code == sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					homeB = true;
					settingsB = false;
				}
			}
			
		}

		draw();
	}
}

void Menu::draw() {
	menu_window->clear(sf::Color(119, 192, 200));
	if (homeB) {
		menu_window->draw(spr_green_btn);
		menu_window->draw(spr_blue_btn);
		menu_window->draw(spr_orange_btn);
		menu_window->draw(spr_yellow_btn);

		menu_window->draw(play);
		menu_window->draw(settings);
		menu_window->draw(exit);
	}
	else if (settingsB) {
		menu_window->draw(spr_yellow_btn);
		menu_window->draw(inp_window_size);
		menu_window->draw(back);
	}
	cursor->process(*menu_window, menu_window->mapPixelToCoords(sf::Mouse::getPosition(*menu_window)));

	menu_window->display();
}
