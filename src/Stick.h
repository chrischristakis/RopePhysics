#ifndef STICK_H
#define STICK_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Node.h"

class Stick {
private:

	float length;
	std::shared_ptr<Node> n1;
	std::shared_ptr<Node> n2;
	std::unique_ptr<sf::VertexArray> line;

public:

	Stick(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2);

	void draw();
	void update();

};

#endif
