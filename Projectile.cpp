#include "Projectile.h"
#include <iostream>
using namespace std;
Projectile::Projectile(float startX, float startY, float dX, float dY, float s) {
	x = startX;
	y = startY;
	dirx = dX;
	diry = dY;
	speed = s;
	isActive = true;
}
bool Projectile::getIsActive() const {
	return isActive;
}
sf::Texture Snowball::snowball;
Snowball::Snowball(float x, float y, float dirx, float diry, float speed)
	: Projectile(x, y, dirx, diry, speed)
{
	if (snowball.getSize().x == 0)
	{
		snowball.loadFromFile("SnowBrosAssets/Images/snowball.png");
	}
	snow.setTexture(snowball);
	snow.setScale(0.03f, 0.03f);
}
void Snowball::update() {
	x += dirx * speed;
	y += diry * speed;
	diry += 0.06f;
}
void Snowball::onPlatform()
{
	isActive = false;
}
void Snowball::onHit() {
	isActive = false;
}
sf::FloatRect Snowball::getHitBox() const {
	return sf::FloatRect(x, y, 16, 16);
}

void Snowball::draw(sf::RenderWindow& window) {
	snow.setPosition(x, y);
	window.draw(snow);
}
bool Snowball::getIsActive() const {
	return isActive;
}
void Snowball::setActive(bool val) {
	isActive = val;
}
sf::Texture Knife::knifeTexture;
Knife::Knife(float x, float y, float attackX, float attackY, float speed)
	: Projectile(x, y, 0, 0, speed)
{
	if (knifeTexture.getSize().x == 0)
	{
		knifeTexture.loadFromFile("SnowBrosAssets/Images/Tornado_Blue.png");
	}
	knifeSprite.setTexture(knifeTexture);
	knifeSprite.setTextureRect(sf::IntRect(426, 881, 68, 44));
	knifeSprite.setOrigin(16, 16);
	knifeSprite.setScale(0.6f, 0.6f);
	float dx = attackX - x;
	float dy = attackY - y;
	float distance = sqrt(dx * dx + dy * dy);
	if (distance != 0) {
		dirx = dx / distance;
		diry = dy / distance;
	}
	else {
		dirx = 1;
		diry = 0;
	}
}
void Knife::update() {
	x += dirx * speed;
	y += diry * speed;
	if (x > 800 || x < 0 || y>600 || y < 0)
		isActive = false;
}
void Knife::draw(sf::RenderWindow& window) {
	knifeSprite.setPosition(x, y);
	if (dirx == -1)
	{
		knifeSprite.setScale(0.6f, 0.6f);
	}
	else
	{
		knifeSprite.setScale(-0.6f, 0.6f);
	}
	window.draw(knifeSprite);
}
void Knife::onHit() {
	isActive = false;
}
sf::FloatRect Knife::getHitBox() const
{
	return sf::FloatRect(x, y, 16, 16);
}
Rocket::Rocket(float startX, float startY, float targetX, float targetY,
	float speed, float explosionRadius)
	: Projectile(startX, startY, 0, 0, speed),
	radius(explosionRadius),
	hasExploded(false)
{
	float dx = targetX - startX;
	float dy = targetY - startY;
	float len = sqrt(dx * dx + dy * dy);

	if (len != 0) {
		dirx = dx / len;
		diry = dy / len;
	}
}

void Rocket::update() {
	if (!isActive) return;

	x += dirx * speed;
	y += diry * speed;

	if (x < 0 || x > 800 || y < 0 || y > 600) {
		isActive = false;
	}
}

void Rocket::draw(sf::RenderWindow& window) {
	if (!isActive) return;

	sf::CircleShape shape(8.f);
	shape.setFillColor(sf::Color(255, 100, 0));
	shape.setPosition(x, y);
	window.draw(shape);
}

void Rocket::onHit() {
	hasExploded = true;
	isActive = false;
}

bool Rocket::getHasExploded() const {
	return hasExploded;
}

float Rocket::getRadius() const {
	return radius;
}