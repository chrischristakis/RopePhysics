#include "Game.h"
#include "Node.h"
#include <vector>

//Cant initialize it in the class
Game *Game::instance = nullptr;
sf::RenderWindow *Game::window = nullptr;
int Game::width = 0;
int Game::height = 0;

Node *node1;
Node *node2;
sf::VertexArray line(sf::LinesStrip, 2);

void Game::init(int w, int h, std::string title) {
	//If already initialized:
	if (window != nullptr) 
		return;

	width = w;
	height = h;

	window = new sf::RenderWindow(sf::VideoMode(w, h), title);
	window->setVerticalSyncEnabled(true);

	node1 = new Node(500, 530, 10, -35);
	node2 = new Node(230, 420, 44, -4);
	line[0].position = node1->getPos();
	line[1].position = node2->getPos();
	line[0].color = sf::Color::Red;
	line[1].color = sf::Color::Red;
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
	
	window->draw(line);
	node1->draw();
	node2->draw();

	window->display();
}

void Game::update() {
	node1->update();
	node2->update();
	line[0].position = node1->getPos();
	line[1].position = node2->getPos();
}