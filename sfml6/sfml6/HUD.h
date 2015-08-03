#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include <Windows.h>
#include<stdio.h>
static const int MENU = 0;
static const int PAUSE = 5;
static const int SUBPLAY = 1;
static const int PLAY = 10;
static const int LOSE = -1;
static const int WIN = 99;

class HUD
{
public:
	void update(sf::RenderWindow& win);
	void draw(sf::RenderWindow& win);
	void setState(int state);
	void getdir(std::vector<std::string> &out, const std::string &directory);
	HUD();
	~HUD();

	std::vector<std::string> files;
private:
	bool enterpressed;
	bool escpressed;
	bool rightpressed;
	bool leftpressed;
	bool uppressed;
	bool downpressed;

	Map* map;
	sf::Font font;
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
	sf::RectangleShape menu;
	sf::Sprite header1;
	sf::Texture head1;

	sf::Sprite winpic;
	sf::Texture winpict;
	sf::Sprite losepic;
	sf::Texture losepict;

	int currentState;
	int currentHover;
	int chover;
};

