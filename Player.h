#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "Enemy.h"

class Player
{
private:

	// Player Variables
	int health;
	int score;
	bool died;
	bool fired;
	bool bulletOnHit;
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

	std::vector<sf::Sprite> lifes;

	float lifeXSize;
	float lifeYSize;

	// Projectile Variables
	Projectile* projectile;
	sf::Vector2f projectileSpawnLocation;
	std::vector<Projectile> projectiles;

	// Enemy Variables
	Enemy* enemy;
	sf::Vector2f enemySpawnLocation;
	std::vector<Enemy> enemies;

	int spawnTimer;
	int MAX_SPAWN_TIMER;
	bool spawned;

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

	bool getDied();

	void initPlayer();
	void initHUD(float top, float right, float bottom, float left);

	void playerMovement();
	void fireProjectile();

	void initEnemy();
	void spawnEnemy();

	void bulletOnHit();

	void update();
	void render(sf::RenderTarget* target);
};

