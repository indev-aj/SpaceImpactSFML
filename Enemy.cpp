#include "Enemy.h"

Enemy::Enemy()
{
	this->topBound = 0.f;
	this->rightBound = 800.f;
	this->bottomBound = 600.f;
	this->leftBound = 0.f;
	initEnemy();
}

Enemy::~Enemy()
{
}

void Enemy::setSpawnTimer(float timer)
{
	this->spawnTimer = timer;
}

void Enemy::setHealth(int health)
{
	this->health = health;
}

void Enemy::setDamage(int damage)
{
	this->damage = damage;
}

float Enemy::getSpawnTimer()
{
	return this->spawnTimer;
}

int Enemy::getDamage()
{
	return this->damage;
}

int Enemy::getHealth()
{
	return this->health;
}

void Enemy::enemyMovement()
{
	if (this->spawnTimer >= this->MAX_SPAWN_TIMER) {
		if (!this->spawned) {
			this->spawned = true;
			this->spawnTimer = 0;
		}
	}
	else {
		this->spawned = false;

		if (this->spawnTimer < this->MAX_SPAWN_TIMER)
			this->spawnTimer += 1;
	}

	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].move(-this->movementSpeed, 0.f);
	}
}

void Enemy::spawnEnemy()
{
	if (this->enemyCount < maxEnemyCount) {
		this->spawnLocation.x = this->rightBound + enemyXSize;
		this->spawnLocation.y = rand() % int(this->bottomBound - enemyYSize) + 30;
		enemySprite.setPosition(this->spawnLocation);
		
		if (this->spawned) {
			enemies.push_back(enemySprite);
			this->enemyCount++;
		}
	}
}

void Enemy::initEnemy()
{
	this->setHealth(1);
	this->setDamage(1);
	this->setSpawnTimer(0.f);

	this->MAX_SPAWN_TIMER = 125.f;
	this->maxEnemyCount = 10;
	this->movementSpeed = 5.f;
	this->maxEnemyCount = 10;
	this->spawned = false;

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
	spawnEnemy();
	enemyMovement();
}

void Enemy::render(sf::RenderTarget* target)
{
	for (int i = 0; i < enemies.size(); i++) {
		target->draw(this->enemies[i]);

		if (this->enemies[i].getPosition().x < (this->leftBound - enemyXSize)) {
			this->enemies.erase(enemies.begin() + i);
		}
	}
}
