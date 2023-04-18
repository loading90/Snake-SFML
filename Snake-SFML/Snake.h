#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <vector>
#include "Object.h"


#include <iostream>

using std::cout;
using std::endl;

typedef enum
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	NONE
} Direction;

class Node
{
	sf::RectangleShape* sprite;
	sf::Vector2f coords;
	sf::Vector2f prevCoords;
public:
	Node(sf::Vector2f startCoords, sf::Color color = sf::Color::White);
	Node(sf::Vector2f coords, sf::Vector2f prevCoords, sf::Color color = sf::Color::White);
	Node(const Node& node);

	void Draw(sf::RenderWindow* win);

	void SetCoords(sf::Vector2f coords);
	sf::Vector2f GetCoords() const;
	sf::Vector2f GetPrevCoords() const;

	~Node();
};
class Snake
{
public:
	std::vector<Node> nodes;
	Direction dir;
	Direction lastDir;
public:
	Snake(sf::Vector2f startPoint, int startSize);

	void AddNode();
	void Update(sf::Int32 time);

	void SetDirection(Direction dir);

	int GetSnakeSize() const;
	std::vector<Node>& GetObjects();
};

