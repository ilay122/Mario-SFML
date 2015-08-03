#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"
const float powerUpSpeed = 4.f;
const sf::Vector2f powerupGrav(0, 5.f);
class Powerup
{
public:
	sf::Sprite shape;
	Powerup(sf::Texture* textur,int x,int y, int type);
	bool update(Player& player,Map& map);
	void draw(sf::RenderWindow& win);
	~Powerup();
private:
	sf::Texture* tex;
	bool goingRight;
	int type;
	int time;
	sf::Clock cl;
};

