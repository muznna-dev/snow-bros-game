#include "Enemy.h"

Enemy::Enemy(float startX, float startY, float w, float h, int hp, float spd)
    : x(startX), y(startY), width(w), height(h),
    health(hp), speed(spd), alive(true), direction(1), vy(0.0f), snowCoat(0), maxSnowCoat(4),
    isRolling(false), isEncased(false), isFrozen(false), startTimer(0), snowDecay(120), snowDecayTimer(0), snowPower(1), killedByPlayer(1)
{
}
Enemy::~Enemy() {}

void Enemy::landOn(float yPos) {
    y = yPos;
    vy = 0.0f;
}

void Enemy::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        alive = false;
    }
}

sf::FloatRect Enemy::getHitBox() const {
    return sf::FloatRect(x, y, width, height);
}

bool Enemy::isAlive() const {
    return alive;
}
float Enemy::getX() const { return x; }
float Enemy::getY() const { return y; }
float Enemy::getVy() const { return vy; }
void Enemy::gotHit()
{
    if (snowPower == 1)
    {
        snowCoat++;
    }
    if (snowPower == 2)
    {
        snowCoat += 2;
    }
    if (isRolling)
    {
        return;
    }
    if (snowCoat == 1)
    {
        isFrozen = true;
    }
    else if (snowCoat >= 3)
    {
        isEncased = true;
        isFrozen = false;
        vy = 0;
    }
}
bool Enemy::getIsRolling() const
{
    return isRolling;
}
bool Enemy::getIsEncased() const
{
    return isEncased;
}
void Enemy::startRolling(int dir)
{
    if (isEncased)
    {
        isRolling = true;
        direction = dir;
    }
}
void Enemy::setDecayTimer()
{
    snowDecayTimer = 0;
}
int Enemy::getDirection() const
{
    return direction;
}
void Enemy::becomeEncased()
{
    isEncased = true;
}
void Enemy::skipSpawnDelay()
{
    startTimer = 180;
}
void Enemy::setSnowPower(int power)
{
    snowPower = power;
}
int Enemy::getScore() const {
    return 100;
}
void Enemy::setKilledBy(int player) {
    killedByPlayer = player;
}
int Enemy::getKilledBy() const {
    return killedByPlayer;
}