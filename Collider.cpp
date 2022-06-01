#include "Collider.h"

Collider::Collider(sf::Sprite& body) : body(body)
{

}

Collider::~Collider()
{
}

bool Collider::checkCollision(Collider& other)
{
    sf::Vector2f otherPos = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPos = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPos.x - thisPos.x;
    float deltaY = otherPos.y - thisPos.y;

    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        return true;
    }

    return false;
}
