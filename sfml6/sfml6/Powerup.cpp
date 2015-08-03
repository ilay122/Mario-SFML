#include "Powerup.h"


Powerup::Powerup(sf::Texture* textur, int x, int y, int type)
{
	tex = textur;
	shape.setTexture((*tex));
	shape.setPosition(x, y);
	goingRight = true;
	this->type = type;
	time = 0;
	if (type == 0){
		shape.setTextureRect(sf::IntRect(0,0,32,32));
	}
	else if (type == 1){
		shape.setTextureRect(sf::IntRect(36, 0, 32, 32));
	}
}


Powerup::~Powerup()
{
}
bool Powerup::update(Player& player,Map& map){
	if (type == 0){
		time += cl.restart().asMilliseconds();
		if (time <= 250){
			shape.move(0, -3);
		}
		else{
			if (goingRight){
				shape.move(powerUpSpeed, 0);
			}
			else{
				shape.move(-powerUpSpeed, 0);
			}
			shape.move(powerupGrav);
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
								shape.setPosition(shape.getPosition().x, here.getPosition().y - here.getGlobalBounds().height - 3);
								//top collision
							}
							if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
							{
								shape.setPosition(shape.getPosition().x, here.getPosition().y + here.getGlobalBounds().height);
								//bottom collision
							}
							if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
							{
								shape.setPosition(here.getPosition().x - shape.getGlobalBounds().width - 7, shape.getPosition().y);
								goingRight = false;
								//left collision
							}
							if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
							{
								shape.setPosition(here.getPosition().x + here.getGlobalBounds().width + 5, shape.getPosition().y);
								goingRight = true;

								//right collision
							}

							if (map.map[i].at(j) == 'd')
								return true;

						}

					}
				}
			}
			if (player.shape.getGlobalBounds().intersects(shape.getGlobalBounds())){
				player.getPowered();
				return true;
			}
		}
	}
	else if (type == 1){
		time += cl.restart().asMilliseconds();
		if (time <= 170){
			shape.move(0, -3);
		}
		else{
			if (player.shape.getGlobalBounds().intersects(shape.getGlobalBounds())){
				player.getPowered();
				return true;
			}
		}
	}
	return false;
}
void Powerup::draw(sf::RenderWindow& win){
	win.draw(shape);
}