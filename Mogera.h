#include "Enemy.h"
#include "EnemyFactory.h"
class Mogera : public Enemy {
protected:
    static sf::Texture MogeraTexture;
    sf::Sprite MogeraSprite;
    int attackTime;
    bool spawnReady;
    int spawnBotom;
    int spawnFlyng;
    int spawnTornado;
    int frame;
    int timer;
    int delay;
    bool flash;
    int flashTime;
public:
    Mogera(float startX, float startY, float speed);
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void checkPlatform(sf::RectangleShape& platform) override {}
    void checkWall(sf::RectangleShape& wall) override {}
    void setDirection(int dir) override { direction = dir; }
    bool shouldSpawn() const { return spawnReady; }
    int getSpawnBotom() const { return spawnBotom; }
    int getSpawnFlyng() const { return spawnFlyng; }
    int getSpawnTornado() const { return spawnTornado; }
    void resetSpawn() { spawnReady = false; }
    Enemy* spawnChild() override;
    void gotHit() override;
};