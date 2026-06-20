#include "Gamakichi.h"
sf::Texture Gamakichi::MogeraTexture;
Gamakichi::Gamakichi(float x, float y, float speed)
    : Enemy(x, y, 200, 200, 50, 0)
{
    if (MogeraTexture.getSize().x == 0)
    {
        MogeraTexture.loadFromFile("SnowBrosAssets/Images/Gamakichi.png");
    }
    MogeraSprite.setTexture(MogeraTexture);
    MogeraSprite.setTextureRect(sf::IntRect(67, 0, 1234, 641));
    MogeraSprite.setOrigin(617, 270);
    MogeraSprite.setScale(0.3f, 0.3f);
    attackTime = 0;
    spawnReady = false;
    spawnBotom = 1;
    spawnFlyng = 0;
    spawnTornado = 0;
    frame = 0;
    timer = 0;
    delay = 10;
    flash = false;
    flashTime = 0;
}
void Gamakichi::update()
{
    attackTime++;
    if (attackTime >= 120)
    {
        spawnReady = true;
        attackTime = 0;
    }
    timer++;
    if (timer >= delay)
    {
        frame++;
        if (frame > 1)
        {
            frame = 0;
        }
        timer = 0;
    }
    if (frame == 0)
    {
        MogeraSprite.setTextureRect(sf::IntRect(67, 0, 1234, 641));
    }
    else if (frame == 1)
    {
        MogeraSprite.setTextureRect(sf::IntRect(1300, 0, 1234, 641));
    }
    if (flash)
    {
        flashTime++;
        MogeraSprite.setColor(sf::Color(255, 100, 100));
        if (flashTime >= 20)
        {
            flash = false;
            MogeraSprite.setColor(sf::Color::White);
        }
    }
}
void Gamakichi::draw(sf::RenderWindow& window) {
    MogeraSprite.setPosition(x + width / 2, y + height / 2);
    window.draw(MogeraSprite);
}
Enemy* Gamakichi::spawnChild()
{
    spawnReady = false;
    Enemy* child = EnemyFactory::create("Tornado", x, y + height, 1.5f);
    if (child)
    {
        child->setDirection(-1);
        child->skipSpawnDelay();
    }
    return child;
}
void Gamakichi::gotHit()
{
    health--;
    flash = true;
    flashTime = 0;
    if (health <= 0)
    {
        alive = false;
    }
}