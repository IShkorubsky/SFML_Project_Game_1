#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine. 
	It will update and render the game.
	Wrapper class.
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeldDown;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void initializeVariables();
	void initializeWindow();
	void initializeFonts();
	void initializeText();
	void initializeEnemies();

public:
	//Constructor
	Game();

	//Destructor
	virtual ~Game();

	//Accessors
	const bool isRunning() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();	

	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};

