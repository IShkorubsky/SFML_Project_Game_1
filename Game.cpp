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

	this->window->setFramerateLimit(165);
}

void Game::initializeEnemies()
{
	this->enemy.setPosition(10.0f,10.0f);
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Yellow);
	this->enemy.setOutlineColor(sf::Color::Red);
	this->enemy.setOutlineThickness(4.0f);
}

//Constructor / Deconstructor
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeEnemies();
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

	//Update mouse position
	//Relative to the window
	std::cout << "Mouse position: " 
		<< sf::Mouse::getPosition(*this->window).x << " " 
		<< sf::Mouse::getPosition(*this->window).y << std::endl;
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
	this->window->clear();

	//Draw game objects
	this->window->draw(this->enemy);

	//Draw game objects
	this->window->display();
}
