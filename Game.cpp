#include "Game.h"

//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.0f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeldDown = false;
}

void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "My first SFML Game", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initializeEnemies()
{
	this->enemy.setPosition(10.0f,10.0f);
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Yellow);
	this->enemy.setOutlineColor(sf::Color::Red);
	this->enemy.setOutlineThickness(3.0f);
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

//Functions
void Game::spawnEnemy()
{
	/*
		Spawns enemies and sets their colors and positions.
			-Sets a random position.
			-Sets a random color.
			-Adds enemy to the vector.
	*/

	this->enemy.setPosition(
		(float)(rand() % (int)(this->window->getSize().x - this->enemy.getSize().x)),
		30.0f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//Spawn the enemy
	this->enemies.push_back(this->enemy);

	//Remove enemies at the end of the screen
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

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	/*
		Updates the enemy spawn timer and spawns enemies when
		the total amount of enemies is smaller than the maximum.

		Moves the enemies.
		Removes the enemies at the edge of the screen.
	*/

	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.0f;
		}
		else
		{
			this->enemySpawnTimer += 1.0f;
		}
	}

	//Move the enemies
	for (int i = 0; i < this->enemies.size();i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.0f, 5.0f);

		//Check if enemy gets out of screen bounds
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			//Delete enemy
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeldDown == false) 
		{
			this->mouseHeldDown = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Add Points
					this->points += 5.0f;
					std::cout << "Current points:" << this->points << std::endl;
				}
			}
		}
	}
	else
	{
		this->mouseHeldDown = false;
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();

		this->updateEnemies();
	}
	else 
	{
		//Game Over
	}

}

void Game::renderEnemies()
{
	//Renders the enemies.
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	/*
		Renders the game objects.
			-Clear old frame
			-Render objects
			-Display frame in window
	*/

	//Clear frame
	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	//Draw game objects
	this->window->display();
}
