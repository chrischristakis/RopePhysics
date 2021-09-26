#include "Node.h"
#include "Game.h"
#include <iostream>
using namespace std;

Node::Node(float x, float y, float velX, float velY, int radius) {
	this->radius = radius;

	pos = std::make_unique<sf::Vector2f>(x, y);
	oldPos = std::make_unique<sf::Vector2f>(x - velX, y - velY);
	
	node = std::make_unique<sf::CircleShape>(radius);
	//So the node is drawn with it's origin at the center of the circle.
	node->setPosition(sf::Vector2f(pos->x-radius, pos->y-radius));
}

void Node::draw() {
	node->setPosition(sf::Vector2f(pos->x - radius, pos->y - radius));
	node->setFillColor((frozen)? sf::Color::Cyan : sf::Color::White);
	Game::getWindow()->draw(*node);
}

void Node::update() {
	//Verlet integration 
	if(!frozen && !selected) {
		float vx = (pos->x - oldPos->x) * friction;
		float vy = (pos->y - oldPos->y) * friction;

		oldPos->x = pos->x;
		oldPos->y = pos->y;

		pos->x += vx;
		pos->y += vy + gravity;
	}
}

//Keep the nodes in the window
void  Node::constrain() {
	if (!frozen && !selected) {
		float vx = (pos->x - oldPos->x) * friction;
		float vy = (pos->y - oldPos->y) * friction;

		if (pos->x > Game::getWidth()) {
			pos->x = Game::getWidth();
			oldPos->x = pos->x + vx * bounce;
		}
		if (pos->x < 0) {
			pos->x = 0;
			oldPos->x = pos->x + vx * bounce;
		}
		if (pos->y > Game::getHeight()) {
			pos->y = Game::getHeight();
			oldPos->y = pos->y + vy * bounce;
		}
		if (pos->y < 0) {
			pos->y = 0;
			oldPos->y = pos->y + vy * bounce;
		}
	}
}