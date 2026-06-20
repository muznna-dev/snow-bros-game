#pragma once
#include <SFML/Graphics.hpp>
#include "FlyngFoogaFooga.h"
#include "Projectile.h"

class Tornado : public FlyngFoogaFoog {
private:
    int  tornadoTime;
    bool knifeReady;
    Knife* knife;
    static sf::Texture tornadoTexture;
public:
    Tornado(float x, float y, float spd);
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void checkPlatform(sf::RectangleShape& platform) override;
    void attack(float playerX, float playerY) override;
    bool shouldThrowKnife() const { return knifeReady; }
    void resetKnife() { knifeReady = false; }
    Knife* getKnife() override;
};