#include "Map.h"


Map::Map()
{
	tex.loadFromFile("data/tiles.png");
	here.setTexture(tex);
	viewrect.width = 800;
	viewrect.height = 600;
	montex.loadFromFile("data/textures.png");
	
	shroom.loadFromFile("data/powerups.png");
	player = new Player();
	
}


Map::~Map()
{
}
void Map::setLevel(std::string level){
	clock.restart();
	this->clevel = level;
	if (player->isDead())
		player->restartLife();
	map.clear();
	backup.clear();
	monsters.clear();
	powerups.clear();
	player->restart();
	std::string line;
	std::ifstream myfile("maps/"+level);
	while (getline(myfile, line))
	{
		map.push_back(line);

	}
	myfile.close();
	

	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[i].size(); j++){
			if (map[i].at(j) == '<'){
				Monster mon(&montex, 0, false,j,i);
				monsters.push_back(mon);
				map[i][j] = ' ';
			}
			else if (map[i].at(j) == '>'){
				Monster mon(&montex, 0, true,j,i);
				monsters.push_back(mon);
				map[i][j] = ' ';
			}
		}
	}
	
}
std::string Map::getLevel(){
	return clevel;
}
void Map::update(sf::RenderWindow& win){
	time += clock.restart().asSeconds();
	int ret=player->update(sf::Keyboard(), (*this), win);
	if (ret == 1){
		hud->setState(WIN);
	}
	else if (ret == -1){
		hud->setState(LOSE);
	}

	for (int i = 0; i < monsters.size(); i++){
		bool died = monsters[i].update((*player), (*this));
		if (died)
			monsters.erase(monsters.begin() + i);
	}
	for (int i = 0; i < powerups.size(); i++){
		bool died = powerups[i].update((*player), (*this));
		if (died)
			powerups.erase(powerups.begin() + i);
	}
}
void Map::draw(sf::RenderWindow& win){
	viewrect.left = (*player).shape.getPosition().x - 400;
	viewrect.top = (*player).shape.getPosition().y - 300;
	

	for (int i = 0; i < map.size(); i++){
		for (int j = 0; j < map[i].size(); j++){
			if (map[i].at(j) != ' ' && map[i].at(j) !='d'){
				here.setPosition(j * 32, i * 32);
				switch (map[i].at(j)){
				case '1':{
					here.setTextureRect(sf::IntRect(0, 0, 16, 16));
					break;
				}
				case '2':{
					here.setTextureRect(sf::IntRect(85, 0, 16, 16));
					break;
				}
				case 'a':{
					here.setTextureRect(sf::IntRect(0, 34, 16, 16));
					break;
				}
				case 's':{
					here.setTextureRect(sf::IntRect(18, 34 ,15, 16));
					break;
				}
				case 'z':{
					here.setTextureRect(sf::IntRect(0, 51, 16, 16));
					break;
				}
				case 'x':{
					here.setTextureRect(sf::IntRect(18, 51, 15, 16));
					break;
				}
				case '?':{
					here.setTextureRect(sf::IntRect(0, 186, 16, 16));
					break;
				}
				case 'b':{
					here.setTextureRect(sf::IntRect(34,34,16,16));
					break;
				}
				case 'M':{
					here.setTextureRect(sf::IntRect(0, 186, 16, 16));
					break;
				}
				case 'i':{
					continue;
				}
				case 'e':{
					here.setTextureRect(sf::IntRect(102,0,16,16));
					break;
				}
				case 'A':{
					here.setTextureRect(sf::IntRect(0, 34, 16, 16));
					break;
				}
				case 'S' : {
					here.setTextureRect(sf::IntRect(18, 34, 15, 16));
					break;
				}
				case 'c':{
					here.setTextureRect(sf::IntRect(16, 186, 16, 16));
					break;
				}
				case 'q': {
					here.setTextureRect(sf::IntRect(0, 34, 16, 16));
					break;
				}
				case 'w': {
					here.setTextureRect(sf::IntRect(18, 34, 15, 16));
					break;
				}
				case '[': {
					here.setTextureRect(sf::IntRect(0, 34, 16, 16));
					break;
				}
				case ']': {
					here.setTextureRect(sf::IntRect(18, 34, 15, 16));
					break;
				}
				case '|':{
					here.setTextureRect(sf::IntRect(51, 170, 16, 16));
					break;
				}
				case '~':{
					here.setTextureRect(sf::IntRect(51, 51, 16, 16));
					break;
				}
				case '\'':{
					here.setTextureRect(sf::IntRect(34, 51, 16, 16));
					break;
				}
				}
				here.setScale(2, 2);
				if (viewrect.intersects(here.getGlobalBounds()))
					win.draw(here);
			}
		}
	}

	for (int i = 0; i < monsters.size(); i++){
		if (viewrect.intersects(monsters[i].shape.getGlobalBounds()))
			monsters[i].draw(win);
	}
	for (int i = 0; i < powerups.size(); i++){
		powerups[i].draw(win);
	}

	(*player).draw(win);
}
void Map::addPowerUp(int x, int y, int type){
	Powerup a(&shroom, x, y, type);
	powerups.push_back(a);
}
void Map::restart(){
	setLevel(clevel);
}
void Map::setHUD(HUD* hud){
	this->hud = hud;
}
sf::Vector2f Map::getPlayerPos(){
	return player->shape.getPosition();
}