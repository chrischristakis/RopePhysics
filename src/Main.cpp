#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include "Node.h"
using namespace std::chrono;

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Rope physics");

	Node node(500, 500, 1, 1);

	long nsPerTick = 1e9 / 60;
	long delta = 0;
	high_resolution_clock::time_point last, now;
	last = high_resolution_clock::now();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		now = high_resolution_clock::now();
		auto nsDur = duration_cast<nanoseconds>(now - last).count();
		delta += duration<long>(nsDur).count();
		last = now;

		if (delta >= nsPerTick) {
			delta = 0;
			node.update();
		}

		window.clear(sf::Color(30,35,45,255));
		node.draw(&window);
		window.display();
	}

	return 0;
}