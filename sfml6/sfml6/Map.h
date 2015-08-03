#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include "string"
#include <fstream>
#include <iostream>
#include "Player.h"
#include "Monster.h"
#include "Powerup.h"
#include "HUD.h"

struct Monster;
struct Powerup;
struct HUD;
class Map
{
public:
	std::vector<std::string> map;
	std::vector<std::string> backup;
	std::vector<Powerup> powerups;
	std::vector<Monster> monsters;
	sf::FloatRect viewrect;
	sf::Clock clock;

	void setLevel(std::string);
	void setHUD(HUD* hud);
	std::string getLevel();
	void restart();
	void draw(sf::RenderWindow& win);
	void update(sf::RenderWindow& win);
	void addPowerUp(int x, int y, int type);
	sf::Vector2f getPlayerPos();
	Map();
	~Map();
private:
	Player* player;
	std::string clevel;
	sf::Texture tex;
	sf::Sprite here;
	sf::Texture montex;
	sf::Texture shroom;
	HUD* hud;
	int time;
};

