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

	

	// Player Sprite
	sf::Texture playerTexture;
	sf::Sprite playerSprite;

	float playerXSize;
	float playerYSize;

	// Player HUDs
	sf::RectangleShape hudBar;

	sf::Texture lifeTexture;
	sf::Sprite lifeSprite;

	float lifeXSize;
	float lifeYSize;

	// Projectile Variables
	Projectile* projectile;
	sf::Vector2f projectileSpawnLocation;

	std::vector<Projectile> projectiles;

	// Window bounds
	float leftBound;
	float rightBound;
	float topBound;
	float bottomBound;

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
	void initHUD();
	void initWindow(sf::RenderTarget* target);

	void playerMovement();
	void fireProjectile();

	void update();
	void render(sf::RenderTarget* target);
};

