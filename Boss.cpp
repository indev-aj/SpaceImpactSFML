#include "Boss.h"

Boss::Boss()
{
    initBoss();
}

Boss::~Boss()
{
}

void Boss::setHealth(int health)
{
    this->health = health;
}

void Boss::setDamage(int damage)
{
    this->damage = damage;
}

void Boss::setSpeed(int speed)
{
    this->speed = speed;
}

void Boss::setSpawnLocation(sf::Vector2f spawnLocation)
{
    this->spawnLocation = spawnLocation;
    this->bossSprite.setPosition(this->spawnLocation);
}

float Boss::getXSize()
{
    return 0.0f;
}

float Boss::getYSize()
{
    return 0.0f;
}

int Boss::getDamage()
{
    return this->damage;
}

int Boss::getHealth()
{
    return this->health;
}

sf::Sprite Boss::getBoss()
{
    return this->bossSprite;
}

sf::Vector2f Boss::getCurrentPosition()
{
    return this->bossSprite.getPosition();
}

void Boss::initBoss()
{
    this->setHealth(10);
    this->setDamage(1);
    this->setSpeed(1);

    if (!this->bossTexture.loadFromFile("assets/boss.png"))
        std::cout << "Failed to load boss texture!" << std::endl;
    else
        std::cout << "Successfully load boss texture!" << std::endl;

    this->bossSprite.setTexture(this->bossTexture);
    this->bossYSize = this->bossSprite.getTexture()->getSize().y * this->bossSprite.getScale().y;
    this->bossXSize = this->bossSprite.getTexture()->getSize().x * this->bossSprite.getScale().x;
}

void Boss::moveIn()
{
    this->bossSprite.move(-this->speed, 0.f);
}

void Boss::moveUp()
{
    this->bossSprite.move(0.f, -this->speed);
}

void Boss::moveDown()
{
    this->bossSprite.move(0.f, this->speed);
}
