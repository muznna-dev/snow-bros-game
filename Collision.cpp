#include "Collision.h"
#include <iostream>
using namespace std;
bool Collision::intersects(const sf::FloatRect& Hitbox1, const sf::FloatRect& Hitbox2)
{
    return Hitbox1.intersects(Hitbox2);
}
bool Collision::isLandingOnPlatform(const sf::FloatRect& Hitbox, float objectVy, const sf::FloatRect& platHitbox)
{
    float objectFeet = Hitbox.top + Hitbox.height;
    float platTop = platHitbox.top;
    return (Hitbox.intersects(platHitbox) && objectVy > 0 && objectFeet <= platTop + 15);
}