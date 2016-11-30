#include "Settings.h"

Settings::Settings(){

}


Settings::~Settings(){}

void Settings::getData(int &screenSizeX, int &screenSizeY, int &fps) {
	std::ifstream settings("data/settings.conf");

	std::string lines;
	std::string buff;
	int index = 0;

	if (!settings)
		return;

	while (!settings.eof()) {
		getline(settings, buff, '\0');
		lines += buff;
	}
		
	settings.close();

	for (int i = 0; i < lines.length(); i++) {
		if (lines[i] == ';') {
			buff = lines.substr(index, i - index);
			std::size_t pos = buff.find(' ');

			if (buff.substr(0, pos) == "SCREEN_SIZE") {
				std::size_t pos1 = lines.find('x');
				screenSizeX = stoi(buff.substr(pos+1, pos1-pos-1));
				screenSizeY = stoi(buff.substr(pos1+1, buff.length()-pos1-1));
			}
			else if (buff.substr(0, pos) == "MAX_FPS") {
				fps = stoi(buff.substr(pos+1, buff.length()-pos-1));
			}

			index = i+2;
		}
	}
}

