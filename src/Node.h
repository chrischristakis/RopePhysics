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
	bool frozen = false;
	const float gravity = 0.55f;
	const float bounce = 0.39f;
	const float friction = 0.995f;

public:

	Node(float x, float y, float velX, float velY, int radius);
	Node(float x, float y, float velX, float velY) : Node(x, y, velX, velY, 1) {};
	Node(float x, float y, int radius): Node(x,y,0,0,radius) {}
	Node(float x, float y): Node(x,y,0,0,1) {} //delegated constructor

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

	bool getFrozen() {
		return frozen;
	}

	void setFrozen(bool frozen) {
		this->frozen = frozen;
	}

	void setVel(float vx, float vy) {
		oldPos->x = pos->x - vx;
		oldPos->y = pos->x - vy;
	}
};

#endif