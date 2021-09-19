#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include "Game.h"
using namespace std::chrono;

int main() {

	Game::init(1000, 1000, "Rope physics");

	long nsPerTick = 1e9 / 60;
	long delta = 0;
	high_resolution_clock::time_point last, now;
	last = high_resolution_clock::now();

	sf::sleep(sf::seconds(4));

	while (Game::getWindow()->isOpen()) {
		
		Game::getInstance().pollEvents();

		now = high_resolution_clock::now();
		auto nsDur = duration_cast<nanoseconds>(now - last).count();
		delta += duration<long>(nsDur).count();
		last = now;

		if (delta >= nsPerTick) {
			delta = 0;
			Game::getInstance().update();
		}

		Game::getInstance().draw();
	}

	return 0;
}