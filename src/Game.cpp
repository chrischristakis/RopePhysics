#include "Game.h"
#include "Node.h"

//Cant initialize it in the class
Game *Game::instance = nullptr;
sf::RenderWindow *Game::window = nullptr;

Node *node;

void Game::init() {
	//If already initialized:
	if (window != nullptr) 
		return;
	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Rope physics");

	node = new Node(500,500,2,2,20);
}

void Game::pollEvents() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::draw() {
	window->clear(sf::Color(30, 35, 45, 255));

	node->draw();

	window->display();
}

void Game::update() {
	node->update();
}