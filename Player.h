#pragma once
#include "SFML/Graphics.hpp"
#include "Collision.h"
#include "Projectile.h"
class Player
{
private:
    float x, y;
    float spawnX, spawnY;
    float vx, vy;
    float speed;
    float gravity;
    float jumpStrength;
    bool isOnGround;
    int lives;
    int facing;
    Snowball* snowball;
    bool thrown;
    sf::RectangleShape player;
    bool snowballPower;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    int frame;
    int timer;
    int delay;
    sf::Keyboard::Key left, right, jump, shoot;
    bool distancePower;
    int speedTime;
    int balloonTime;
    bool speedOn;
    bool balloonOn;
public:
    Player();
    void handleInput();
    void update();
    void draw(sf::RenderWindow& window);
    void checkPlatform(sf::RectangleShape& platform);
    sf::FloatRect getHitbox() const;
    float getVy() const;
    void landOn(float yPos);
    Snowball* getSnowball();
    void loseLife();
    void setSpeed(float val);
    float getSpeed() const;
    void setGravity(float val);
    void setSnowballPower(bool val);
    bool getSnowballPower();
    void setPosition(float playerX, float playerY);
    void setDirection(int direction);
    int getLives() const;
    void addLife();
    void checkWall(sf::RectangleShape& wall);
    void respawn();
    void setControls(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j, sf::Keyboard::Key s);
    void setDistancePower(bool val);
    void activateSpeed(int time, float newSpeed);
    void activateBalloon(int time, float newGravity);
};