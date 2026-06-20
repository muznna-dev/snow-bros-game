#include "Botom.h"
#include "Collision.h"
#include <iostream>
using namespace std;
sf::Texture Botom::enemyTexture;
sf::Texture Botom::snowTexture;
Botom::Botom(float x, float y, float spd)
	: Enemy(x, y, 40.0f, 40.0f, 2, spd)
{
	if (enemyTexture.getSize().x == 0)
	{
		enemyTexture.loadFromFile("SnowBrosAssets/Images/Botom_Pink.png");
	}
	enemySprite.setTexture(enemyTexture);
	enemySprite.setTextureRect(sf::IntRect(0, 220, 90, 90));
	enemySprite.setOrigin(50, 40);
	enemySprite.setScale(0.6f, 0.6f);
	if (snowTexture.getSize().x == 0)
	{
		snowTexture.loadFromFile("SnowBrosAssets/Images/Player_Red.png");
	}
	snowSprite.setTexture(snowTexture);
	snowSprite.setTextureRect(sf::IntRect(0, 880, 80, 80));
	snowSprite.setOrigin(40, 40);
	snowSprite.setScale(0.8f, 0.8f);
	frame = 0;
	timer = 0;
	delay = 10;
}
void Botom::update() {
	if (startTimer < 180)
	{
		startTimer++;
		vy += 0.5f;
		y += vy;
		enemySprite.setTextureRect(sf::IntRect(0, 135, 93, 95));
		if (direction == -1)
		{
			enemySprite.setScale(0.6f, 0.6f);
		}
		else
		{
			enemySprite.setScale(-0.6f, 0.6f);
		}
		return;
	}
	if (isRolling)
	{
		snowCoat = 3;
		snowSprite.setTextureRect(sf::IntRect(245, 880, 85, 87));
		x += direction * 10;
		vy += 0.5f;
		y += vy;
		if (y + height < 580)
		{
			if (x <= 20)
			{
				x = 20;
				direction = 1;
			}
			else if (x + width >= 780)
			{
				x = 780 - width;
				direction = -1;
			}
		}
		else
		{
			y = 580 - height;
			vy = 0;
			if (x + width < 20 || x > 780)
			{
				alive = false;
			}
		}
		return;
	}
	if (isEncased)
	{
		snowSprite.setTextureRect(sf::IntRect(245, 880, 85, 87));
		snowSprite.setOrigin(50, 40);
		snowSprite.setScale(0.8f, 0.8f);
	}
	if (snowCoat == 1)
	{
		snowSprite.setTextureRect(sf::IntRect(0, 880, 80, 80));
	}
	else if (snowCoat == 2)
	{
		snowSprite.setTextureRect(sf::IntRect(85, 880, 80, 80));
	}
	else if (snowCoat == 3)
	{
		snowSprite.setTextureRect(sf::IntRect(163, 880, 80, 80));
	}
	if (isEncased)
	{
		vy += 0.5f;
		y += vy;
		return;
	}
	if (snowCoat > 0 && snowCoat < 3)
	{
		isFrozen = true;
		snowDecayTimer++;
		if (snowDecayTimer >= snowDecay)
		{
			snowCoat--;
			snowDecayTimer = 0;
			if (snowCoat <= 0)
			{
				snowCoat = 0;
				isFrozen = false;
			}
		}
		vy += 0.5f;
		y += vy;
		return;
	}
	if (isFrozen)
	{
		vy += 0.5f;
		y += vy;
		return;
	}

	x += direction * speed;
	float gravity = 0.5f;
	vy += gravity;
	y += vy;
	if (x <= 20 || x + width >= 780) {
		direction *= -1;
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
	if (frame == 0)
	{
		enemySprite.setTextureRect(sf::IntRect(0, 365, 93, 90));
	}
	if (frame == 1)
	{
		enemySprite.setTextureRect(sf::IntRect(93, 365, 93, 90));
	}
	if (frame == 2)
	{
		enemySprite.setTextureRect(sf::IntRect(186, 365, 93, 90));
	}
	if (direction == -1)
	{
		enemySprite.setScale(0.6f, 0.6f);
	}
	else
	{
		enemySprite.setScale(-0.6f, 0.6f);
	}
}
void Botom::setDirection(int dir)
{
	direction = dir;
}
void Botom::checkPlatform(sf::RectangleShape& platform) {
	sf::FloatRect hitbox = getHitBox();
	sf::FloatRect platHitbox = platform.getGlobalBounds();

	if (Collision::isLandingOnPlatform(hitbox, vy, platHitbox)) {
		landOn(platHitbox.top - hitbox.height);
	}
}
void Botom::checkWall(sf::RectangleShape& wall)
{
	sf::FloatRect enemyBox = getHitBox();
	sf::FloatRect wallBox = wall.getGlobalBounds();
	if (Collision::intersects(enemyBox, wallBox))
	{
		if (!isRolling)
		{
			if (enemyBox.left < wallBox.left)
			{
				x = wallBox.left - width;
				direction = -1;
			}
			else
			{
				x = wallBox.left + wallBox.width;
				direction = 1;
			}
		}
		else
		{
			if (!(y + height >= 580))
			{
				if (enemyBox.left < wallBox.left)
				{
					x = wallBox.left - width;
					direction = -1;
				}
				else
				{
					x = wallBox.left + wallBox.width;
					direction = 1;
				}
			}
		}
	}
}
void Botom::draw(sf::RenderWindow& window) {
	enemySprite.setPosition(x + width / 2, y + height / 2);
	window.draw(enemySprite);
	if (snowCoat > 0)
	{
		snowSprite.setPosition(x + width / 2, y + height / 2);
		window.draw(snowSprite);
	}
}