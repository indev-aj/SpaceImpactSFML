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

void Player::setProjectileSpawnLocation()
{
	float playerXMid = this->playerXSize;
	float playerXPos = this->playerSprite.getPosition().x;

	float playerYMid = (this->playerYSize / 2) - 2;
	float playerYPos = this->playerSprite.getPosition().y;
	this->projectileSpawnLocation = { playerXPos + playerXMid, playerYPos + playerYMid };
}

// Getter
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

bool Player::getDied()
{
	return this->died;
}

// Initialize Player object
void Player::initPlayer()
{
	this->setHealth(3);
	this->setFiringTimer(0.f);

	this->score = 0;
	this->MAX_FIRING_TIMER = 20.f;
	this->died = false;
	this->fired = false;
	this->movementSpeed = 7.f;
	this->health = this->getHealth();
	this->firingTimer = this->getFiringTimer();

	if (!this->playerTexture.loadFromFile("assets/player 64bit.png"))
		std::cout << "Failed to load player texture!" << std::endl;
	else
		std::cout << "Successfully load player texture!" << std::endl;

	this->playerSprite.setTexture(this->playerTexture);
	this->playerYSize = this->playerSprite.getTexture()->getSize().y * this->playerSprite.getScale().y;
	this->playerXSize = this->playerSprite.getTexture()->getSize().x * this->playerSprite.getScale().x;
}

void Player::initHUD(float top, float right, float bottom, float left)
{
	this->topBound = top;
	this->rightBound = right;
	this->bottomBound = bottom;
	this->leftBound = left;

	if (!this->lifeTexture.loadFromFile("assets/heart original.png"))
		std::cout << "Failed to load life texture!" << std::endl;
	else
		std::cout << "Successfully load life texture!" << std::endl;

	this->lifeSprite.setTexture(this->lifeTexture);
	this->lifeSprite.setScale(0.1, 0.1);
	this->lifeYSize = this->lifeSprite.getTexture()->getSize().y * this->lifeSprite.getScale().y;
	this->lifeXSize = this->lifeSprite.getTexture()->getSize().x * this->lifeSprite.getScale().x;

	this->hudBar.setSize(sf::Vector2f(800.f, 30.f));
	this->hudBar.setPosition(0.f, 0.f);
	this->hudBar.setFillColor(sf::Color(0, 0, 0, 100));

	this->playerSprite.setPosition(0.f, (this->bottomBound / 2 - this->playerYSize));

	for (int i = 0; i < this->health; i++) {
		lifeSprite.setPosition(i * (lifeXSize + 5.f) + 5.f, 5.f);
		lifes.push_back(lifeSprite);
	}
}

// Handle Keyboard Input
void Player::playerMovement()
{
	// Move Vertically
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->playerSprite.getPosition().y > (topBound + this->hudBar.getSize().y)) {
		this->playerSprite.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->playerSprite.getPosition().y < (bottomBound - this->playerYSize)) {
		this->playerSprite.move(0.f, this->movementSpeed);
	}

	// Move Horizontally
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->playerSprite.getPosition().x > leftBound) {
		this->playerSprite.move(-this->movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->playerSprite.getPosition().x < (rightBound - this->playerXSize)) {
		this->playerSprite.move(this->movementSpeed, 0.f);
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
		setProjectileSpawnLocation();
		this->projectile = new Projectile(this->projectileSpawnLocation);
		this->projectile->setSpeed(5);

		this->projectiles.push_back(*this->projectile);

		// Reduce health
		/*this->health -= 1;
		lifes.pop_back();*/
	}
}

void Player::updateHUD()
{
	// Update health hud
	for (int i = 0; i < this->health; i++) {

	}
}

void Player::update()
{
	if (this->health > 0) {
		playerMovement();
		fireProjectile();
	}
	else {
		this->died = true;
	}
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->playerSprite);
	target->draw(this->hudBar);

	if (this->lifes.size() > 0) {
		for (int i = 0; i < this->lifes.size(); i++) {
			target->draw(this->lifes[i]);
		}
	}

	if (this->projectiles.size() > 0) {
		for (int i = 0; i < this->projectiles.size(); i++) {
			this->projectiles[i].update();
			target->draw(this->projectiles[i].getProjectile());

			if (this->projectiles[i].getLocation().x > this->rightBound) {
				this->projectiles.erase(projectiles.begin() + i);
			}
		}
	}
}
