#include "LevelManager.h"

LevelManager::LevelManager()
{
    levels[0] = &level1;
    levels[1] = &level2;
    levels[2] = &level3;
    levels[3] = &level4;
    levels[4] = &level5;
    levels[5] = &level6;
    levels[6] = &level7;
    levels[7] = &level8;
    levels[8] = &level9;
    levels[9] = &level10;
    index = 0;
    currentLevel = levels[index];

}

void LevelManager::load(Player& p1, Player& p2, ScoreSystem* score) {
    scoreSystem = score;
    levels[index]->load(p1, p2, scoreSystem);
}

void LevelManager::update(Player& p1, Player& p2)
{
    currentLevel->update(p1, p2);
}

bool LevelManager::isLevelComplete() const {
    return currentLevel->isLevelComplete();
}

void LevelManager::setLevel(int lvl) {
    index = lvl - 1;
    currentLevel = levels[index];
}
void LevelManager::draw(sf::RenderWindow& window)
{
    currentLevel->draw(window);
}

bool LevelManager::isGameOver()
{
    return (currentLevel->gameOver || index > 9);
}

void LevelManager::nextLevel(Player& p1, Player& p2) {
    index++;
    currentLevel = levels[index];
    levels[index]->load(p1, p2, scoreSystem);

}

int LevelManager::getCurrentIndex() const {
    return index;
}