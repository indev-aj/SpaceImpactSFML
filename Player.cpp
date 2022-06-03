#include "Player.h"

// Constructor
Player::Player()
{
	initSounds();
	initPlayer();
	initEnemy();
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
	this->toSpawnBoss = rand() % 10 + 3;
	this->died = false;
	this->fired = false;
	this->bossSpawned = false;
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

// Initialize HUD
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

	if (!this->font.loadFromFile("assets/fonts/roman.ttf"))
		std::cout << "Failed to load font!" << std::endl;
	else
		std::cout << "Successfully load font!" << std::endl;

	this->lifeSprite.setTexture(this->lifeTexture);
	this->lifeSprite.setScale(0.1, 0.1);
	this->lifeYSize = this->lifeSprite.getTexture()->getSize().y * this->lifeSprite.getScale().y;
	this->lifeXSize = this->lifeSprite.getTexture()->getSize().x * this->lifeSprite.getScale().x;

	this->hudBar.setSize(sf::Vector2f(800.f, 30.f));
	this->hudBar.setPosition(0.f, 0.f);
	this->hudBar.setFillColor(sf::Color(0, 0, 0, 100));

	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(18);

	this->scoreText.setString("Score: 0");
	sf::FloatRect textBound = scoreText.getGlobalBounds();

	this->scoreText.setPosition(this->rightBound - textBound.width - 10, 3.f);

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

	// Enemy Spawn Timing
	if (!this->bossSpawned) {
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
	}
	else {
		if (this->movingTimer >= this->MAX_MOVING_TIMER) {
			if (!this->changeDirection) {
				this->changeDirection = true;
				this->movingTimer = 0;
			}
		}
		else {
			this->changeDirection = false;

			if (this->movingTimer < this->MAX_MOVING_TIMER)
				this->movingTimer += 1;
		}
	}
}

void Player::fireProjectile()
{
	if (this->fired) {
		this->fireSound.play();
		setProjectileSpawnLocation();
		this->projectile = new Projectile(this->projectileSpawnLocation);
		this->projectile->setSpeed(5);

		this->projectiles.push_back(*this->projectile);
	}
}

void Player::initEnemy()
{
	this->MAX_SPAWN_TIMER = 100;
	this->spawnTimer = 0;
	this->spawned = true;
}

void Player::spawnEnemy()
{
	if (this->spawned) {
		this->enemy = new Enemy();
		this->enemySpawnLocation.x = this->rightBound + this->enemy->getXSize();
		this->enemySpawnLocation.y = rand() % int(this->bottomBound - this->enemy->getYSize()) + 30;
		this->enemy->setSpawnLocation(this->enemySpawnLocation);

		enemies.push_back(*this->enemy);
	}
}

void Player::initBoss()
{
	this->MAX_MOVING_TIMER = 100;
	this->movingTimer = 0;
	this->bossSpawned = true;
}

void Player::spawnBoss()
{
	if (this->bossSpawned && !once) {
		this->boss = new Boss();
		this->bossSpawnLocation.x = this->rightBound + this->boss->getXSize();
		this->bossSpawnLocation.y = this->bottomBound / 2 - this->boss->getYSize();

		this->boss->setSpawnLocation(this->bossSpawnLocation);

		once = true;
	}
}

void Player::bulletOnHit()
{
	if (this->projectiles.size() > 0 && this->enemies.size() > 0) {
		for (int i = 0; i < this->projectiles.size(); i++) {
			for (int j = 0; j < this->enemies.size(); j++) {
				if (projectiles[i].getProjectile().getGlobalBounds().intersects(enemies[j].getEnemy().getGlobalBounds())) {
					this->projectiles.erase(projectiles.begin() + i);
					this->enemies.erase(enemies.begin() + j);

					// Update Score
					this->score += 1;
					std::string scoreString = "Score: " + std::to_string(this->score);
					this->scoreText.setString(scoreString);
					sf::FloatRect textBound = scoreText.getGlobalBounds();

					this->scoreText.setPosition(this->rightBound - textBound.width - 10, 3.f);

					if (this->score == this->toSpawnBoss)
						initBoss();
				}
			}
		}
	}
	else if (this->projectiles.size() > 0 && bossSpawned) {
		for (int i = 0; i < this->projectiles.size(); i++) {
			if (projectiles[i].getProjectile().getGlobalBounds().intersects(this->boss->getBoss().getGlobalBounds())) {
				int currentHealth = this->boss->getHealth();
				currentHealth--;

				this->boss->setHealth(currentHealth);
				this->projectiles.erase(projectiles.begin() + i);

				if (this->boss->getHealth() <= 0) {
					this->score += 5;
					std::string scoreString = "Score: " + std::to_string(this->score);
					this->scoreText.setString(scoreString);
					sf::FloatRect textBound = scoreText.getGlobalBounds();

					this->scoreText.setPosition(this->rightBound - textBound.width - 10, 3.f);
					delete this->boss;
					this->gameWon = true;
				}
			}
		}
	}
}

void Player::enemyOnHit()
{
	if (this->enemies.size() > 0) {
		for (int i = 0; i < this->enemies.size(); i++) {
			if (enemies[i].getEnemy().getGlobalBounds().intersects(this->playerSprite.getGlobalBounds())) {
				std::cout << enemies[i].getDamage() << " damage taken!" << std::endl;
				this->health -= 1;
				this->lifes.pop_back();
				this->enemies.erase(enemies.begin() + i);

				this->damagedSound.play();
			}
		}
	}
}

void Player::initSounds()
{
	if (!this->fireBuffer.loadFromFile("assets/audio/fire.ogg"))
		std::cout << "Failed to load fire.ogg!" << std::endl;
	else
		this->fireSound.setBuffer(this->fireBuffer);

	if (!this->damagedBuffer.loadFromFile("assets/audio/damaged.ogg"))
		std::cout << "Failed to load fire.ogg!" << std::endl;
	else
		this->damagedSound.setBuffer(this->damagedBuffer);
}

void Player::endGame()
{
	this->endGameText.setFont(this->font);
	if (this->gameWon) {
		this->endGameText.setString("You Won The Game!");
		this->endGameText.setOrigin(this->endGameText.getLocalBounds().width / 2, this->endGameText.getLocalBounds().height / 2);
		this->endGameText.setPosition(this->rightBound / 2, this->bottomBound / 2);

		if (this->playerSprite.getPosition().x <= 0 && this->playerSprite.getPosition().y <= (this->bottomBound / 2 - this->playerYSize)) {
			this->inPlace = true;
		}

		if (!this->inPlace) {
			if (this->playerSprite.getPosition().y > (this->bottomBound / 2 - this->playerYSize)) {
				playerSprite.move(0.f, -2.f);
			}
			else if (this->playerSprite.getPosition().y < (this->bottomBound / 2 - this->playerYSize)) {
				playerSprite.move(0.f, 2.f);
			}

			if (this->playerSprite.getPosition().x > 0) {
				playerSprite.move(-2.f, 0.f);
			}
		}
		else if (this->inPlace) {
			playerSprite.move(5.f, 0.f);
		}

		if (this->playerSprite.getPosition().x > this->rightBound) {
			this->endGameText.setString(" You Won The Game!\nPress SPACEBAR To Exit");
			this->endGameText.setPosition((this->rightBound / 2) - 18, this->bottomBound / 2);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				this->died = true;
			}
		}
	}
	else if (this->health <= 0) {
		this->endGameText.setString(" You Lose The Game!\nPress SPACEBAR To Exit");
		this->endGameText.setOrigin(this->endGameText.getLocalBounds().width / 2, this->endGameText.getLocalBounds().height / 2);
		this->endGameText.setPosition((this->rightBound / 2) + 20, this->bottomBound / 2);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			this->died = true;
		}
	}
}

void Player::bossUpdate()
{
	if (this->boss->getCurrentPosition().x > this->rightBound - this->boss->getXSize() - 100) {
		this->boss->moveIn();
		if (this->boss->getCurrentPosition().x <= this->rightBound - this->boss->getXSize() - 100)
			this->hasEntered = true;
	}

	if (hasEntered) {
		if (this->changeDirection) {
			this->moveCount++;

			if (this->dir == "up" && this->moveCount > 1) {
				this->dir = "down";
				this->moveCount = 0;
			}
			else if (this->dir == "down" && this->moveCount > 1) {
				this->dir = "up";
				this->moveCount = 0;
			}
		}

		if (this->dir == "up")
			this->boss->moveUp();
		else if (this->dir == "down")
			this->boss->moveDown();
	}
}

void Player::update()
{
	if (!this->gameWon) {
		playerMovement();
		fireProjectile();

		spawnEnemy();

		bulletOnHit();
		enemyOnHit();

		spawnBoss();
	}

	endGame();
}

void Player::render(sf::RenderTarget* target)
{
	if (this->health > 0)
		target->draw(this->playerSprite);
	
	target->draw(this->hudBar);
	target->draw(this->scoreText);
	target->draw(this->endGameText);

	if (this->lifes.size() > 0) {
		for (int i = 0; i < this->lifes.size(); i++) {
			target->draw(this->lifes[i]);
		}
	}

	// Draw Projectiles
	if (this->projectiles.size() > 0) {
		for (int i = 0; i < this->projectiles.size(); i++) {
			this->projectiles[i].update();
			target->draw(this->projectiles[i].getProjectile());

			if (this->projectiles[i].getLocation().x > this->rightBound) {
				this->projectiles.erase(projectiles.begin() + i);
			}
		}
	}

	// Draw Enemies
	if (this->enemies.size() > 0) {
		for (int i = 0; i < this->enemies.size(); i++) {
			this->enemies[i].update();
			target->draw(this->enemies[i].getEnemy());

			if (this->enemies[i].getLocation().x < this->leftBound - this->enemies[i].getXSize()) {
				this->enemies.erase(enemies.begin() + i);
			}
		}
	}

	if (this->bossSpawned && !this->gameWon) {
		target->draw(this->boss->getBoss());
		bossUpdate();
	}
}
