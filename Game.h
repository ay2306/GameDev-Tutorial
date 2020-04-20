#pragma once
#ifndef GAME_H
#include<iostream>
#include<vector>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#define GAME_H
/*
	Class that acts the game engine
	Wrapper Class
*/
class Game {
private: 
	/*
		Variables
	*/
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videoMode;
	sf::Vector2i mousePosition;
	// Enemies
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;
	/*
		Enemies Logic
	*/
	unsigned int points;
	unsigned int maxEnemies;
	float enemySpawnTimer;
	float enemySpawnTimerMax;

	/*
		Utility Methods
	*/
	void spawnEnemies();
	void initVariables();
	void initWindow();
	void initEnemies();
public:
	Game();
	virtual ~Game();
	// Accessors
	const bool isRunning()const;
	// Loops methods
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();

	void renderEnemies();
	void render();
};

#endif // !GAME_H