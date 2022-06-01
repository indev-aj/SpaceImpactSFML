#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Boss
{
private:
	int health;
	int damage;
	int speed;

	sf::Vector2f spawnLocation;

	sf::Texture bossTexture;
	sf::Sprite bossSprite;

	float bossXSize;
	float bossYSize;

public:
	Boss();
	~Boss();

	void setHealth(int health);
	void setDamage(int damage);
	void setSpeed(int speed);
	void setSpawnLocation(sf::Vector2f spawnLocation);

	float getXSize();
	float getYSize();

	int getDamage();
	int getHealth();

	sf::Sprite getBoss();
	sf::Vector2f getCurrentPosition();

	void initBoss();

	void moveIn();
	void moveUp();
	void moveDown();
};

