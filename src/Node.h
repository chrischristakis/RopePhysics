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
	const float gravity = 0.55f;
	const float bounce = 0.39f;
	const float friction = 0.995f;

public:

	Node(float x, float y, float velX, float velY, int radius);
	Node(float x, float y, float velX, float velY) : Node(x, y, velX, velY, 3) {};
	Node(float x, float y, int radius): Node(x,y,0,0,radius) {}
	Node(float x, float y): Node(x,y,0,0,3) {} //delegated constructor

	void draw();
	void update();
	void constrain();

	sf::Vector2f getPos() {
		return *pos;
	}

	void setPos(float x, float y) {
		pos->x = x;
		pos->y = y;
	}
};

#endif