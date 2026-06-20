#pragma once
#include "Levels.h"
#include "Player.h"
class LevelManager
{
private:
    Level1 level1;
    Level2 level2;
    Level3 level3;
    Level4 level4;
    Level5 level5;
    Level6 level6;
    Level7 level7;
    Level8 level8;
    Level9 level9;
    Level10 level10;
    Level* levels[10];
    int index;
    Level* currentLevel;
    ScoreSystem* scoreSystem;
public:
    LevelManager();
    void load(Player& p1, Player& p2, ScoreSystem* score);
    void update(Player& p1, Player& p2);
    void draw(sf::RenderWindow& window);
    bool isGameOver();
    bool isLevelComplete() const;
    void nextLevel(Player& p1, Player& p2);
    int getCurrentIndex() const;
    void setLevel(int lvl);



};