#include "Gem.h"
sf::Texture Gem::emeraldTexture;
Gem::Gem(float startX, float startY) : x(startX), y(startY), collected(false) {
    if (emeraldTexture.getSize().x == 0)
    {
        emeraldTexture.loadFromFile("SnowBrosAssets/Images/emerald.png");
    }
    shape.setRadius(16.f);
    shape.setTexture(&emeraldTexture);
    shape.setOrigin(16.f, 16.f);
    shape.setPosition(x, y);
}

void Gem::draw(sf::RenderWindow& window) {
    if (!collected) window.draw(shape);
}

sf::FloatRect Gem::getHitBox() const {
    return shape.getGlobalBounds();
}

bool Gem::isCollected() const {
    return collected;
}

void Gem::collect() {
    collected = true;
}