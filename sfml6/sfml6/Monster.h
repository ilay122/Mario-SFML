#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
const float MonsterSpeed = 4.f;
const sf::Vector2f monGravity(0, 3.7);
struct Player;
struct Map;

class Monster
{
public:
	sf::Sprite shape;
	bool active;
	sf::Texture* tex;
	int type;
	int state;
	bool movingRight;
	float gravitySpeed;
	float gravity;

	bool update(Player& player,Map& map);
	void draw(sf::RenderWindow& win);
	Monster(sf::Texture* texture,int type,bool moveright,int x,int y);
	~Monster();
protected:

};

