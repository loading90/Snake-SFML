#pragma once
#include "Object.h"
#include "Snake.h"
#include "Apple.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

class Game
{
	sf::RenderWindow* window;
	Snake* snake;
	Apple* apple;
public:
	Game();

	void Run();

	~Game();
};

