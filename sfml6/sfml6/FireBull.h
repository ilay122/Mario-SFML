#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
const float BulletSpeed = 7.f;
const float buljumph = 10.f;
struct Map;
class FireBull
{
public:
	sf::Sprite shape;
	void draw(sf::RenderWindow& win);
	bool update(Map& map);
	FireBull(int x, int y, sf::Texture* tex, bool goingright);
	~FireBull();
private:
	void jump();
	sf::Texture* tex;
	bool isjumping;
	int jumpingspeed;
	bool goingright;
};

