#include "Tornado.h"
#include <iostream>
using namespace std;

sf::Texture Tornado::tornadoTexture;
Tornado::Tornado(float x, float y, float spd)
    : FlyngFoogaFoog(x, y, spd)
{
    startTimer = 0;
    tornadoTime = 0;
    knifeReady = false;
    knife = nullptr;
    frame = 0;
    timer = 0;
    delay = 10;
    if (tornadoTexture.getSize().x == 0)
    {
        if (!tornadoTexture.loadFromFile("SnowBrosAssets/Images/Tornado_Blue.png"))
        {
            cout << "Tornado image failed to load" << endl;
        }
    }
    enemySprite.setTexture(tornadoTexture);
    enemySprite.setTextureRect(sf::IntRect(0, 39, 136, 120));
    enemySprite.setOrigin(40, 40);
    enemySprite.setScale(0.5f, 0.5f);
}

void Tornado::update() {
    if (startTimer < 220)
    {
        startTimer++;
        vy += 0.5f;
        y += vy;
        enemySprite.setTextureRect(sf::IntRect(0, 39, 136, 120));
        enemySprite.setOrigin(40, 60);
        if (direction == -1)
        {
            enemySprite.setScale(0.5f, 0.5f);
        }
        else
        {
            enemySprite.setScale(-0.5f, 0.5f);
        }
        return;
    }
    FlyngFoogaFoog::update();
    if (isFrozen || isEncased)
    {
        knife = nullptr;
        enemySprite.setTextureRect(sf::IntRect(0, 39, 136, 120));
        enemySprite.setOrigin(60, 60);
        if (direction == -1)
        {
            enemySprite.setScale(0.5f, 0.5f);
        }
        else
        {
            enemySprite.setScale(-0.5f, 0.5f);
        }
        return;
    }
    tornadoTime++;
    if (tornadoTime >= 60) {
        knifeReady = true;
        tornadoTime = 0;
    }
    timer++;
    if (timer >= delay)
    {
        frame++;
        if (frame > 2)
        {
            frame = 0;
        }
        timer = 0;
    }
    if (!flight)
    {
        delay = 10;
        if (frame == 0)
        {
            enemySprite.setTextureRect(sf::IntRect(147, 39, 136, 120));
        }
        else if (frame == 1)
        {
            enemySprite.setTextureRect(sf::IntRect(279, 39, 135, 120));
        }
        else if (frame == 2)
        {
            enemySprite.setTextureRect(sf::IntRect(420, 34, 136, 120));
        }
    }
    else
    {
        delay = 15;
        if (frame == 0)
        {
            enemySprite.setTextureRect(sf::IntRect(0, 1040, 136, 120));
        }
        else if (frame == 1)
        {
            enemySprite.setTextureRect(sf::IntRect(147, 1040, 135, 120));
        }
        else if (frame == 2)
        {
            enemySprite.setTextureRect(sf::IntRect(279, 1040, 136, 120));
        }
    }
    enemySprite.setOrigin(40, 70);
    if (direction == -1)
    {
        enemySprite.setScale(0.5f, 0.5f);
    }
    else
    {
        enemySprite.setScale(-0.5f, 0.5f);
    }
}

void Tornado::checkPlatform(sf::RectangleShape& platform) {

    FlyngFoogaFoog::checkPlatform(platform);
}

void Tornado::draw(sf::RenderWindow& window) {

    enemySprite.setPosition(x + width / 2, y + height / 2);
    window.draw(enemySprite);
    if (snowCoat > 0 || isEncased)
    {
        snowSprite.setPosition(x + width / 2, y + height / 2 - 5);
        window.draw(snowSprite);
    }
    if (knife != nullptr)
    {
        knife->draw(window);
    }
}
void Tornado::attack(float playerX, float playerY)
{
    if (getIsEncased() || getIsRolling())
    {
        return;
    }
    if (knifeReady && knife == nullptr && playerY == y)
    {
        knife = new Knife(x, y, playerX, playerY, 5);
        knifeReady = false;
    }
    if (knife != nullptr)
    {
        knife->update();

        if (!knife->getIsActive())
        {
            delete knife;
            knife = nullptr;
        }
    }
}
Knife* Tornado::getKnife()
{
    return knife;
}