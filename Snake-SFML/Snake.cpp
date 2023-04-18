#include "Snake.h"

#pragma region Node
Node::Node(sf::Vector2f startCoords, sf::Color color)
{
	this->sprite = new sf::RectangleShape(sf::Vector2f(::CHUNK_SIZE, ::CHUNK_SIZE));
	this->sprite->setFillColor(color);
	//this->sprite->setOrigin(::CHUNK_SIZE / 2, ::CHUNK_SIZE / 2);
	this->sprite->setPosition(startCoords.x * ::CHUNK_SIZE, startCoords.y * ::CHUNK_SIZE);
	//this->sprite->setOutlineThickness(1);
	//this->sprite->setOutlineColor(sf::Color(250, 150, 100));
	SetCoords(startCoords);
}
Node::Node(sf::Vector2f coords, sf::Vector2f prevCoords, sf::Color color)
	: Node(coords, color)
{
	if (prevCoords.x >= 0 && prevCoords.y >= 0)
	{
		this->prevCoords = prevCoords;
	}
	else
		throw new std::exception("Error node constructor!");
}
Node::Node(const Node& node) :Node(node.coords, node.prevCoords, node.sprite->getFillColor()) {}

void Node::Draw(sf::RenderWindow* win)
{
	if (this->sprite != nullptr)
	{
		this->sprite->setPosition(this->coords.x * ::CHUNK_SIZE, this->coords.y * ::CHUNK_SIZE);
		win->draw(*this->sprite);
	}
	else
		throw new std::exception_ptr;
}

void Node::SetCoords(sf::Vector2f coords)
{
	if (coords.x >= 0 && coords.y >= 0 && coords.x <= ::FIELD_SIZE - 1 && coords.y <= ::FIELD_SIZE - 1)
	{
		this->prevCoords = this->coords;
		this->coords = coords;
	}
	else
		throw new Error(1, "Wrong coords value!");
}
sf::Vector2f Node::GetCoords() const
{
	return this->coords;
}
sf::Vector2f Node::GetPrevCoords() const
{
	return this->prevCoords;
}

Node::~Node()
{
	if (this->sprite != nullptr) delete this->sprite;
}
#pragma endregion

#pragma region Snake
Snake::Snake(sf::Vector2f startPoint, int startSize)
{
	if (startPoint.x > 0 && startPoint.y > 0 && startSize > 1)
	{
		Node head(startPoint, sf::Vector2f(startPoint.x - 1, startPoint.y), sf::Color::Red);
		this->nodes.push_back(head);
		for (size_t i = 1; i < startSize; i++)
		{
			AddNode();
		}
		this->dir = RIGHT;
		this->lastDir = RIGHT;
	}
	else
		throw new std::exception("Snake constructor error!");
}

void Snake::AddNode()
{
	sf::Vector2f coordsEndNode = this->nodes[GetSnakeSize() - 1].GetCoords();
	sf::Vector2f coordsNewNode = this->nodes[GetSnakeSize() - 1].GetPrevCoords();

	sf::Vector2f vect(coordsNewNode.x - coordsEndNode.x, coordsNewNode.y - coordsEndNode.y);

	sf::Vector2f prevCoordsNewNode(coordsNewNode.x + vect.x, coordsNewNode.y + vect.y);
	Node temp(coordsNewNode, prevCoordsNewNode, sf::Color::White);
	this->nodes.push_back(temp);
}

void Snake::Update(sf::Int32 time)
{
	static float stepTime;
	stepTime += time;
	if (stepTime > 100)
	{
		sf::Vector2f temp = this->nodes[0].GetCoords();
		switch (this->dir)
		{
		case UP:
			if (this->lastDir != DOWN)
			{
				--temp.y;
				this->lastDir = UP;
			}
			else
			{
				++temp.y;
				this->dir = DOWN;
			}
			break;
		case RIGHT:
			if (this->lastDir != LEFT)
			{
				++temp.x;
				this->lastDir = RIGHT;
			}
			else
			{
				this->dir = LEFT;
				--temp.x;
			}
			break;
		case DOWN:
			if (this->lastDir != UP)
			{
				++temp.y;
				this->lastDir = DOWN;
			}
			else
			{
				this->dir = UP;
				--temp.y;
			}
			break;
		case LEFT:
			if (this->lastDir != RIGHT)
			{
				--temp.x;
				this->lastDir = LEFT;
			}
			else
			{
				++temp.x;
				this->dir = RIGHT;
			}
			break;
		}
		this->nodes[0].SetCoords(temp);
		for (int i = 1; i < this->nodes.size(); i++)
		{
			this->nodes[i].SetCoords(this->nodes[i - 1].GetPrevCoords());
		}

		for (int i = 1; i < this->nodes.size(); i++)
		{
			if (temp.x == this->nodes[i].GetCoords().x && temp.y == this->nodes[i].GetCoords().y)
			{
				throw new Error(2, "Snake crossing!");
			}
		}

		stepTime = 0;
	}
}

void Snake::SetDirection(Direction dir)
{
	if (dir != Direction::NONE)
		this->dir = dir;
}

int Snake::GetSnakeSize() const
{
	return (int)this->nodes.size();
}
std::vector<Node>& Snake::GetObjects()
{
	return this->nodes;
}
#pragma endregion
