#include "FlyngFoogaFooga.h"
#include "Collision.h"
#include <cstdlib>
#include <iostream>
using namespace std;
sf::Texture FlyngFoogaFoog::foogaTexture;

FlyngFoogaFoog::FlyngFoogaFoog(float x, float y, float spd)
    : Botom(x, y, spd)
{
    flight = false;
    groundTime = 0;
    flightTime = 0;
    maxSnowCoat = 4;
    groundDuration = 200 + rand() % 301;
    flightDuration = 120 + rand() % 81;

    flightPhase = 0;
    hoverTime = 0;

    vy = -1.0f;
    if (foogaTexture.getSize().x == 0)
    {
        if (!foogaTexture.loadFromFile("SnowBrosAssets/Images/FlyingFoogaFoog_Blue.png"))
        {
            cout << "Fooga image failed to load" << endl;
        }
    }
    enemySprite.setTexture(foogaTexture);
    enemySprite.setTextureRect(sf::IntRect(0, 0, 80, 70));
    enemySprite.setOrigin(72, 120);
    enemySprite.setScale(0.45f, 0.45f);
}

void FlyngFoogaFoog::update() {
    if (isEncased || isFrozen)
    {
        flight = false;
    }
    if (!flight) {
        Botom::update();
        enemySprite.setTextureRect(sf::IntRect(0, 0, 182, 180));
        enemySprite.setOrigin(90, 120);
        enemySprite.setScale(0.45f * -direction, 0.45f);
        groundTime++;

        if (groundTime >= groundDuration) {
            flight = true;
            groundTime = 0;
            flightTime = 0;

            groundDuration = 200 + rand() % 301;
            flightDuration = 120 + rand() % 81;

            flightPhase = 0;
            hoverTime = 0;
            vy = -1.0f;
        }
    }
    else {
        flightTime++;
        enemySprite.setTextureRect(sf::IntRect(208, 14, 182, 180));
        enemySprite.setOrigin(40, 73);
        enemySprite.setScale(0.45f * -direction, 0.45f);
        x += direction * speed;
        if (flightPhase == 0) {
            y += vy;

            if (y <= 120.0f) {
                y = 120.0f;
                flightPhase = 1;
                hoverTime = 0;
            }
        }
        else if (flightPhase == 1) {
            hoverTime += 10;

            if (hoverTime >= 40) {
                flightPhase = 2;
                vy = 1.0f;
            }
        }
        else if (flightPhase == 2) {
            y += vy;
        }
        if (x <= 0 || x + width >= 800) {
            direction *= -1;
        }
        if (flightTime >= flightDuration) {
            flight = false;
            flightTime = 0;
        }
    }
}

void FlyngFoogaFoog::checkPlatform(sf::RectangleShape& platform) {

    if (!flight) {
        sf::FloatRect hitbox = getHitBox();
        sf::FloatRect platHitbox = platform.getGlobalBounds();

        if (Collision::isLandingOnPlatform(hitbox, vy, platHitbox)) {
            landOn(platHitbox.top - hitbox.height);
        }
    }
}

void FlyngFoogaFoog::draw(sf::RenderWindow& window) {
    enemySprite.setPosition(x + width / 2, y + height / 2);
    window.draw(enemySprite);
    if (snowCoat > 0 || isEncased)
    {
        snowSprite.setPosition(x + width / 2, y + height / 2 - 5);
        window.draw(snowSprite);
    }
}
void FlyngFoogaFoog::setFlight(bool val)
{
    flight = val;
}