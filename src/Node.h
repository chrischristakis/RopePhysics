#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>

class Node {
private:

	sf::CircleShape *node;
	sf::Vector2f *pos;
	int radius;

public:

	Node(float x, float y, int radius);
	Node(float x, float y): Node(x,y,10) {} //delegated constructor
	~Node();

	void draw(sf::RenderWindow *window);
	void update();
};

#endif