#include <SFML/Graphics.hpp>
#include "HUD.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mario");
	
	window.setFramerateLimit(60);
	HUD hud;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		hud.update(window);
		window.clear(sf::Color(76,199,255));
		hud.draw(window);
		window.display();
	}

	return 0;
}