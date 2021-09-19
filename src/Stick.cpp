#include "Stick.h"
#include "Game.h"
#include <iostream>

Stick::Stick(std::shared_ptr<Node> n1, std::shared_ptr<Node> n2) {
	this->n1 = n1;
	this->n2 = n2;

	float dx = n1->getPos().x - n2->getPos().x;
	float dy = n1->getPos().y - n2->getPos().y;
	length = sqrt(dx * dx + dy * dy);

	line = std::make_unique<sf::VertexArray>(sf::LinesStrip, 2);
	(*line)[0].position = n1->getPos();
	(*line)[1].position = n2->getPos();
	(*line)[0].color = sf::Color::Red;
	(*line)[1].color = sf::Color::Red;
}

void Stick::draw() {
	(*line)[0].position = n1->getPos();
	(*line)[1].position = n2->getPos();
	Game::getWindow()->draw(*line);
} 

void Stick::update() {
	//Current length of stick (Could be stretched)
	float dx = n1->getPos().x - n2->getPos().x;
	float dy = n1->getPos().y - n2->getPos().y;
	float newLength = sqrt(dx * dx + dy * dy);

	//Calculate the percent each node has to move in each axis
	// and store it as an offset of the current length along the stick.
	float diff = length - newLength;
	float percent = (diff / newLength) / 2; //div by 2 since its for each node.
	float offsetX = dx * percent;
	float offsetY = dy * percent;

	n1->setPos(n1->getPos().x + offsetX, n1->getPos().y + offsetY);
	n2->setPos(n2->getPos().x - offsetX, n2->getPos().y - offsetY);
}