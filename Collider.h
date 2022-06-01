#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
private:
	sf::Sprite& body;
public:
	Collider(sf::Sprite& body);
	~Collider();

	sf::Vector2f getPosition() { return body.getPosition(); }
	sf::Vector2f getHalfSize() { return { body.getTexture()->getSize().x / 2.0f , body.getTexture()->getSize().y / 2.0f }; }
	bool checkCollision(Collider& other);
};

