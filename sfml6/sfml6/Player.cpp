#include "Player.h"


Player::Player()
{
	goright = true;
	tex.loadFromFile("data/textures.png");
	shape.setTexture(tex);
	shape.setTextureRect(sf::IntRect(188, 0, 18, 18));
	shape.scale(1.7, 1.7);
	shape.setPosition(playerstartpos);
	isJumping = false;
	font.loadFromFile("data/Snowstorm.ttf");
	text.setFont(font);

	bigmario = false;
	firemario = false;
	lives = 3;
	jumpingspeed = 0;
	time = 0;
	cangethurt = true;


}


Player::~Player()
{
}

int Player::update(sf::Keyboard& key,Map& map,sf::RenderWindow& win){
	bool clicked = false;
	shape.move(Gravity);
	if (key.isKeyPressed(sf::Keyboard::Right)){
		shape.move(playerSpeed, 0);
		
		clicked = true;
		goright = true;
	}
	if (key.isKeyPressed(sf::Keyboard::Left)){
		shape.move(-playerSpeed, 0);
		
		clicked = true;
		goright = false;
	}
	if (key.isKeyPressed(sf::Keyboard::Z) && !zpressed){
		if (firemario){
			if (bullets.size() < 2){
				FireBull bul(shape.getPosition().x, shape.getPosition().y, &tex, goright);
				bullets.push_back(bul);
			}
		}
	}
	zpressed = key.isKeyPressed(sf::Keyboard::Z);
	if (!isJumping){
		if (key.isKeyPressed(sf::Keyboard::Space) && !spacepressed){
			isJumping = true;
			jumpingspeed = -jumpHeight;
			clicked = true;
			shape.move(0, -10);
		}
		
	}
	else{
		shape.move(0, jumpingspeed);
		jumpingspeed++;
	}
	spacepressed = key.isKeyPressed(sf::Keyboard::Space);
	

	if (firemario){
		if (goright){

		}
		else{

		}
	}
	else if (bigmario){
		if (goright){

		}
		else{

		}
	}
	else{
		if (goright){

		}
		else{

		}
	}

	sf::RectangleShape here;
	here.setSize(sf::Vector2f(32,32));
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
						isJumping = false; 
						isJumpingmini = false;
						if (bigmario || firemario){
							shape.setPosition(shape.getPosition().x, here.getPosition().y - here.getGlobalBounds().height-22);
							
						}
						else{
							shape.setPosition(shape.getPosition().x, here.getPosition().y - here.getGlobalBounds().height);
						}
						if (map.map[i].at(j) == 'A' || map.map[i].at(j) == 'S'){
							if (key.isKeyPressed(sf::Keyboard::Down)){
								for (int y = 0; y < map.map.size(); y++){
									for (int x = 0; x < map.map[y].size(); x++){
										if (map.map[y].at(x) == 'E'){
											shape.setPosition(x * 32, y * 32);
											break;
										}
									}
								}
							}
						}
						if (map.map[i].at(j) == '[' || map.map[i].at(j) == ']'){
							if (key.isKeyPressed(sf::Keyboard::Down)){
								for (int y = 0; y < map.map.size(); y++){
									for (int x = 0; x < map.map[y].size(); x++){
										if (map.map[y].at(x) == 'q'){
											shape.setPosition(x * 32, y * 32-55);
											break;
										}
									}
								}
							}
						}
						//top collision
					}
					
					if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
					{
						shape.setPosition(shape.getPosition().x, here.getPosition().y + here.getGlobalBounds().height +1);
						if (map.map[i].at(j) == 'M'){
							if (bigmario){
								map.addPowerUp(j * 32, i * 32, 1);
							}
							else{
								map.addPowerUp(j * 32, i * 32, 0);
							}
							map.map[i][j] = 'e';
						}
						if (map.map[i].at(j) == '?'){
							score += 100;
							isJumping = false;
							jumpingspeed = 0;
							map.map[i][j] = 'e';
						}
						if ((bigmario || firemario) && map.map[i].at(j) == '2'){
							map.map[i][j] = ' ';
							isJumping = false;
							jumpingspeed = 0;
						}
						//bottom collision
					}
					if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
					{
						shape.setPosition(here.getPosition().x - shape.getGlobalBounds().width, shape.getPosition().y);
						//left collision
					}
					if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
					{
						shape.setPosition(here.getPosition().x +here.getGlobalBounds().width+ 2, shape.getPosition().y);
						
						//right collision
					}
					
					if (map.map[i].at(j) == 'd'){
						restart();
						map.restart();
						lives--;
					}
					if (map.map[i].at(j) == 'c'){
						map.map[i][j] = ' ';
						score += 100;
					}
					if (map.map[i].at(j) == '|' || map.map[i].at(j) == '~' || map.map[i].at(j) == '\''){
						return 1;
					}
				}
				
			}
		}
	}
	if (firemario){
		for (int i = 0; i < bullets.size(); i++){
			bool died = bullets[i].update(map);
			if (died)
				bullets.erase(bullets.begin() + i);
		}
	}
	
	text.setString("Lives : "+std::to_string(lives));
	text.setPosition(shape.getPosition().x + 280, shape.getPosition().y - 370);
	sf::View view;
	view = win.getDefaultView();
	view.setCenter(shape.getPosition());
	view.move(0, -75);
	
	win.setView(view);
	
	if (isDead())
		return -1;
	return 0;
}
void Player::draw(sf::RenderWindow& win){
	win.draw(shape);
	for (int i = 0; i < bullets.size(); i++){
		bullets[i].draw(win);
	}
	win.draw(text);
}
bool Player::getHurt(Map& map){
	if (firemario){
		firemario = false;
		shape.setTextureRect(sf::IntRect(189, 56, 18, 31));
	}
	else if (bigmario){
		bigmario = false;
		shape.setTextureRect(sf::IntRect(188, 0, 18, 18));
	}
	else{
		map.restart();
		restart();
		lives--;
		return true;
	}
	return false;
}
void Player::minijump(){
	jumpingspeed = -jumpHeight;
	isJumping = true;
}
void Player::getPowered(){
	if (bigmario){
		shape.setTextureRect(sf::IntRect(190,125,18,31));
		firemario = true;
	}
	else{
		bigmario = true;
		shape.setTextureRect(sf::IntRect(189, 56, 18, 31));
	}
	shape.move(0, -20);
}
void Player::restart(){
	cangethurt = true;
	time = 0;
	shape.setTextureRect(sf::IntRect(188, 0, 18, 18));
	shape.setPosition(playerstartpos);
	firemario = false;
	bigmario = false;
	isJumping = false;
	goright = true;
}
bool Player::isjumping(){
	return isJumping;
}
bool Player::isDead(){
	return lives <= 0;
}
int Player::getScore(){
	return this->score;
}
void Player::restartLife(){
	this->lives = 3;
	
}