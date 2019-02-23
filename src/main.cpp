#include <iostream>
#include <armadillo>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}

		window.clear();
		window.display();
	}
}
