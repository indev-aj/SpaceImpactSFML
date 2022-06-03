#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "Enemy.h"
#include "Boss.h"

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

	bool gameWon = false;
	bool inPlace = false;

	int toSpawnBoss;

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

	// Fonts
	sf::Font font;
	sf::Text scoreText;
	sf::Text endGameText;

	// Audio
	sf::SoundBuffer fireBuffer;
	sf::SoundBuffer damagedBuffer;
	sf::Sound fireSound;
	sf::Sound damagedSound;

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

	// Boss Variables
	Boss* boss;
	sf::Vector2f bossSpawnLocation;

	int movingTimer;
	int MAX_MOVING_TIMER;
	bool bossSpawned;
	bool once = false;
	bool hasEntered = false;
	bool changeDirection = false;

	std::string dir = "up";
	int moveCount = 0;

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

	void initBoss();
	void spawnBoss();

	void bulletOnHit();
	void enemyOnHit();

	void initSounds();
	void endGame();

	void bossUpdate();
	void update();
	void render(sf::RenderTarget* target);
};

