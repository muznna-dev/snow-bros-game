
#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
class Enemy {
protected:
    float x, y;
    float width, height;
    int health;
    float speed;
    bool alive;
    int direction;
    float vy;
    int snowCoat;
    int maxSnowCoat;
    bool isEncased;
    bool isRolling;
    bool isFrozen;
    int startTimer;
    int snowDecay;
    int snowDecayTimer;
    int snowPower;
    int killedByPlayer;
public:
    Enemy(float startX, float startY, float w, float h, int hp, float s);
    virtual ~Enemy();
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void checkPlatform(sf::RectangleShape& platform) = 0;  // pure virtual
    virtual void checkWall(sf::RectangleShape& wall) = 0;
    void  landOn(float yPos);      // shared landing logic
    void  takeDamage(int amount);
    sf::FloatRect getHitBox() const;
    bool  isAlive() const;
    float getX()   const;
    float getY()   const;
    float getVy()  const;
    virtual void setDirection(int dir) = 0;
    virtual void gotHit();
    bool getIsRolling() const;
    bool getIsEncased() const;
    int getDirection() const;
    void startRolling(int dir);
    void becomeEncased();
    virtual void attack(float playerX, float playerY) {};
    virtual Knife* getKnife() { return nullptr; }
    void setDecayTimer();
    virtual bool shouldSpawn() const { return false; }
    virtual Enemy* spawnChild() { return nullptr; }
    void skipSpawnDelay();
    void setSnowPower(int power);
    int getScore() const;
    void setKilledBy(int player);
    int getKilledBy() const;
};