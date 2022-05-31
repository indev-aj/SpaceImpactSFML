#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

using namespace std;

class Game
{
	Player player;
	//Projectile projectile;
	Enemy enemy;
	vector<Enemy> Enemies;
	vector<Boss> Bosses;

	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	string gameState;
	bool endGame;

	// Window bounds
	float leftBound;
	float rightBound;
	float topBound;
	float bottomBound;

	void initVariables();
	void initWindow();

public:
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;

	void pollEvents();

	void update();
	void render();
};