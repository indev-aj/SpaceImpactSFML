#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Projectile.h"

class Player
{
private:

	// Player Variables
	int health;
	int score;
	bool died;
	bool fired;
	float firingTimer;
	float MAX_FIRING_TIMER;
	float movementSpeed;

	sf::RectangleShape player;

	// Projectile Variables
	Projectile* projectile;
	sf::Vector2f projectileSpawnLocation;

	std::vector<Projectile> projectiles;

public:
	Player();
	~Player();
	 
	void setHealth(int health);
	void setFiringTimer(float timer);
	void setProjectileSpawnLocation();

	float getFiringTimer();
	int getHealth();
	int getScore();

	void initPlayer();

	void playerMovement();
	void fireProjectile();

	void update();
	void render(sf::RenderTarget* target);
};

