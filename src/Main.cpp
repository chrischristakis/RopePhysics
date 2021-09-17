#include <SFML/Graphics.hpp>
#include "Node.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Rope physics");

	Node node(500, 500);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		node.update();

		window.clear(sf::Color(35,35,45,255));
		node.draw(&window);
		window.display();
	}

	return 0;
}