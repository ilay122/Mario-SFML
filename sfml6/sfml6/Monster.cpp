#include "Monster.h"


Monster::Monster(sf::Texture* texture,int type,bool moveright,int x,int y)
{
	state = 0;
	active = false;
	this->tex = texture;
	shape.setTexture((*tex));
	this->type = type;
	this->movingRight = moveright;
	if (!movingRight)
		shape.setTextureRect(sf::IntRect(7, 259, 16, 17));
	else
		shape.setTextureRect(sf::IntRect(37, 259, 16, 17));

	shape.setScale(1.55, 1.55);
	//shape.setScale(5, 5);
	shape.setPosition(x*32,y*32-1);
}


Monster::~Monster()
{
}
bool Monster::update(Player& player,Map& map){
	
	
	if (active && map.viewrect.intersects(shape.getGlobalBounds())){
		
		shape.move(monGravity);
		if (movingRight){
			shape.move(MonsterSpeed, 0);
		}
		else{
			shape.move(-MonsterSpeed, 0);
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
							shape.setPosition(shape.getPosition().x, here.getPosition().y - here.getGlobalBounds().height+5);
							//top collision
						}
						if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
						{
							shape.setPosition(shape.getPosition().x, here.getPosition().y + here.getGlobalBounds().height );
							//bottom collision
						}
						if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
						{
							shape.setTextureRect(sf::IntRect(7, 259, 16, 17));
							shape.setPosition(here.getPosition().x - shape.getGlobalBounds().width -7, shape.getPosition().y);
							movingRight = false;
							//left collision
						}
						if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
						{
							shape.setTextureRect(sf::IntRect(37, 259, 16, 17));
							shape.setPosition(here.getPosition().x + here.getGlobalBounds().width + 2, shape.getPosition().y);
							movingRight = true;
							
							//right collision
						}
						
						if (map.map[i].at(j) == 'd')
							return true;
						
					}

				}
			}
		}
		
		if (player.shape.getGlobalBounds().intersects(shape.getGlobalBounds())){
			float player_bottom = shape.getPosition().y + shape.getGlobalBounds().height;
			float tiles_bottom = player.shape.getPosition().y + player.shape.getGlobalBounds().height;
			float player_right = shape.getPosition().x + shape.getGlobalBounds().width;
			float tiles_right = player.shape.getPosition().x + player.shape.getGlobalBounds().width;

			float b_collision = tiles_bottom - shape.getPosition().y;
			float t_collision = player_bottom - player.shape.getPosition().y;
			float l_collision = player_right - player.shape.getPosition().x;
			float r_collision = tiles_right - shape.getPosition().x;

			
			
			if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
			{
				player.minijump();
				return true;
				
				//bottom collision
			}
			else{

				bool restarted=player.getHurt(map);
				if (!restarted)
					return true;
			}
			
		}

	}
	else{
		if (map.viewrect.contains(shape.getPosition())){
			active = true;
		}
	}
	
	return false;
	
}
void Monster::draw(sf::RenderWindow& win){
	if (active)
		win.draw(shape);
}