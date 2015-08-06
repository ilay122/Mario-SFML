#include "HUD.h"



HUD::HUD()
{
	font.loadFromFile("data/Snowstorm.ttf");
	text1.setFont(font);
	text1.setCharacterSize(28);
	text1.setColor(sf::Color::Black);

	text2.setFont(font);
	text2.setCharacterSize(28);
	text2.setColor(sf::Color::Black);

	text3.setFont(font);
	text3.setCharacterSize(32);
	text3.setColor(sf::Color::Black);

	map = new Map();
	map->setHUD(this);
	getdir(files, "maps/");

	map->setLevel("map1.txt");
	currentState = MENU;
	

	menu.setFillColor(sf::Color::White);
	menu.setSize(sf::Vector2f(250, 350));
	menu.setOutlineColor(sf::Color::Black);
	
	head1.loadFromFile("data/marioheader1.jpg");
	header1.setTexture(head1);
	header1.setPosition(20,100);

	winpict.loadFromFile("data/mariowon.jpg");
	winpic.setTexture(winpict);

	losepict.loadFromFile("data/mariolost.jpg");
	losepic.setTexture(losepict);

	
}


HUD::~HUD()
{
}
void HUD::update(sf::RenderWindow& win){
	switch (currentState){
		case MENU:{
			text1.setPosition(370, 300);
			text2.setPosition(370, 400);
			text1.setString("Play");
			text2.setString("Exit");
			text1.setStyle(sf::Text::Regular);
			text2.setStyle(sf::Text::Regular);
			if ( !uppressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				currentHover--;
			}
			if (!downpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				currentHover++;
			}
			if (currentHover < 0)
				currentHover = 1;
			if (currentHover >= 2)
				currentHover = 0;


			if (currentHover == 0){
				text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			
			else if (currentHover == 1){
				text2.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}

			if (!enterpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if (currentHover == 1)
					win.close();
				if (currentHover == 0){
					setState(SUBPLAY);
				}
			}

			break;
		}
		case SUBPLAY:{
			text1.setPosition(370, 300);
			text2.setPosition(370, 400);
			text1.setStyle(sf::Text::Regular);
			text2.setStyle(sf::Text::Regular);
			text2.setString("Back");

			if (!uppressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				currentHover--;
			}
			if (!downpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				currentHover++;
			}
			if (currentHover < 0)
				currentHover = 1;
			if (currentHover >= 2)
				currentHover = 0;


			if (currentHover == 0){
				text1.setStyle(sf::Text::Underlined);
				if (!rightpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					chover++;
				}
				if (!leftpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					chover++;
				}

				if (chover < 0){
					chover = files.size() - 1;
				}
				if (chover >= files.size()){
					chover = 0;
				}
			}
			else if (currentHover == 1){
				text2.setStyle(sf::Text::Underlined);
			}
			if (!enterpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if (currentHover == 1){
					currentHover = 0;
					setState(MENU);
					map->restart();
				}
				else if (currentHover == 0){
					map->setLevel(files[chover]);
					setState(PLAY);
				}
			}
			text1.setString(files[chover]);
			break;
		}
		case PAUSE:{
			text1.setStyle(sf::Text::Regular);
			text2.setStyle(sf::Text::Regular);

			if (!uppressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				currentHover--;
			}
			if (!downpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				currentHover++;
			}
			if (currentHover < 0)
				currentHover = 1;
			if (currentHover >= 2)
				currentHover = 0;

			if (currentHover == 0){
				text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			else if (currentHover == 1){
				text2.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			if (!enterpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if (currentHover == 0){
					setState(PLAY);
				}
				else if (currentHover == 1){
					currentHover = 0;
					setState(SUBPLAY);
				}
			}

			text1.setString("Resume");
			text2.setString("Level Select");
			menu.setPosition(map->getPlayerPos().x - 100, map->getPlayerPos().y-250);
			text1.setPosition(menu.getPosition().x+20,menu.getPosition().y+20);
			text2.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 60);
			break;
		}
		
		case PLAY:{
			map->update(win);
			if (!escpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
				setState(PAUSE);
			}
			break;
		}
		case LOSE:{
			text3.setString("YOU HAVE LOST");
			text1.setStyle(sf::Text::Regular);
			text2.setStyle(sf::Text::Regular);
			text1.setString("Restart");
			text2.setString("Level Select");
			if (!uppressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				currentHover--;
			}
			if (!downpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				currentHover++;
			}
			if (currentHover < 0)
				currentHover = 1;
			if (currentHover >= 2)
				currentHover = 0;

			if (currentHover == 0){
				text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			else if (currentHover == 1){
				text2.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}

			if (!enterpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if (currentHover == 0){
					map->restart();
					setState(PLAY);
				}
				else if (currentHover == 1){
					currentHover = 0;
					setState(SUBPLAY);
				}
			}
			menu.setPosition(map->getPlayerPos().x - 100, map->getPlayerPos().y - 250);
			text1.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 20);
			text2.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 60);
			text3.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 190);
			losepic.setPosition(menu.getPosition().x - 25, menu.getPosition().y + 250);
			break;
		}
		case WIN:{
			text3.setString("YOU HAVE WON");
			text1.setStyle(sf::Text::Regular);
			text2.setStyle(sf::Text::Regular);
			text1.setString("Restart");
			text2.setString("Level Select");
			if (!uppressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				currentHover--;
			}
			if (!downpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				currentHover++;
			}
			if (currentHover < 0)
				currentHover = 1;
			if (currentHover >= 2)
				currentHover = 0;

			if (currentHover == 0){
				text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			else if (currentHover == 1){
				text2.setStyle(sf::Text::Bold | sf::Text::Underlined);
			}
			if (!enterpressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
				if (currentHover == 0){
					map->restart();
					setState(PLAY);
				}
				else if (currentHover == 1){
					currentHover = 0;
					setState(SUBPLAY);
				}
			}

			menu.setPosition(map->getPlayerPos().x - 100, map->getPlayerPos().y - 250);
			text1.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 20);
			text2.setPosition(menu.getPosition().x + 20, menu.getPosition().y + 60);
			text3.setPosition(menu.getPosition().x + 20, menu.getPosition().y - 60);
			winpic.setPosition(menu.getPosition().x +6, menu.getPosition().y + 250);
			
			break;
		}
	}
	escpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	enterpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
	rightpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	leftpressed=sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	uppressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	downpressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}
void HUD::draw(sf::RenderWindow& win){
	switch (currentState){
		case MENU:{
			win.setView(win.getDefaultView());
			win.draw(header1);
			win.draw(text1);
			win.draw(text2);
			break;
		}
		case SUBPLAY:{
			win.setView(win.getDefaultView());
			win.draw(header1);
			win.draw(text1);
			win.draw(text2);
			break;
		}
		case PAUSE:{
			map->draw(win);
			win.draw(menu);
			win.draw(text1);
			win.draw(text2);
			break;
		}
		
		case PLAY:{
			map->draw(win);
			break;
		}
		case LOSE:{
			win.draw(menu);
			win.draw(text1);
			win.draw(text2);
			win.draw(text3);
			win.draw(losepic);
			break;
		}
		case WIN:{
			win.draw(menu);
			win.draw(text1);
			win.draw(text2);
			win.draw(text3);
			win.draw(winpic);
			break;
		}
	}
}
void HUD::setState(int state){
	this->currentState = state;
}
void HUD::getdir(std::vector<std::string> &out, const std::string &directory){
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return; /* No files found */

	do {
		const std::string file_name = file_data.cFileName;
		
		const std::string full_file_name = directory + "/" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;
		if (file_name.size() < 5)
			continue;
		if (file_name.substr(file_name.size()-4) != ".txt")
			continue;
		if (is_directory)
			continue;

		out.push_back(file_data.cFileName);
	} while (FindNextFile(dir, &file_data));

	FindClose(dir);
	
}
