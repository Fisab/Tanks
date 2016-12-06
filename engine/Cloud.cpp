#include "Cloud.h"



Cloud::Cloud()
{
	cloud0.loadFromFile("data/images/Clouds/cloud1.png");
	cloud1.loadFromFile("data/images/Clouds/cloud2.png");
	cloud2.loadFromFile("data/images/Clouds/cloud2.png");
}


Cloud::~Cloud()
{
}

void Cloud::process(sf::RenderWindow& window, float time) {

}

void Cloud::spawnClouds() {
	clouds.push_back(cloud());
	//clouds[clouds.size() - 1].sprite.setTexture();
}
