#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <memory>

class Node {
private:

	std::unique_ptr<sf::CircleShape> node;
	std::unique_ptr<sf::Vector2f> pos;
	std::unique_ptr<sf::Vector2f> oldPos;
	int radius;

public:

	Node(float x, float y, float velX, float velY, int radius);
	Node(float x, float y, float velX, float velY) : Node(x, y, velX, velY, 10) {};
	Node(float x, float y, int radius): Node(x,y,0,0,radius) {}
	Node(float x, float y): Node(x,y,0,0,5) {} //delegated constructor

	void draw();
	void update();
};

#endif