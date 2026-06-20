#include"ScoreSystem.h"

stats::stats() {
	score = 0;
	gems = 0;
	lives = 2;
}
void stats::updateScore(int s) {
	score += s;
}
int stats::getScore() const {
	return score;
}
void stats::updateGems(int g) {
	gems += g;
}
void stats::lifeloss() {
	lives--;
}
void stats::lifeAdd() {
	lives++;
}
int stats::getLives() {
	return lives;
}

void stats::reset() {
	score = 0;
	gems = 0;
	lives = 2;
}

ScoreSystem::ScoreSystem(stats* st1, stats* st2) {
	s1 = st1;
	s2 = st2;
	if (st2 != nullptr)
		multi = true;
	else
		multi = false;

}
void ScoreSystem::enemyKilled(int player, int chain) {
	int score = 100;

	if (player == 1)
		s1->updateScore(score);
	else if (player == 2)
		s2->updateScore(score);

}
void ScoreSystem::gems(int player, int g) {
	if (player == 1)
		s1->updateGems(g);
	else if (player == 2)
		s2->updateGems(g);
}
void ScoreSystem::playerLoseLife(int player) {
	if (player == 1)
		s1->lifeloss();
	else if (player == 2 && multi)
		s2->lifeloss();
}
void ScoreSystem::BossDead(int player, int gems, int score) {
	if (player == 1)
	{
		s1->updateScore(score);
		s1->updateGems(gems);

	}
	else if (player == 2 && multi) {
		s2->updateScore(score);
		s2->updateGems(gems);
	}
}