#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include "Map.h"
#include "FireBull.h"
const float playerSpeed = 8.f;
const sf::Vector2f Gravity(0,6.5);
const float jumpHeight = 25.f;
const sf::Vector2f playerstartpos(100,100);
struct Map;
struct FireBull;
class Player
{
public:
	int lives;
	sf::Clock clock;
	sf::Sprite shape;
	std::vector<FireBull> bullets;
	int update(sf::Keyboard&,Map& map,sf::RenderWindow& win);
	void draw(sf::RenderWindow& win);
	bool getHurt(Map& map);
	void minijump();
	void getPowered();
	void restart();
	bool isjumping();
	bool isDead();
	int getScore();
	void restartLife();
	Player();
	~Player();
private:
	int jumpingspeed;
	bool goright;
	bool isJumping;
	sf::Texture tex;
	sf::Font font;
	sf::Text text;

	int time;
	bool spacepressed;
	int score;

	bool cangethurt;
	bool bigmario;
	bool firemario;
	int jumpingspeed2;
	bool isJumpingmini;
	float gravity;
	float gravitySpeed;

	bool zpressed;
};

