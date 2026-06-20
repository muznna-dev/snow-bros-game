#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "Botom.h"
#include "FlyngFoogaFooga.h"
#include "ScoreSystem.h"
#include "EnemyFactory.h"
#include "Gem.h"
class Level
{
protected:
	Player* player1;
	Player* player2;
	sf::CircleShape stars[10];
	int starCount;
	bool starsSpawned;
	bool starLevel;
	void spawnStars();
	sf::RectangleShape platforms[20];
	int platCount;
	Enemy* enemies[10];
	int enemyCount;
	Gem* gems[20];
	int gemCount;
	ScoreSystem* scoreSystem;
	sf::RectangleShape walls[20];
	int wallCount;
	sf::Texture platformTexture;
	sf::Texture wallTexture;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	static sf::Texture starTexture;
public:
	Level();
	virtual ~Level();
	bool gameOver;
	bool levelComplete;
	virtual void load(Player& p1, Player& p2, ScoreSystem* score);
	virtual void update(Player& p1, Player& p2);
	virtual void draw(sf::RenderWindow& window);
	virtual void spawnEnemies() = 0;
	bool isLevelComplete() const;
	bool isGameOver() const;
	void spawnPlayers(Player& p1, Player& p2);
};
class Level1 : public Level
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
	void spawnEnemies() override;
};

class Level2 : public Level
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
	void spawnEnemies() override;
};

class Level3 : public Level
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
	void spawnEnemies() override;
};

class Level4 : public Level
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
	void spawnEnemies() override;
};

class Level5 : public Level
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
	void spawnEnemies() override;
};

class Level6 : public Level1
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
};

class Level7 : public Level2
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
};

class Level8 : public Level3
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
};

class Level9 : public Level4
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
};
class Level10 : public Level5
{
public:
	void load(Player& p1, Player& p2, ScoreSystem* score) override;
	void spawnEnemies() override;
};