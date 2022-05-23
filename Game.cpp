#include "Game.h"


void Game::initVariables()
{
	this->window = nullptr;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Space Impact");
	this->window->setFramerateLimit(60);

	this->rightBound = this->window->getSize().x;
	this->leftBound = 0.f;
	this->topBound = 0.f;
	this->bottomBound = this->window->getSize().y;
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->player.initHUD(this->topBound, this->rightBound, this->bottomBound, this->leftBound);
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
	this->player.update();
}

void Game::render()
{
	
	this->window->clear(sf::Color(121, 174, 137));

	this->player.render(this->window);

	this->window->display();
}
