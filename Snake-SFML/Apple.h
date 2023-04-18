#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Snake.h"
#include "Object.h"

#include <iostream>

using std::cout;
using std::endl;

class Apple
{
	sf::RectangleShape* sprite;
	sf::Vector2f coords;

	void NewCoords();
public:
	Apple();
	
	bool Update(std::vector<Node>& nodes, sf::RenderWindow* window);

	~Apple();
};

