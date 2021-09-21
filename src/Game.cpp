#include "Game.h"
#include "Node.h"
#include "Stick.h"
#include <vector>
#include <memory>

//Cant initialize it in the class
Game *Game::instance = nullptr;
sf::RenderWindow *Game::window = nullptr;
int Game::width = 0;
int Game::height = 0;

std::vector<std::shared_ptr<Node>> nodes;
std::vector<std::unique_ptr<Stick>> sticks;

void updateSticks() {
	for (int i = 0; i < sticks.size(); i++)
		sticks[i]->update();
}

void updateNodes() {
	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->update();
}

void constrainNodes() {
	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->constrain();
}

void Game::init(int w, int h, std::string title) {
	//If already initialized:
	if (window != nullptr) 
		return;

	width = w;
	height = h;

	window = new sf::RenderWindow(sf::VideoMode(w, h), title);
	window->setVerticalSyncEnabled(true);

	//nodes.emplace_back(std::make_shared<Node>(200, 200, 66, -66));
	//nodes.emplace_back(std::make_shared<Node>(290, 200, 0, 0));
	//nodes.emplace_back(std::make_shared<Node>(290, 290, 0, 0));
	//nodes.emplace_back(std::make_shared<Node>(200, 290, 0, 0));

	for (int i = 0; i < 10; i++)
	{
		float vx = (i == 4) ? 300 : 0;
		nodes.emplace_back(std::make_shared<Node>(500, 50 * i, vx, 0));
	}
	nodes[0]->setFrozen(true);

	for (int i = 0; i < 9; i++)
		sticks.emplace_back(std::make_unique<Stick>(nodes[i], nodes[i + 1]));
	
	//sticks.emplace_back(std::make_unique<Stick>(nodes[0], nodes[1]));
	//sticks.emplace_back(std::make_unique<Stick>(nodes[1], nodes[2]));
	//sticks.emplace_back(std::make_unique<Stick>(nodes[2], nodes[3]));
	//sticks.emplace_back(std::make_unique<Stick>(nodes[3], nodes[0]));
	//sticks.emplace_back(std::make_unique<Stick>(nodes[0], nodes[2]));
	//sticks.emplace_back(std::make_unique<Stick>(nodes[1], nodes[3]));

	sticks.emplace_back(std::make_unique<Stick>(nodes[0], nodes[1]));
	sticks.emplace_back(std::make_unique<Stick>(nodes[1], nodes[2]));
	sticks.emplace_back(std::make_unique<Stick>(nodes[2], nodes[3]));
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

	for (int i = 0; i < sticks.size(); i++)
		sticks[i]->draw();

	for (int i = 0; i < nodes.size(); i++)
		nodes[i]->draw();

	window->display();
}

void Game::update() {
	updateNodes();
	//We loop to fix the 'jelly' problem, it allows the points to adjust and correct themselves.
	for (int i = 0; i < 4; i++)
	{
		updateSticks();
		constrainNodes();
	}
}