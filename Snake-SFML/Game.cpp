#include "Game.h"

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(20 * ::CHUNK_SIZE, 20 * ::CHUNK_SIZE), "Snake");
	this->window->setVerticalSyncEnabled(true);
	this->snake = new Snake(sf::Vector2f(5,5), 4);
	this->apple = new Apple;
}

void Game::Run()
{
	std::vector<Node>& objects = this->snake->GetObjects();

	sf::Clock clock;
	sf::Int32 time;

	while (this->window->isOpen())
	{
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			// Кроме обычного способа наше окно будет закрываться по нажатию на Escape
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				this->window->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			this->snake->SetDirection(UP);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->snake->SetDirection(RIGHT);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			this->snake->SetDirection(DOWN);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->snake->SetDirection(LEFT);
		else
			this->snake->SetDirection(NONE);

		this->window->clear();

		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		try
		{
			this->snake->Update(time);
		}
		catch (Error* error)
		{
			if (error->code == 1) // Выход за пределы
			{
				cout << "Game over!" << endl;
			}
			if (error->code == 2) // Выход за пределы
			{
				cout << "Game over crossing!" << endl;
			}
		}

		if (this->apple->Update(objects, this->window))
		{
			this->snake->AddNode();
		}

		for (int i = 0; i < objects.size(); i++)
		{
			this->snake->nodes[i].Draw(this->window);
		}

		this->window->display();

	}
}

Game::~Game()
{
	if (this->snake != nullptr) delete this->snake;
	if (this->window != nullptr) delete this->window;
}
