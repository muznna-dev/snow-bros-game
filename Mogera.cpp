#include "Mogera.h"
sf::Texture Mogera::MogeraTexture;
Mogera::Mogera(float x, float y, float speed)
    : Enemy(x, y, 200, 200, 50, 0)
{
    if (MogeraTexture.getSize().x == 0)
    {
        MogeraTexture.loadFromFile("SnowBrosAssets/Images/mogera2.png");
    }
    MogeraSprite.setTexture(MogeraTexture);
    MogeraSprite.setTextureRect(sf::IntRect(0, 0, 390, 400));
    MogeraSprite.setOrigin(195, 75);
    MogeraSprite.setScale(0.45f, 0.45f);
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
void Mogera::update()
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
        if (frame > 2)
        {
            frame = 0;
        }
        timer = 0;
    }
    if (frame == 0)
    {
        MogeraSprite.setTextureRect(sf::IntRect(0, 0, 390, 400));
    }
    else if (frame == 1)
    {
        MogeraSprite.setTextureRect(sf::IntRect(400, 0, 390, 370));
    }
    else if (frame == 2)
    {
        MogeraSprite.setTextureRect(sf::IntRect(790, 0, 390, 400));
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
void Mogera::draw(sf::RenderWindow& window) {
    MogeraSprite.setPosition(x + width / 2, y + height / 2);
    window.draw(MogeraSprite);
}
Enemy* Mogera::spawnChild()
{
    spawnReady = false;
    Enemy* child = EnemyFactory::create("Botom", x, y + height, 1.5f);
    if (child)
    {
        child->setDirection(-1);
        child->skipSpawnDelay();
    }
    return child;
}
void Mogera::gotHit()
{
    health--;
    flash = true;
    flashTime = 0;
    if (health <= 0)
    {
        alive = false;
    }
}