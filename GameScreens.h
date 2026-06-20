#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "UIElements.h"
#include "Shop.h"
#include<string>

using namespace std;

class SplashScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Text logo;
	sf::RectangleShape load;
	sf::RectangleShape fullLoad;
	sf::Clock time;
	float progress;
	bool complete;
	sf::Texture* bgTex;
	sf::Sprite bg;
public:
	SplashScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	bool isComplete();

};


class LevelChoiceScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* bgTex;
	sf::Texture* btnTex;
	sf::Text heading;
	sf::Text progress;
	sf::Sprite bg;
	bool unlocked[10];
	int max;
	Button levelBtns[10];
	int chosen;
	Button backBtn;

public:

	LevelChoiceScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg, sf::Texture* btn);
	void setup() override;
	int getChosenLevel() const;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	void setMaxLevel(int level);
	bool backClicked() const;
	void resetChoice();
};

class ShopScreen : public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* bgTex;
	sf::Texture* btnTex;
	sf::Text items[5];
	sf::Text price[5];
	sf::Text itemCounts[5];
	Button buy[5];
	sf::Sprite bg;
	sf::Text heading;
	sf::Text gemDisplay;
	Button exitBtn;
	int itemsBought;
	Shop* shop;
	bool multi;
	bool msgBox;
	int pendingItemIndex;
	Button player1ChoiceBtn;
	Button player2ChoiceBtn;
	sf::RectangleShape popupOverlay;
	sf::Text popupText;

public:
	ShopScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg, sf::Texture* btn);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;

	int getBoughtItem() const;
	bool exitClicked() const;
	void resetExit();
	void setShop(Shop* s, bool m);
	void refreshDisplay();
};
class HUDScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	int lives;
	int score;
	int level;
	sf::Text livesLayout;
	sf::Text scoreLayout;
	sf::Text levelLayout;
	bool multi;
	int lives2;
	int score2;
	sf::Text livesLayout2;
	sf::Text scoreLayout2;
public:
	HUDScreen(sf::RenderWindow& win, sf::Font& f);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	void setLives(int l);
	void setScore(int s);
	void setLevel(int lv);

	void setMulti(bool multiP);
	void setLives2(int l);
	void setScore2(int s);
};

class LevelCompleteScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	Button nextBtn;
	Button menuBtn;
	sf::Texture* btnTex;
	sf::Text title;
	sf::Text score;
	int finalScore;
	int level;
	int btnClicked;
	sf::Clock timer;
	float timeLeft;

	bool multi;
	sf::Text score2;
	int finalScore2;
public:
	bool goNext;
	LevelCompleteScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btn);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void setData(int level, int score);
	int getBtnClicked() const;
	void update() override;
	void draw() override;
	void setData2(int level, int score1, int score2);
	void setMulti(bool m);


};

class GameOverScreen :public Screen {
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* btnTex;
	Button menuBtn;
	sf::Text msg;
	sf::Text score;
	sf::Text level;
	int finalLevel;
	int finalScore;
	bool multi;
	sf::Text score2;
	int finalScore2;
public:
	GameOverScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btn);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	void setData(int score, int level);
	void setData2(int score1, int score2, int level);
	bool menuClicked() const;
	void setMulti(bool m);

};


class ModeChoiceScreen : public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* bgTex;
	sf::Texture* btnTex;
	sf::Sprite bg;
	sf::Text title;
	Button singleBtn;
	Button multiBtn;
	int choice;
public:
	ModeChoiceScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg, sf::Texture* btn);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	int getChoice() const;
	void resetChoice();
};