#include "Player.h"
#include <iostream>
#include "SFML/Graphics.hpp"
using namespace std;
Player::Player()
{
	spawnX = 50;
	spawnY = 530;
	x = spawnX;
	y = spawnY;
	vx = 0;
	vy = 0;
	frame = 0;
	timer = 0;
	delay = 8;
	speed = 5;
	gravity = 0.5;
	jumpStrength = -10;
	isOnGround = false;
	lives = 2;
	facing = 1;
	snowball = nullptr;
	thrown = false;
	player.setSize(sf::Vector2f(30.f, 50.f));
	player.setFillColor(sf::Color::White);
	snowballPower = false;
	if (!playerTexture.loadFromFile("SnowBrosAssets/Images/Skull.png"))
	{
		cout << "Player image failed to load" << endl;
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(20, 0, 65, 80));
	playerSprite.setScale(-0.90f, 0.90f);
	playerSprite.setOrigin(75.f / 2.f, 100.f / 2.f);
	speedTime = 0;
	balloonTime = 0;
	speedOn = false;
	balloonOn = false;
}
void Player::update()
{
	if (lives == 0)
	{
		playerSprite.setTextureRect(sf::IntRect(0, 800, 80, 80));
	}
	isOnGround = false;
	vy += gravity;
	x += vx;
	if (x < 20)
	{
		x = 20;
	}
	if (x + player.getSize().x > 780)
	{
		x = 780 - player.getSize().x;
	}
	y += vy;
	float groundLevel = 580;
	float playerHeight = 50;
	if (y >= groundLevel - playerHeight)
	{
		y = groundLevel - playerHeight;
		vy = 0;
		isOnGround = true;
	}
	if (snowball != nullptr)
	{
		snowball->update();
	}
	if (snowball != nullptr && !snowball->getIsActive())
	{
		delete snowball;
		snowball = nullptr;
	}
	player.setPosition(x, y);
	vx = 0;
	if (facing == 1)
	{
		playerSprite.setScale(-0.90f, 0.90f);
	}
	else if (facing == -1)
	{
		playerSprite.setScale(0.90f, 0.90f);
	}
	if (speedOn)
	{
		speedTime--;
		if (speedTime <= 0)
		{
			speed = 5;
			speedOn = false;
		}
	}
	if (balloonOn)
	{
		balloonTime--;
		if (balloonTime <= 0)
		{
			gravity = 0.5f;
			balloonOn = false;
		}
	}
}
void Player::handleInput()
{
	if (lives == 0)
	{
		playerSprite.setTextureRect(sf::IntRect(0, 800, 80, 80));
		return;
	}
	if (sf::Keyboard::isKeyPressed(left))
	{
		vx = -speed;
		facing = -1;
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
		if (frame == 0)
		{
			playerSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
		}
		else if (frame == 1)
		{
			playerSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
		}
		else if (frame == 2)
		{
			playerSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
		}
	}
	else if (sf::Keyboard::isKeyPressed(right))
	{
		vx = speed;
		facing = 1;
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
		if (frame == 0)
		{
			playerSprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
		}
		else if (frame == 1)
		{
			playerSprite.setTextureRect(sf::IntRect(160, 0, 80, 80));
		}
		else if (frame == 2)
		{
			playerSprite.setTextureRect(sf::IntRect(240, 0, 80, 80));
		}
	}
	else
	{
		vx = 0;
		frame = 0;
		timer = 0;
		playerSprite.setTextureRect(sf::IntRect(20, 0, 65, 80));
	}
	if (sf::Keyboard::isKeyPressed(jump) && isOnGround)
	{
		vy = jumpStrength;
		isOnGround = false;
	}
	if (sf::Keyboard::isKeyPressed(shoot))
	{
		if (snowball == nullptr && !thrown)
		{
			float snowballX = x + player.getSize().x / 2;
			float snowballY = y + player.getSize().y / 2;
			float strength;
			int range;
			if (distancePower)
			{
				range = 12;
				strength = -0.7f;
			}
			else
			{
				range = 6;
				strength = -0.5f;
			}
			snowball = new Snowball(snowballX, snowballY, facing, strength, range);
		}
		thrown = true;
		playerSprite.setTextureRect(sf::IntRect(244, 160, 80, 80));
	}
	else
	{
		thrown = false;
	}
	if (!isOnGround)
	{
		playerSprite.setTextureRect(sf::IntRect(320, 0, 80, 80));
	}
}
void Player::draw(sf::RenderWindow& window)
{
	player.setPosition(x, y);
	float hitboxCenterX = x + player.getSize().x / 2;
	float hitboxCenterY = y + player.getSize().y / 2;
	playerSprite.setPosition(hitboxCenterX, hitboxCenterY + 5);
	window.draw(playerSprite);
	if (snowball != nullptr)
	{
		snowball->draw(window);
	}
}
sf::FloatRect Player::getHitbox() const
{
	return player.getGlobalBounds();
}
float Player::getVy() const
{
	return vy;
}
void Player::landOn(float yPos)
{
	y = yPos;
	vy = 0;
	isOnGround = true;
	player.setPosition(x, y);
}
void Player::checkPlatform(sf::RectangleShape& platform)
{
	sf::FloatRect Hitbox = getHitbox();
	sf::FloatRect platHitbox = platform.getGlobalBounds();
	if (Collision::isLandingOnPlatform(Hitbox, vy, platHitbox))
	{
		landOn(platHitbox.top - Hitbox.height);
		playerSprite.setTextureRect(sf::IntRect(20, 0, 65, 80));
		handleInput();
	}
}
void Player::loseLife()
{
	if (lives > 0)
	{
		lives--;
		if (lives > 0)
		{
			respawn();
		}
	}
	if (lives < 0)
	{
		lives = 0;
	}
}
Snowball* Player::getSnowball()
{
	return snowball;
}
void Player::setSpeed(float val) {
	speed = val;
}
float Player::getSpeed() const {
	return speed;
}
void Player::setGravity(float val) {
	gravity = val;
}
void Player::setSnowballPower(bool val) {
	snowballPower = val;
}
bool Player::getSnowballPower() {
	return snowballPower;
}
int Player::getLives() const {
	return lives;
}
void Player::addLife() {
	lives++;
}
void Player::checkWall(sf::RectangleShape& wall)
{
	sf::FloatRect HitBox = getHitbox();
	sf::FloatRect wallBox = wall.getGlobalBounds();
	if (Collision::intersects(HitBox, wallBox))
	{
		if (HitBox.left < wallBox.left)
		{
			x = wallBox.left - HitBox.width;
		}
		else
		{
			x = wallBox.left + wallBox.width;
		}
		player.setPosition(x, y);
	}
}
void Player::respawn()
{
	x = spawnX;
	y = spawnY;
	vx = 0;
	vy = 0;
	player.setPosition(x, y);
}
void Player::setPosition(float playerX, float playerY)
{
	x = playerX;
	y = playerY;
}
void Player::setControls(sf::Keyboard::Key l, sf::Keyboard::Key r, sf::Keyboard::Key j, sf::Keyboard::Key s)
{
	left = l;
	right = r;
	jump = j;
	shoot = s;
}
void Player::setDirection(int direction)
{
	facing = direction;
}
void Player::setDistancePower(bool val)
{
	distancePower = val;
}
void Player::activateSpeed(int time, float newSpeed)
{
	speed = newSpeed;
	speedTime = time;
	speedOn = true;
}
void Player::activateBalloon(int time, float newGravity)
{
	gravity = newGravity;
	balloonTime = time;
	balloonOn = true;
}