#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Projectile.h"

class Player
{
	int health;
	int score;
	bool died;
	bool fired;
	float firingTimer;
	float MAX_FIRING_TIMER;
	float movementSpeed;

	sf::Vector2f projectileSpawnLocation;

	sf::RectangleShape player;

	Projectile projectile;

public:
	Player();
	~Player();
	 
	void setHealth(int health);
	void setFiringTimer(float timer);
	void setProjectileSpawnLocation(sf::Vector2f location);

	sf::Vector2f getProjectileSpawnLocation();
	float getFiringTimer();
	int getHealth();
	int getScore();

	void initPlayer();

	void playerMovement();
	void fireProjectile();

	void update();
	void render(sf::RenderTarget* target);
};

