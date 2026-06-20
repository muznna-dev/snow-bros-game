#include "PowerUp.h"
PowerUp::PowerUp(float x, float y, float duration)
    : x(x), y(y), duration(duration), timer(0), isActive(true) {
}
void PowerUp::update() {

}
bool PowerUp::getIsActive() const { return isActive; }
float PowerUp::getX() const { return x; }
float PowerUp::getY() const { return y; }
sf::FloatRect PowerUp::getHitBox()   const { return sf::FloatRect(x, y, 20, 20); }
SpeedBoost::SpeedBoost(float x, float y)
    : PowerUp(x, y, 900) {
}
void SpeedBoost::apply(Player& player)
{
    player.activateSpeed(900, 7.5f);
}
void SpeedBoost::remove(Player& player) { player.setSpeed(player.getSpeed() / 1.5f); }
void SpeedBoost::update() {
    if (!isActive) return;
    timer++;
    if (timer >= duration)
        isActive = false;
}

void SpeedBoost::draw(sf::RenderWindow& window) {
    if (!isActive) return;
    sf::RectangleShape shape(sf::Vector2f(20, 20));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Yellow);
    window.draw(shape);
}
SnowballPower::SnowballPower(float x, float y)
    : PowerUp(x, y, -1) {
}
void SnowballPower::apply(Player& player) { player.setSnowballPower(true); }
void SnowballPower::remove(Player& player) { player.setSnowballPower(false); }
void SnowballPower::draw(sf::RenderWindow& window) {
    if (!isActive) return;
    sf::RectangleShape shape(sf::Vector2f(20, 20));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Cyan);
    window.draw(shape);
}
DistanceIncrease::DistanceIncrease(float x, float y)
    : PowerUp(x, y, -1) {
}
void DistanceIncrease::apply(Player& player) { player.setDistancePower(true); }
void DistanceIncrease::remove(Player& player) { player.setDistancePower(false); }
void DistanceIncrease::draw(sf::RenderWindow& window) {
    if (!isActive) return;
    sf::RectangleShape shape(sf::Vector2f(20, 20));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
    window.draw(shape);
}
BalloonMode::BalloonMode(float x, float y)
    : PowerUp(x, y, 600) {
}
void BalloonMode::apply(Player& player)
{
    player.activateBalloon(600, -0.0010f);
}
void BalloonMode::remove(Player& player) { player.setGravity(0.5f); }
void BalloonMode::update() {
    if (!isActive) return;
    timer++;
    if (timer >= duration)
        isActive = false;
}
void BalloonMode::draw(sf::RenderWindow& window) {
    if (!isActive) return;
    sf::RectangleShape shape(sf::Vector2f(20, 20));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Magenta);
    window.draw(shape);
}