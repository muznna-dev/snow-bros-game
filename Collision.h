#pragma once
#include "SFML/Graphics.hpp"
class Collision
{
public:
    static bool intersects(const sf::FloatRect& Hitbox1, const sf::FloatRect& Hitbox2);
    static bool isLandingOnPlatform(const sf::FloatRect& Hitbox, float objectVy, const sf::FloatRect& platHitbox);
};