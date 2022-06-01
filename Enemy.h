#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
	int health;
	int damage;
	int speed;

	sf::Vector2f spawnLocation;

	sf::Texture enemyTexture;
	sf::Sprite enemySprite;

	float enemyXSize;
	float enemyYSize;

public:
	Enemy();
	~Enemy();

	void setHealth(int health);
	void setDamage(int damage);
	void setSpeed(int speed);
	void setSpawnLocation(sf::Vector2f spawnLocation);

	float getXSize();
	float getYSize();

	int getDamage();
	int getHealth();
	int getSpeed();

	sf::Vector2f getLocation();
	sf::Sprite getEnemy();

	void initEnemy();

	void update();
};
