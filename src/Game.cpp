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

//For dragging a node with the mouse
std::shared_ptr<Node> selectedNode = nullptr;
bool rightHeld = false;

void updateSticks() {
	for (int i = 0; i < sticks.size(); i++)
		sticks[i]->update();
}

void updateNodes() {
	for (std::shared_ptr<Node> node : nodes) { 
		sf::Vector2i mpos = sf::Mouse::getPosition(*Game::getWindow()); //relative to window
		sf::Vector2f npos = node->getPos();

		//Distance from mouse to node
		float distance = sqrt((mpos.x - npos.x) * (mpos.x - npos.x) + (mpos.y - npos.y) * (mpos.y - npos.y));

		if (distance <= node->radius
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
			&& !selectedNode)
			selectedNode = node;

		//Toggle a frozen node
		if (distance <= node->radius
			&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
			if (!rightHeld) { //So it doesn't spasm until you release
				node->frozen = !node->frozen;
				rightHeld = true;
			}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
			rightHeld = false;

		//Unselect the node once we release the mouse
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && selectedNode) {
			selectedNode->selected = false;
			selectedNode = nullptr;
		}

		if (selectedNode) {
			selectedNode->selected = true;
			selectedNode->setPos(mpos.x, mpos.y);
			selectedNode->setOldPos(mpos.x, mpos.y); //to keep velocity = 0
		}

		node->update();
	}
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

	for (int i = 0; i < 14; i++)
		nodes.emplace_back(std::make_shared<Node>(500, 50 * i, 0, 0));
	nodes[0]->frozen = true;

	for (int i = 0; i < 13; i++)
		sticks.emplace_back(std::make_unique<Stick>(nodes[i], nodes[i + 1]));
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