#include "Player.h"

// Constructor
Player::Player()
{
	initPlayer();
}

// Destructor
Player::~Player()
{

}

// Setter
void Player::setHealth(int health)
{
	this->health = health;
}

void Player::setFiringTimer(float timer)
{
	this->firingTimer = timer;
}

void Player::setProjectileSpawnLocation(sf::Vector2f location)
{
	this->projectileSpawnLocation = location;
}

// Getter
sf::Vector2f Player::getProjectileSpawnLocation()
{
	return this->projectileSpawnLocation;
}

float Player::getFiringTimer()
{
	return this->firingTimer;
}

int Player::getHealth()
{
	return this->health;
}

int Player::getScore()
{
	return this->score;
}

// Initialize Player object
void Player::initPlayer()
{
	this->setHealth(10);
	this->setFiringTimer(0.f);

	this->score = 0;
	this->MAX_FIRING_TIMER = 20.f;
	this->died = false;
	this->fired = false;
	this->movementSpeed = 10.f;
	this->health = this->getHealth();
	this->firingTimer = this->getFiringTimer();

	this->player.setSize(sf::Vector2f(50.f, 50.f));
	this->player.setFillColor(sf::Color::Blue);
	this->player.setPosition(0.f, 0.f);
}

// Handle Keyboard Input
void Player::playerMovement()
{
	// Move Vertically
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player.move(0.f, this->movementSpeed);
	}

	// Move Horizontally
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player.move(this->movementSpeed, 0.f);
	}

	// Fire
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->firingTimer >= this->MAX_FIRING_TIMER) {
		if (!this->fired) {
			this->fired = true;
			this->firingTimer = 0;
		}
	}
	else {
		this->fired = false;

		if (this->firingTimer < this->MAX_FIRING_TIMER)
			this->firingTimer += 1;
	}
}

void Player::fireProjectile()
{
	if (this->fired) {
		std::cout << "Fired: " << this->fired << std::endl;
	}
}

void Player::update()
{
	playerMovement();
	fireProjectile();
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->player);
}
