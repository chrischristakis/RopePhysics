#include "Node.h"
#include "Game.h"
#include <iostream>
using namespace std;

Node::Node(float x, float y, float velX, float velY, int radius) {
	pos = std::make_unique<sf::Vector2f>(x, y);
	oldPos = std::make_unique<sf::Vector2f>(x - velX, y - velY);
	
	node = std::make_unique<sf::CircleShape>(radius);
	//So the node is drawn with it's origin at the center of the circle.
	node->setPosition(sf::Vector2f(pos->x-radius, pos->y-radius));
}

void Node::draw() {
	Game::getWindow()->draw(*node);
}

void Node::update() {
	cout << pos->x << " : " << pos->y << endl;

	//Verlet integration
	float vx = pos->x - oldPos->x;
	float vy = pos->y - oldPos->y;

	oldPos->x = pos->x;
	oldPos->y = pos->y;

	pos->x += vx;
	pos->y += vy;

	node->setPosition(sf::Vector2f(pos->x - radius, pos->y - radius));
}