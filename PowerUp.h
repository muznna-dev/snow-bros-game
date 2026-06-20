#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class PowerUp {
protected:
    float x, y;
    bool  isActive;
    float duration;
    float timer;
public:
    PowerUp(float x, float y, float duration);
    virtual ~PowerUp() {}
    virtual void apply(Player& player) = 0;
    virtual void remove(Player& player) = 0;
    virtual void update();
    virtual void draw(sf::RenderWindow& window) = 0;
    bool getIsActive() const;
    float getX() const;
    float getY() const;
    sf::FloatRect getHitBox() const;
};
class SpeedBoost : public PowerUp {
public:
    SpeedBoost(float x, float y);
    void apply(Player& player) override;
    void remove(Player& player) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};
class SnowballPower : public PowerUp {
public:
    SnowballPower(float x, float y);
    void apply(Player& player) override;
    void remove(Player& player) override;
    void draw(sf::RenderWindow& window) override;
};
class DistanceIncrease : public PowerUp {
public:
    DistanceIncrease(float x, float y);
    void apply(Player& player) override;
    void remove(Player& player) override;
    void draw(sf::RenderWindow& window) override;
};
class BalloonMode : public PowerUp {
public:
    BalloonMode(float x, float y);
    void apply(Player& player) override;
    void remove(Player& player) override;
    void update() override;
    void draw(sf::RenderWindow& window) override;
};