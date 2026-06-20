#pragma once
#include<string>
#include<cstdlib>
#include<string>

using namespace std;
class stats {
private:
	int score;
	int gems;
	int lives;
public:
	stats();
	void updateScore(int s);
	int getScore() const;
	void updateGems(int g);
	void lifeloss();
	void lifeAdd();
	int getLives();

	void reset();


};

class ScoreSystem {
private:
	stats* s1;
	stats* s2;
	bool multi;
public:
	ScoreSystem(stats* st1, stats* st2);
	void enemyKilled(int player, int chain);
	void gems(int player, int g);
	void playerLoseLife(int player);
	void BossDead(int player, int gems, int score);
};