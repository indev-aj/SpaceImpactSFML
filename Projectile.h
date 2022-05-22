#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Projectile
{
private:
	int speed;
	int damage;
	bool isDestroyed;

	sf::Vector2f spawnLocation;

	sf::RectangleShape projectile;

	void initVariables();
	void initProjectile(sf::Vector2f location);

public:
	Projectile(sf::Vector2f location = {0,0});
	virtual ~Projectile();

	sf::Vector2f setSpawnLocation(sf::Vector2f spawnLocation);

	sf::Vector2f getLocation();

	sf::RectangleShape getProjectile();

	void update();
};

