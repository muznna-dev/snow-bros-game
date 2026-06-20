#pragma once
#include "Screen.h"
#include "UIElements.h"
#include "LoginSystem.h"
#include <SFML/Graphics.hpp>

class LoginScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	LoginSystem& loginSystem;
	TextBox usernameBox;
	TextBox pwBox;

	TextBox usernameBox2;
	TextBox pwBox2;

	Button loginbtn;
	Button registerbtn;
	sf::Text titleText;
	sf::Text msgText;
	sf::Text p1Label;
	sf::Text p2Label;

	bool correctLogin;
	string loggedInUsername;
	string loggedInUsername2;

	bool isMultiMode;

	sf::Texture* bgTexture;
	sf::Sprite bgSprite;

public:
	void reset();
	LoginScreen(sf::RenderWindow& win, sf::Font& f, LoginSystem& ls, sf::Texture* bgTex);
	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	bool login() const;
	string getLoggedInUser() const;
	string getLoggedInUser2() const;
	void setMultiMode(bool multi);
};

class MainMenuScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* btnTexture;
	sf::Texture* bgTexture;
	sf::Sprite bgSprite;
	sf::Text title;
	sf::Text usernameLayout;
	Button newGamebtn;
	Button continuebtn;
	Button shopbtn;
	Button Leaderboardbtn;
	Button logoutbtn;
	string currentUser;
	string currentUser2;
	int buttonNumber;
	bool multi;
public:
	MainMenuScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btnTex,
		sf::Texture* bgTex, const string& username,
		string& username2, bool isMulti);

	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;

	int getButtonClicked() const;
	void resetButtonClicked();
};

class PauseScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* btnTexture;
	sf::RectangleShape overlay;
	sf::Text pTitle;
	Button resumebtn;
	Button mainMenubtn;
	int btnNumber;
public:
	PauseScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btnTex);

	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;

	int getButtonClicked() const;
	void resetButtonClicked();
};

class LeaderboardScreen :public Screen {
private:
	sf::RenderWindow& window;
	sf::Font& font;
	sf::Texture* btnTexture;
	sf::Texture* bgTexture;
	sf::Sprite bgSprite;
	sf::Text top[10];
	Button backbtn;
	int count;
	bool backPressed;
public:
	LeaderboardScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btnTex,
		sf::Texture* bgTex);

	void setup() override;
	void handleEvents(const sf::Event& event) override;
	void update() override;
	void draw() override;
	void resetBackButton();
	void loadLeaderboard();
	bool isBackClicked() const;

};
