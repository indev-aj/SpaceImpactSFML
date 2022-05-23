#include "Projectile.h"

Projectile::Projectile(sf::Vector2f location)
{
	//std::cout << "Spawned at x: " << location.x << "\ty: " << location.y << std::endl;
	initVariables();
	initProjectile(location);
}

Projectile::~Projectile()
{
}

void Projectile::setSpeed(int speed = 10)
{
	this->speed = speed;
}

void Projectile::setDamage(int damage = 1)
{
	this->damage = damage;
}

void Projectile::initVariables()
{
	this->speed = 10;
	this->damage = 1;

	this->isDestroyed = false;
}

void Projectile::initProjectile(sf::Vector2f location)
{
	this->projectile.setSize(sf::Vector2f(10.f, 5.f));
	this->projectile.setFillColor(sf::Color::Red);
	this->projectile.setPosition(this->setSpawnLocation(location));
}

sf::Vector2f Projectile::setSpawnLocation(sf::Vector2f location)
{
	this->spawnLocation = location;
	return this->spawnLocation;
	//std::cout << "x: " << this->spawnLocation.x << "\ty: " << this->spawnLocation.y << std::endl;
}

sf::Vector2f Projectile::getLocation()
{
	return this->projectile.getPosition();
}

sf::RectangleShape Projectile::getProjectile()
{
	return this->projectile;
}

void Projectile::update()
{
	this->projectile.move(this->speed, 0.f);
}
