#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>


class Settings
{
public:
	Settings();
	~Settings();

	void getData(int &screenSizeX, int &screenSizeY, int &fps);

};

#endif
