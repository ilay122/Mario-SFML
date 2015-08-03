#include "FireBull.h"


FireBull::FireBull(int x, int y, sf::Texture* text,bool goingright)
{
	this->tex = text;
	shape.setTexture((*tex));
	shape.setPosition(x, y);
	this->goingright = goingright;
	shape.setTextureRect(sf::IntRect(310,320,16,16));
	shape.setScale(2, 2);
}


FireBull::~FireBull()
{
}
bool FireBull::update(Map& map){
	shape.move(Gravity);
	if (goingright)
		shape.move(BulletSpeed, 0);
	else
		shape.move(-BulletSpeed, 0);

	if (isjumping){
		shape.move(0, jumpingspeed);
		jumpingspeed++;
	}
	for (int i = 0; i < map.monsters.size(); i++){
		if (shape.getGlobalBounds().intersects(map.monsters[i].shape.getGlobalBounds())){
			map.monsters.erase(map.monsters.begin() + i);
			return true;
		}
	}

	sf::RectangleShape here;
	here.setSize(sf::Vector2f(32, 32));
	for (int i = 0; i < map.map.size(); i++){
		for (int j = 0; j < map.map[i].size(); j++){
			if (map.map[i].at(j) != ' '){
				here.setPosition(j * 32, i * 32);
				if (shape.getGlobalBounds().intersects(here.getGlobalBounds())){

					float player_bottom = shape.getPosition().y + shape.getGlobalBounds().height;
					float tiles_bottom = here.getPosition().y + here.getGlobalBounds().height;
					float player_right = shape.getPosition().x + shape.getGlobalBounds().width;
					float tiles_right = here.getPosition().x + here.getGlobalBounds().width;

					float b_collision = tiles_bottom - shape.getPosition().y;
					float t_collision = player_bottom - here.getPosition().y;
					float l_collision = player_right - here.getPosition().x;
					float r_collision = tiles_right - shape.getPosition().x;

					if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
					{
						isjumping = false;
						jump();
						//top collision
					}
					else{
						return true;
					}

					if (map.map[i].at(j) == 'd')
						return true;

				}

			}
		}
	}

	return false;
}
void FireBull::draw(sf::RenderWindow& win){
	win.draw(shape);
}
void FireBull::jump(){
	isjumping = true;
	jumpingspeed = -buljumph;
	shape.move(0, -10);
}