#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
	int health;
	int damage;
	int movementSpeed;
	float spawnTimer;
	float MAX_SPAWN_TIMER;
	bool spawned;
	sf::Vector2f spawnLocation;

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;

	float enemyXSize;
	float enemyYSize;

	int enemyCount;
	int maxEnemyCount;
	std::vector<sf::Sprite> enemies;

	// Window bounds
	float leftBound;
	float rightBound;
	float topBound;
	float bottomBound;

public:
	Enemy();
	~Enemy();

	void setSpawnTimer(float timer);
	void setHealth(int health);
	void setDamage(int damage);

	float getSpawnTimer();
	int getDamage();
	int getHealth();

	void enemyMovement();
	void spawnEnemy();
	void initEnemy();

	void update();
	void render(sf::RenderTarget* target);
};
