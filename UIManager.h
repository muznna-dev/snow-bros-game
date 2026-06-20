#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameScreens.h"
#include "MenuScreens.h"
#include "LoginSystem.h"
#include "ScoreSystem.h"
#include "LevelManager.h"
#include "Player.h"
#include "Shop.h"

class UIManager {
private:
    sf::RenderWindow& window;
    sf::Font& font;
    LoginSystem loginSystem;

    int state;
    string currentUser;
    string player2Name;
    bool isMultiplayer;
    int currentLevel;
    int playerGems;
    int playerLives;
    int playerScore;
    LevelManager* levelManager;
    Player* player1;
    Player* player2;

    PlayerProgress* player1Progress;
    PlayerProgress* player2Progress;

    
    int player2Lives;
    int player2Score;

    // Texture storage
    sf::Texture bgTexture;
    sf::Texture buttonTexture;
    sf::Texture loginBgTexture;
    sf::Texture menuBgTexture;
    sf::Texture leaderboardBgTexture;
    sf::Texture shopBgTexture;
    sf::Texture levelSelectBgTexture;

    // Screens
    LoginScreen* loginScreen;
    MainMenuScreen* mainMenu;
    PauseScreen* pauseScreen;
    LeaderboardScreen* leaderboardScreen;
    SplashScreen* splash;
    LevelChoiceScreen* levelSelect;
    ShopScreen* shop;
    HUDScreen* hud;
    LevelCompleteScreen* levelComplete;
    GameOverScreen* gameOver;
    ModeChoiceScreen* modeChoice;

    Shop* shopSystem;
    stats* player1Stats;
    stats* player2Stats;
    ScoreSystem* scoreSystem;
    sf::Music menuMusic;
    sf::Music gameMusic;
    bool loadAssets();

public:
    UIManager(sf::RenderWindow& win, sf::Font& f);
    ~UIManager();

    void handleEvents(const sf::Event& event);
    void update();
    void draw();

    void checkSession();
    void logout();
};