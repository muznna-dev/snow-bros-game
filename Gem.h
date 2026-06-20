#pragma once
#include <SFML/Graphics.hpp>

class Gem {
private:
    float x, y;
    bool collected;
    sf::CircleShape shape;
    static sf::Texture emeraldTexture;
public:
    Gem(float startX, float startY);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getHitBox() const;
    bool isCollected() const;
    void collect();
};