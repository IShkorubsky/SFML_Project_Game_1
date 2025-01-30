#include "Game.h"

//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
}

void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "My first SFML Game", sf::Style::Titlebar | sf::Style::Close);
}

//Constructor / Deconstructor
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::isRunning() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

//Functions
void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	/*
		@return void

		-Clear old frame
		-Render objects
		-Display frame in window

		Renders the game objects.
	*/

	//Clear frame
	this->window->clear(sf::Color::Red);

	//Draw game objects
	this->window->display();
}
