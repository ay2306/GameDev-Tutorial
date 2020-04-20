#include "Game.h"

void Game::spawnEnemies()
{
	/*
		Tasks:
		- Set Random Position
		- Set Random Color
		- Add Enemy to Enemies Vector
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
		);
	this->enemy.setFillColor(sf::Color::Green);
	this->enemies.push_back(this->enemy);
}

void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 100.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 480;
	this->window = new sf::RenderWindow(this->videoMode, "First Game", sf::Style::Default | sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(0.5f, 0.5f);
	this->enemy.setFillColor(sf::Color::Cyan); 
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(2.f);
}

Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game() {
	delete this->window;
}

const bool Game::isRunning() const
{
	if (this->window != nullptr)return this->window->isOpen();
	return false;
}


void Game::pollEvents()
{
	while (this->window->pollEvent(event)) {
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window);
}


void Game::updateEnemies()
{
	if ((int)enemies.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else this->enemySpawnTimer += 1;
	}
	
	for (auto& enemy : this->enemies) {
		if (enemy.getPosition().y + 5.f >= this->window->getSize().y)enemy.setPosition(enemy.getPosition().x, 0.f);
		enemy.move(0.f, 1.f);
	}
}

void Game::update()
{
	pollEvents();
	updateMousePositions();
}

void Game::renderEnemies()
{
	for (auto& enemy : this->enemies) {
		this->window->draw(enemy);
	}
}

void Game::render()
{
	this->window->clear();
	
	// Draw Game here
	this->updateEnemies();
	this->renderEnemies();

	this->window->display();
}
