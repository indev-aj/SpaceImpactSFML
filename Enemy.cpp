#include "Enemy.h"

Enemy::Enemy()
{
	initEnemy();
}

Enemy::~Enemy()
{
	
}

void Enemy::setHealth(int health)
{
	this->health = health;
}

void Enemy::setDamage(int damage)
{
	this->damage = damage;
}

void Enemy::setSpeed(int speed)
{
	this->speed = speed;
}

int Enemy::getDamage()
{
	return this->damage;
}

int Enemy::getHealth()
{
	return this->health;
}

int Enemy::getSpeed()
{
	return this->speed;
}

void Enemy::setSpawnLocation(sf::Vector2f spawnLocation)
{
	this->spawnLocation = spawnLocation;
	this->enemySprite.setPosition(this->spawnLocation);
}

float Enemy::getXSize()
{
	return this->enemySprite.getTexture()->getSize().x;
}

float Enemy::getYSize()
{
	return this->enemySprite.getTexture()->getSize().y;
}

sf::Vector2f Enemy::getLocation()
{
	return this->enemySprite.getPosition();
}

sf::Sprite Enemy::getEnemy()
{
	return this->enemySprite;
}

void Enemy::initEnemy()
{
	this->setHealth(1);
	this->setDamage(1);

	this->speed = 5.f;

	if (!this->enemyTexture.loadFromFile("assets/enemy.png"))
		std::cout << "Failed to load enemy texture!" << std::endl;
	else
		std::cout << "Successfully load enemy texture!" << std::endl;

	this->enemySprite.setTexture(this->enemyTexture);
	this->enemyYSize = this->enemySprite.getTexture()->getSize().y * this->enemySprite.getScale().y;
	this->enemyXSize = this->enemySprite.getTexture()->getSize().x * this->enemySprite.getScale().x;
}

void Enemy::update()
{
	this->enemySprite.move(-this->speed, 0.f);
}
