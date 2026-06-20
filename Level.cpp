#include "Levels.h"
#include "Gem.h"
#include <iostream>
using namespace std;
//Base Level
sf::Texture Level::starTexture;
Level::Level()
{
    platCount = 0;
    enemyCount = 0;
    wallCount = 0;
    gameOver = false;
    levelComplete = false;
    starCount = 0;
    starsSpawned = false;
    starLevel = false;
}
void Level::spawnStars()
{
    starCount = 5;
    for (int i = 0; i < starCount; i++)
    {
        stars[i].setRadius(16.f);
        stars[i].setTexture(&starTexture);
        stars[i].setOrigin(16.f, 16.f);
        float spacing = 120.f;
        float startX = 100.f;
        stars[i].setPosition(startX + i * spacing, 560.f);
    }
}
void Level::spawnPlayers(Player& p1, Player& p2)
{
    p1.setPosition(50, 530);
    p2.setPosition(730, 530);
    p1.setDirection(1);
    p2.setDirection(-1);
}
Level::~Level()
{
    for (int i = 0; i < enemyCount; i++)
    {
        delete enemies[i];
    }
    for (int i = 0; i < gemCount; i++)
    {
        delete gems[i];
    }
}
void Level::load(Player& p1, Player& p2, ScoreSystem* score)
{
    player1 = &p1;
    player2 = &p2;
    scoreSystem = score;
    spawnPlayers(p1, p2);
    starsSpawned = false;
    starCount = 0;
    starLevel = false;
    levelComplete = false;
    gameOver = false;
    walls[wallCount].setSize(sf::Vector2f(20.f, 600.f));
    walls[wallCount].setPosition(0.f, 0.f);
    walls[wallCount].setFillColor(sf::Color::Magenta);
    wallCount++;
    walls[wallCount].setSize(sf::Vector2f(20.f, 600.f));
    walls[wallCount].setPosition(780.f, 0.f);
    walls[wallCount].setFillColor(sf::Color::Magenta);
    wallCount++;
    platforms[platCount].setSize(sf::Vector2f(760.f, 20.f));
    platforms[platCount].setPosition(20.f, 580.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    if (!platformTexture.loadFromFile("SnowBrosAssets/Images/Platforms.png"))
    {
        cout << "Platform image failed to load" << endl;
    }
    platformTexture.setRepeated(true);
    if (!wallTexture.loadFromFile("SnowBrosAssets/Images/Platforms.png"))
    {
        cout << "Wall image failed to load" << endl;
    }
    wallTexture.setRepeated(true);
    if (!backgroundTexture.loadFromFile("SnowBrosAssets/Images/background.png"))
    {
        std::cout << "Background failed to load\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    float X = 800.0f / backgroundTexture.getSize().x;
    float Y = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(X, Y);
    if (starTexture.getSize().x == 0)
    {
        starTexture.loadFromFile("SnowBrosAssets/Images/star.png");
    }
}
void Level::update(Player& p1, Player& p2)
{
    for (int i = 0; i < platCount; i++)
    {
        p1.checkPlatform(platforms[i]);
        p2.checkPlatform(platforms[i]);
    }
    for (int i = 0; i < wallCount; i++)
    {
        p1.checkWall(walls[i]);
        p2.checkWall(walls[i]);
    }
    if (p1.getSnowball() != nullptr && p1.getSnowball()->getIsActive())
    {
        for (int k = 0; k < platCount; k++)
        {
            if (Collision::intersects(p1.getSnowball()->getHitBox(), platforms[k].getGlobalBounds()))
            {
                p1.getSnowball()->onPlatform();
                break;
            }
        }
    }
    if (p2.getSnowball() != nullptr && p2.getSnowball()->getIsActive())
    {
        for (int k = 0; k < platCount; k++)
        {
            if (Collision::intersects(p2.getSnowball()->getHitBox(), platforms[k].getGlobalBounds()))
            {
                p2.getSnowball()->onPlatform();
                break;
            }
        }
    }
    if (p1.getSnowball() != nullptr && p1.getSnowball()->getIsActive())
    {
        for (int k = 0; k < wallCount; k++)
        {
            if (Collision::intersects(p1.getSnowball()->getHitBox(), walls[k].getGlobalBounds()))
            {
                p1.getSnowball()->onPlatform();
                break;
            }
        }
    }
    if (p2.getSnowball() != nullptr && p2.getSnowball()->getIsActive())
    {
        for (int k = 0; k < wallCount; k++)
        {
            if (Collision::intersects(p2.getSnowball()->getHitBox(), walls[k].getGlobalBounds()))
            {
                p2.getSnowball()->onPlatform();
                break;
            }
        }
    }
    for (int i = 0; i < enemyCount; i++)
    {
        enemies[i]->update();
        if (enemies[i]->shouldSpawn())
        {
            if (enemyCount < 6)
            {
                Enemy* child = enemies[i]->spawnChild();
                if (child && enemyCount < 20)
                {
                    enemies[enemyCount++] = child;
                }
            }
        }
        enemies[i]->attack(p1.getHitbox().left, p1.getHitbox().top);
        if (enemies[i]->getKnife() != nullptr && enemies[i]->getKnife()->getIsActive())
        {
            if (Collision::intersects(enemies[i]->getKnife()->getHitBox(), p1.getHitbox()))
            {
                p1.loseLife();
                enemies[i]->getKnife()->onHit();
            }
            else if (Collision::intersects(enemies[i]->getKnife()->getHitBox(), p2.getHitbox()))
            {
                p2.loseLife();
                enemies[i]->getKnife()->onHit();
            }
            if (enemies[i]->getKnife() != nullptr && enemies[i]->getKnife()->getIsActive())
            {
                for (int j = 0; j < wallCount; j++)
                {
                    if (Collision::intersects(enemies[i]->getKnife()->getHitBox(), walls[j].getGlobalBounds()))
                    {
                        enemies[i]->getKnife()->onHit();
                        break;
                    }
                }
            }
            if (enemies[i]->getKnife() != nullptr && enemies[i]->getKnife()->getIsActive())
            {
                for (int j = 0; j < platCount; j++)
                {
                    if (Collision::intersects(enemies[i]->getKnife()->getHitBox(), platforms[j].getGlobalBounds()))
                    {
                        enemies[i]->getKnife()->onHit();
                        break;
                    }
                }
            }
        }
        for (int j = 0; j < platCount; j++)
        {
            enemies[i]->checkPlatform(platforms[j]);
        }
        for (int j = 0; j < wallCount; j++)
        {
            enemies[i]->checkWall(walls[j]);
        }
        if (p1.getSnowball() != nullptr && p1.getSnowball()->getIsActive())
        {
            if (Collision::intersects(p1.getSnowball()->getHitBox(), enemies[i]->getHitBox()))
            {
                if (p1.getSnowballPower())
                {
                    enemies[i]->setSnowPower(2);
                }
                else
                {
                    enemies[i]->setSnowPower(1);
                }
                enemies[i]->gotHit();
                enemies[i]->setDecayTimer();
                enemies[i]->setKilledBy(1);
                p1.getSnowball()->onHit();
            }
        }
        if (p2.getSnowball() != nullptr && p2.getSnowball()->getIsActive())
        {
            if (Collision::intersects(p2.getSnowball()->getHitBox(), enemies[i]->getHitBox()))
            {
                if (p2.getSnowballPower())
                {
                    enemies[i]->setSnowPower(2);
                }
                else
                {
                    enemies[i]->setSnowPower(1);
                }
                enemies[i]->gotHit();
                enemies[i]->setDecayTimer();
                enemies[i]->setKilledBy(2);
                p2.getSnowball()->onHit();
            }
        }
        for (int j = 0; j < platCount; j++)
        {
            enemies[i]->checkPlatform(platforms[j]);
        }
        if (Collision::intersects(p1.getHitbox(), enemies[i]->getHitBox()))
        {
            if (enemies[i]->getIsEncased() && !enemies[i]->getIsRolling())
            {
                if (p1.getHitbox().left < enemies[i]->getHitBox().left)
                {
                    enemies[i]->startRolling(1);
                    enemies[i]->setKilledBy(1);
                }
                else
                {
                    enemies[i]->startRolling(-1);
                    enemies[i]->setKilledBy(1);
                }
            }
            else if (!enemies[i]->getIsRolling())
            {
                p1.loseLife();
            }
        }
        if (Collision::intersects(p2.getHitbox(), enemies[i]->getHitBox()))
        {
            if (enemies[i]->getIsEncased() && !enemies[i]->getIsRolling())
            {
                if (p2.getHitbox().left < enemies[i]->getHitBox().left)
                {
                    enemies[i]->startRolling(1);
                    enemies[i]->setKilledBy(2);
                }
                else
                {
                    enemies[i]->startRolling(-1);
                    enemies[i]->setKilledBy(2);
                }
            }
            else if (!enemies[i]->getIsRolling())
            {
                p2.loseLife();
            }
        }
        if (enemies[i]->getIsRolling())
        {
            for (int j = 0; j < enemyCount; j++)
            {
                if (i != j && enemies[j]->isAlive())
                {
                    if (Collision::intersects(enemies[i]->getHitBox(), enemies[j]->getHitBox()))
                    {
                        enemies[j]->becomeEncased();
                        enemies[j]->startRolling(enemies[i]->getDirection());
                        enemies[j]->setKilledBy(enemies[i]->getKilledBy());
                    }
                }
            }
        }
    }
    if (starLevel)
    {
        for (int i = 0; i < starCount; i++)
        {
            if (stars[i].getRadius() > 0)
            {
                if (Collision::intersects(p1.getHitbox(), stars[i].getGlobalBounds()))
                {
                    stars[i].setRadius(0);
                }
                else if (Collision::intersects(p2.getHitbox(), stars[i].getGlobalBounds()))
                {
                    stars[i].setRadius(0);
                }
            }
        }
    }
    for (int i = 0; i < enemyCount; i++)
    {
        if (!enemies[i]->isAlive())
        {
            scoreSystem->enemyKilled(enemies[i]->getKilledBy(), enemies[i]->getScore());
            delete enemies[i];
            for (int j = i; j < enemyCount - 1; j++)
            {
                enemies[j] = enemies[j + 1];
            }
            enemyCount--;
            i--;
        }
    }
    for (int i = 0; i < gemCount; i++)
    {
        if (!gems[i]->isCollected())
        {
            if (Collision::intersects(p1.getHitbox(), gems[i]->getHitBox()))
            {
                gems[i]->collect();
                scoreSystem->gems(1, 10);
            }
            else if (Collision::intersects(p2.getHitbox(), gems[i]->getHitBox()))
            {
                gems[i]->collect();
                scoreSystem->gems(2, 10);
            }
        }
    }
    static int gemTimer = 0;
    static bool timerActive = true;
    if (!levelComplete && !gameOver) {
        gemTimer++;
        if (gemTimer >= 300 && gemCount < 20) {
            float gemX = 100 + (rand() % 600);
            gems[gemCount++] = new Gem(gemX, 560.f);
            gemTimer = 0;
        }
    }
    if (levelComplete || gameOver) {
        gemTimer = 0;
    }
    if (starLevel && enemyCount == 0 && !starsSpawned)
    {
        spawnStars();
        starsSpawned = true;
    }
    if (starLevel && starsSpawned)
    {
        bool allCollected = true;

        for (int i = 0; i < starCount; i++)
        {
            if (stars[i].getRadius() > 0)
            {
                allCollected = false;
                break;
            }
        }
        if (allCollected && !levelComplete)
        {
            levelComplete = true;
            p1.activateSpeed(1300, 7.5f);
            p1.setSnowballPower(true);
            p2.activateSpeed(1300, 7.5f);
            p2.setSnowballPower(true);
        }
    }
    if (!starLevel)
    {
        if (enemyCount == 0 && !levelComplete)
        {
            levelComplete = true;
            p1.setSnowballPower(false);
            p1.setDistancePower(false);
            p2.setSnowballPower(false);
            p2.setDistancePower(false);
            cout << "Level Complete" << endl;
        }
    }
    if ((p1.getLives() <= 0 && p2.getLives() <= 0) && !gameOver)
    {
        gameOver = true;
        cout << "You LOSE" << endl;
    }
}
void Level::draw(sf::RenderWindow& window)
{
    window.draw(backgroundSprite);
    for (int i = 0; i < platCount; i++)
    {
        sf::Sprite platformSprite;
        platformSprite.setTexture(platformTexture);
        sf::Vector2f size = platforms[i].getSize();
        platformSprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
        platformSprite.setPosition(platforms[i].getPosition());
        window.draw(platformSprite);
        if (starLevel)
        {
            for (int i = 0; i < starCount; i++)
            {
                if (stars[i].getRadius() > 0)
                {
                    window.draw(stars[i]);
                }
            }
        }
    }
    for (int i = 0; i < enemyCount; i++)
    {
        enemies[i]->draw(window);
    }
    for (int i = 0; i < gemCount; i++)
    {
        gems[i]->draw(window);
    }
    for (int i = 0; i < wallCount; i++)
    {
        sf::Sprite wallSprite;
        wallSprite.setTexture(wallTexture);
        sf::Vector2f size = walls[i].getSize();
        wallSprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
        wallSprite.setPosition(walls[i].getPosition());
        window.draw(wallSprite);
    }
    player1->draw(window);
    if (player2 != player1) {
        player2->draw(window);
    }
}
bool Level::isLevelComplete() const
{
    return levelComplete;
}
bool Level::isGameOver() const
{
    return gameOver;
}
//Level 1
void Level1::spawnEnemies()
{
}
void Level1::load(Player& p1, Player& p2, ScoreSystem* score)
{
    platCount = 0;
    enemyCount = 0;
    wallCount = 0;
    gemCount = 0;
    Level::load(p1, p2, score);

    platforms[platCount].setSize(sf::Vector2f(320.f, 20.f));
    platforms[platCount].setPosition(240.f, 130.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(30.f, 220.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(550.f, 220.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(240.f, 20.f));
    platforms[platCount].setPosition(280.f, 310.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(30.f, 395.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(550.f, 395.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(240.f, 20.f));
    platforms[platCount].setPosition(280.f, 480.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    Enemy* topLeft = EnemyFactory::create("Botom", 250.f, 90.f, 1.0f);
    if (topLeft)
    {
        topLeft->setDirection(1);
        enemies[enemyCount++] = topLeft;
    }
    Enemy* topRight = EnemyFactory::create("Botom", 540.f, 90.f, 1.0f);
    if (topRight)
    {
        topRight->setDirection(-1);
        enemies[enemyCount++] = topRight;
    }
    Enemy* midLeft = EnemyFactory::create("Botom", 40.f, 180.f, 1.0f);
    if (midLeft)
    {
        midLeft->setDirection(1);
        enemies[enemyCount++] = midLeft;
    }
    Enemy* midRight = EnemyFactory::create("Botom", 750.f, 180.f, 1.0f);
    if (midRight)
    {
        midRight->setDirection(-1);
        enemies[enemyCount++] = midRight;
    }
}
//Level2
void Level2::load(Player& p1, Player& p2, ScoreSystem* score)
{
    platCount = 0;
    enemyCount = 0;
    wallCount = 0;
    gemCount = 0;
    Level::load(p1, p2, score);

    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(30.f, 130.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(550.f, 130.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(130.f, 220.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(180.f, 20.f));
    platforms[platCount].setPosition(620.f, 220.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(240.f, 20.f));
    platforms[platCount].setPosition(370.f, 310.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(180.f, 20.f));
    platforms[platCount].setPosition(0.f, 395.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(220.f, 20.f));
    platforms[platCount].setPosition(550.f, 395.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(340.f, 20.f));
    platforms[platCount].setPosition(250.f, 480.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    spawnEnemies();
}
void Level2::spawnEnemies()
{
    Enemy* left = EnemyFactory::create("Botom", 250.f, 90.f, 1.5f);
    Enemy* right = EnemyFactory::create("Botom", 650.f, 90.f, 1.5f);
    Enemy* ff = EnemyFactory::create("FlyngFoogaFoog", 400.f, 90.f, 1.5f);
    if (left)
    {
        left->setDirection(-1);
        enemies[enemyCount++] = left;
    }
    if (right)
    {
        right->setDirection(1);
        enemies[enemyCount++] = right;
    }
    if (ff)
    {
        enemies[enemyCount++] = ff;
    }
}
//Level 3
void Level3::load(Player& p1, Player& p2, ScoreSystem* score)
{
    platCount = 0;
    enemyCount = 0;
    wallCount = 0;
    gemCount = 0;
    Level::load(p1, p2, score);

    platforms[platCount].setSize(sf::Vector2f(340.f, 20.f));
    platforms[platCount].setPosition(230.f, 140.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(120.f, 20.f));
    platforms[platCount].setPosition(0.f, 170.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(120.f, 20.f));
    platforms[platCount].setPosition(680.f, 170.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(560.f, 20.f));
    platforms[platCount].setPosition(120.f, 260.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(120.f, 20.f));
    platforms[platCount].setPosition(0.f, 330.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(120.f, 20.f));
    platforms[platCount].setPosition(680.f, 330.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(160.f, 20.f));
    platforms[platCount].setPosition(110.f, 400.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(160.f, 20.f));
    platforms[platCount].setPosition(320.f, 400.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(160.f, 20.f));
    platforms[platCount].setPosition(530.f, 400.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(80.f, 20.f));
    platforms[platCount].setPosition(0.f, 490.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(80.f, 20.f));
    platforms[platCount].setPosition(700.f, 490.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(400.f, 20.f));
    platforms[platCount].setPosition(190.f, 490.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    spawnEnemies();
}
void Level3::spawnEnemies()
{
    Enemy* botom = EnemyFactory::create("Botom", 350.f, 90.f, 1.5f);
    Enemy* ff = EnemyFactory::create("FlyngFoogaFoog", 400.f, 170.f, 1.5f);
    Enemy* tornado = EnemyFactory::create("Tornado", 450.f, 90.f, 2.0f);
    if (botom)
    {
        botom->setDirection(-1);
        enemies[enemyCount++] = botom;
    }
    if (ff)
    {
        enemies[enemyCount++] = ff;
    }
    if (tornado)
    {
        tornado->setDirection(1);
        enemies[enemyCount++] = tornado;
    }
}
//Level 4
void Level4::load(Player& p1, Player& p2, ScoreSystem* score)
{
    platCount = 0;
    enemyCount = 0;
    wallCount = 0;
    gemCount = 0;
    Level::load(p1, p2, score);
    starLevel = true;

    platforms[platCount].setSize(sf::Vector2f(350.f, 20.f));
    platforms[platCount].setPosition(0.f, 500.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(350.f, 20.f));
    platforms[platCount].setPosition(450.f, 500.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(250.f, 20.f));
    platforms[platCount].setPosition(700.f, 350.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(250.f, 20.f));
    platforms[platCount].setPosition(700.f, 190.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(350.f, 20.f));
    platforms[platCount].setPosition(0.f, 420.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(350.f, 20.f));
    platforms[platCount].setPosition(450.f, 420.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(280.f, 20.f));
    platforms[platCount].setPosition(280.f, 150.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(380.f, 20.f));
    platforms[platCount].setPosition(70.f, 240.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(280.f, 20.f));
    platforms[platCount].setPosition(280.f, 330.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(80.f, 20.f));
    platforms[platCount].setPosition(70.f, 330.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(110.f, 20.f));
    platforms[platCount].setPosition(550.f, 270.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    walls[wallCount].setSize(sf::Vector2f(20.f, 90.f));
    walls[wallCount].setPosition(sf::Vector2f(70.f, 240.f));
    walls[wallCount].setFillColor(sf::Color::Magenta);
    wallCount++;
    walls[wallCount].setSize(sf::Vector2f(20.f, 200.f));
    walls[wallCount].setPosition(sf::Vector2f(550.f, 150.f));
    walls[wallCount].setFillColor(sf::Color::Magenta);
    wallCount++;
    spawnEnemies();
}
void Level4::spawnEnemies()
{
    Enemy* left = EnemyFactory::create("Tornado", 450.f, 90.f, 2.0f);
    Enemy* right = EnemyFactory::create("Tornado", 350.f, 90.f, 2.0f);
    if (left)
    {
        left->setDirection(-1);
        enemies[enemyCount++] = left;
    }
    if (right)
    {
        right->setDirection(1);
        enemies[enemyCount++] = right;
    }
}
//Level 5
void Level5::spawnEnemies()
{
    Enemy* boss = EnemyFactory::create("Mogera", 550.f, 110.f, 0.f);

    if (boss)
    {
        enemies[enemyCount++] = boss;
    }
}
void Level5::load(Player& p1, Player& p2, ScoreSystem* score)
{
    platCount = 0;
    enemyCount = 0;
    wallCount = 0;
    gemCount = 0;
    Level::load(p1, p2, score);
    backgroundTexture.loadFromFile("SnowBrosAssets/Images/mogera_bg.png");
    float X = 800.0f / backgroundTexture.getSize().x;
    float Y = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(X, Y);
    platforms[platCount].setSize(sf::Vector2f(200.f, 20.f));
    platforms[platCount].setPosition(100.f, 320.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(500.f, 20.f));
    platforms[platCount].setPosition(450.f, 320.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(500.f, 20.f));
    platforms[platCount].setPosition(450.f, 420.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(200.f, 20.f));
    platforms[platCount].setPosition(100.f, 400.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(140.f, 20.f));
    platforms[platCount].setPosition(260.f, 490.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    platforms[platCount].setSize(sf::Vector2f(140.f, 20.f));
    platforms[platCount].setPosition(420.f, 540.f);
    platforms[platCount].setFillColor(sf::Color::Magenta);
    platCount++;
    spawnEnemies();
}
//Level 6
void Level6::load(Player& p1, Player& p2, ScoreSystem* score)
{
    Level1::load(p1, p2, score);
    backgroundTexture.loadFromFile("SnowBrosAssets/Images/background2.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    enemyCount = 0;
    Enemy* e1 = EnemyFactory::create("Botom", 250.f, 90.f, 1.5f);
    if (e1)
    {
        e1->setDirection(1);
        enemies[enemyCount++] = e1;
    }
    Enemy* e2 = EnemyFactory::create("Botom", 540.f, 90.f, 1.5f);
    if (e2)
    {
        e2->setDirection(-1);
        enemies[enemyCount++] = e2;
    }
    Enemy* e3 = EnemyFactory::create("Botom", 40.f, 180.f, 1.5f);
    if (e3)
    {
        e3->setDirection(1);
        enemies[enemyCount++] = e3;
    }
    Enemy* ff = EnemyFactory::create("FlyngFoogaFoog", 400.f, 90.f, 1.5f);
    if (ff)
    {
        enemies[enemyCount++] = ff;
    }
}
//Level 7
void Level7::load(Player& p1, Player& p2, ScoreSystem* score)
{
    Level2::load(p1, p2, score);
    backgroundTexture.loadFromFile("SnowBrosAssets/Images/background2.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    enemyCount = 0;
    Enemy* ff1 = EnemyFactory::create("FlyngFoogaFoog", 250.f, 90.f, 1.5f);
    if (ff1)
    {
        enemies[enemyCount++] = ff1;
    }
    Enemy* ff2 = EnemyFactory::create("FlyngFoogaFoog", 650.f, 90.f, 1.5f);
    if (ff2)
    {
        enemies[enemyCount++] = ff2;
    }
    Enemy* tornado = EnemyFactory::create("Tornado", 300.f, 170.f, 2.0f);
    if (tornado)
    {
        tornado->setDirection(1);
        enemies[enemyCount++] = tornado;
    }
}
//Level 8
void Level8::load(Player& p1, Player& p2, ScoreSystem* score)
{
    Level3::load(p1, p2, score);
    backgroundTexture.loadFromFile("SnowBrosAssets/Images/background2.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    enemyCount = 0;
    Enemy* ff = EnemyFactory::create("FlyngFoogaFoog", 350.f, 90.f, 1.5f);
    if (ff)
    {
        enemies[enemyCount++] = ff;
    }
    Enemy* tornado1 = EnemyFactory::create("Tornado", 400.f, 170.f, 2.5f);
    if (tornado1)
    {
        tornado1->setDirection(-1);
        enemies[enemyCount++] = tornado1;
    }
    Enemy* tornado2 = EnemyFactory::create("Tornado", 450.f, 90.f, 2.5f);
    if (tornado2)
    {
        tornado2->setDirection(1);
        enemies[enemyCount++] = tornado2;
    }
}
//Level 9
void Level9::load(Player& p1, Player& p2, ScoreSystem* score)
{
    Level4::load(p1, p2, score);
    backgroundTexture.loadFromFile("SnowBrosAssets/Images/background2.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
    enemyCount = 0;
    Enemy* t1 = EnemyFactory::create("Tornado", 350.f, 90.f, 2.5f);
    if (t1)
    {
        t1->setDirection(-1);
        enemies[enemyCount++] = t1;
    }
    Enemy* t2 = EnemyFactory::create("Tornado", 450.f, 90.f, 2.5f);
    if (t2)
    {
        t2->setDirection(1);
        enemies[enemyCount++] = t2;
    }
    Enemy* t3 = EnemyFactory::create("Tornado", 400.f, 170.f, 2.5f);
    if (t3)
    {
        t3->setDirection(-1);
        enemies[enemyCount++] = t3;
    }
}
//Level 10
void Level10::load(Player& p1, Player& p2, ScoreSystem* score)
{
    Level5::load(p1, p2, score);
    enemyCount = 0;
    spawnEnemies();
    backgroundTexture.loadFromFile("SnowBrosAssets/Images/Gamakichi-bg.png");
    backgroundSprite.setTexture(backgroundTexture);
    float scaleX = 800.0f / backgroundTexture.getSize().x;
    float scaleY = 600.0f / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
}
void Level10::spawnEnemies()
{
    Enemy* boss = EnemyFactory::create("Gamakichi", 550.f, 110.f, 0.f);

    if (boss)
    {
        enemies[enemyCount++] = boss;
    }
}