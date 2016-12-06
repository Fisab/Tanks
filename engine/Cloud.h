#ifndef CLOUD_H
#define CLOUD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Cloud
{
public:
	Cloud();
	~Cloud();

	void process(sf::RenderWindow& window, float time);

private:
	void spawnClouds();
	
	sf::Texture cloud0;
	sf::Texture cloud1;
	sf::Texture cloud2;

	sf::Sprite sprite;

	struct cloud {
		sf::Sprite sprite;
		int opacity = 255;
		double scale = 0.1;
	};

	std::vector<cloud> clouds;
};

#endif
