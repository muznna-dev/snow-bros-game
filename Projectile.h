//Updated
#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
protected:
	float x, y;
	float dirx, diry;
	float speed;
	bool isActive;
public:
	Projectile(float startX, float startY, float dX, float dY, float s);
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void onHit() = 0;
	bool getIsActive() const;
};

class Snowball :public Projectile {
private:
	static sf::Texture snowball;
	sf::Sprite snow;
public:
	Snowball(float x, float y, float dirx, float diry, float speed);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	void onHit() override;
	sf::FloatRect getHitBox() const;
	bool getIsActive() const;
	void onPlatform();
	void setActive(bool val);
};

class Knife : public Projectile {
private:
	float attackX;
	float attackY;
	static sf::Texture knifeTexture;
	sf::Sprite knifeSprite;
public:
	Knife(float x, float y, float attackX, float attackY, float speed);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	void onHit() override;
	sf::FloatRect getHitBox() const;
};

class Rocket : public Projectile {
private:
	float radius;
	bool hasExploded;
public:
	Rocket(float startX, float startY, float targetX, float targetY,
		float speed, float explosionRadius);
	void update() override;
	void draw(sf::RenderWindow& window) override;
	void onHit() override;
	bool getHasExploded() const;
	float getRadius()     const;
};