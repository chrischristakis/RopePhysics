#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <memory>

class Node {
private:

	std::unique_ptr<sf::CircleShape> node;
	std::unique_ptr<sf::Vector2f> pos;
	int radius;

public:

	Node(float x, float y, int radius);
	Node(float x, float y): Node(x,y,10) {} //delegated constructor

	void draw(sf::RenderWindow *window);
	void update();
};

#endif