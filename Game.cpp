#include "Game.h"

//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 25;
	this->enemySpawnTimerMax = 20.0f;
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

void Game::initializeFonts()
{
	if (this->font.loadFromFile("Fonts/Hello Cupcake.otf"))
	{
		std::cout << "ERROR::GAME::INITIALIZEFONTS::Failed to load font!" << std::endl;
	}
}

void Game::initializeText()
{
	this->uiText.setFont(this->font);
	this->uiText.setPosition(sf::Vector2f(10.f, -10.f));
	this->uiText.setCharacterSize(70);
	this->uiText.setScale(0.6f,0.6f);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setOutlineColor(sf::Color::Black);
	this->uiText.setOutlineThickness(3);
}

void Game::initializeEnemies()
{
	this->enemy.setPosition(10.0f,10.0f);
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Yellow);
	this->enemy.setOutlineColor(sf::Color::Black);
	this->enemy.setOutlineThickness(3.0f);
}

//Constructor / Deconstructor
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeFonts();
	this->initializeText();
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

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::spawnEnemy()
{
	/*
		Spawns enemies and sets their colors and positions.
			-Sets a random type.
			-Sets a random position.
			-Sets a random color.
			-Adds enemy to the vector.
	*/

	this->enemy.setPosition(
		(float)(rand() % (int)(this->window->getSize().x - this->enemy.getSize().x)),
		30.0f
	);

	//Randomize enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(30.0f, 30.0f));
		this->enemy.setFillColor(sf::Color::Red);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
		this->enemy.setFillColor(sf::Color::Magenta);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(70.0f, 70.0f));
		this->enemy.setFillColor(sf::Color::Yellow);
		break;
	case 3:
		this->enemy.setSize(sf::Vector2f(90.0f, 90.0f));
		this->enemy.setFillColor(sf::Color::Blue);
		break;
	case 4:
		this->enemy.setSize(sf::Vector2f(110.0f, 110.0f));
		this->enemy.setFillColor(sf::Color::Green);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(130.0f, 130.0f));
		this->enemy.setFillColor(sf::Color::White);
		break;
	}

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

void Game::updateText()
{
	std::stringstream ss;
	
	ss << "Points : " << this->points << "\n" 
		<< "Health : " << this->health << "\n";

	this->uiText.setString(ss.str());
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

		this->enemies[i].move(0.0f, 2.0f);

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
					//Add Points
					if (this->enemies[i].getFillColor() == sf::Color::Red)
					{
						this->points += 25;
					}
					else if(this->enemies[i].getFillColor() == sf::Color::Magenta)
					{
						this->points += 20;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
					{
						this->points += 15;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
					{
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
					{
						this->points += 5;
					}
					

					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
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

		this->updateText();

		this->updateEnemies();
	}

	//Endgame condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Renders the enemies.
	for (auto& e : this->enemies)
	{
		target.draw(e);
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
	this->window->clear(sf::Color::Cyan);

	//Draw game objects
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	//Draw game objects
	this->window->display();
}
