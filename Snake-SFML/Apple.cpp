#include "Apple.h"

Apple::Apple()
{
	this->sprite = new sf::RectangleShape(sf::Vector2f(10, 10));
	this->sprite->setFillColor(sf::Color::Green);
	this->sprite->setOrigin(-5, -5);
	NewCoords();
}

void Apple::NewCoords()
{
	srand(time(NULL));
	this->coords.x = rand() % (::FIELD_SIZE - 1);
	this->coords.y = rand() % (::FIELD_SIZE - 1);

	this->sprite->setPosition(this->coords.x * ::CHUNK_SIZE, this->coords.y * ::CHUNK_SIZE);
}
bool Apple::Update(std::vector<Node>& nodes, sf::RenderWindow * window)
{
	window->draw(*this->sprite);

	for (int i = 1; i < nodes.size(); i++)
	{
		if (this->coords.x == nodes[i].GetCoords().x && this->coords.y == nodes[i].GetCoords().y)
		{
			NewCoords();
			return true;
		}
	}

	return false;
}

Apple::~Apple()
{
	if (this->sprite != nullptr) delete this->sprite;
}
