#include "Node.h"
#include <iostream>
using namespace std;

Node::Node(float x, float y, int radius) {
	pos = new sf::Vector2f(x, y);
	node = new sf::CircleShape(radius);

	//So the node is drawn with it's origin at the center of the circle.
	node->setPosition(sf::Vector2f(pos->x-radius, pos->y-radius));
}

Node::~Node() {
	delete pos;
	delete node;
}

void Node::draw(sf::RenderWindow *window) {
	window->draw(*node);
}

void Node::update() {
	cout << pos->x << " : " << pos->y << endl;
}