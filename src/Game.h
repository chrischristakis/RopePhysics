#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

// --SINGLETON--
class Game {
private:
	//This needs to be in private and not delete since we need to call it from getInstance
	Game() {}

	static Game *instance;
	static sf::RenderWindow *window;

public:
	Game(Game &other) = delete;
	void operator=(const Game &other) = delete;

	static void init();

	void pollEvents();
	void draw();
	void update();

	static Game& getInstance() {
		if (instance == nullptr)
			instance = new Game();
		return *instance;
	}
	
	/*Not reference return since if this is called before initializing and
	reference is returned, we get exceptions.*/
	static sf::RenderWindow* getWindow() {
		return window;
	}

};

#endif
