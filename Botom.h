#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Botom : public Enemy {
protected:
    static sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    static sf::Texture snowTexture;
    sf::Sprite snowSprite;
    int frame;
    int timer;
    int delay;
public:
    Botom(float startX, float startY, float spd);
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void checkPlatform(sf::RectangleShape& platform) override;
    void setDirection(int dir) override;
    void checkWall(sf::RectangleShape& platform) override;
};