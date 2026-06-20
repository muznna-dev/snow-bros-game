#include "UIManager.h"
#include "ScoreSystem.h"
#include "LevelManager.h"
#include "Player.h"

bool UIManager::loadAssets() {
    if (!bgTexture.loadFromFile("SnowBrosAssets/Images/splash_bg.png")) return false;
    if (!buttonTexture.loadFromFile("SnowBrosAssets/Images/button_bg.png")) return false;
    if (!loginBgTexture.loadFromFile("SnowBrosAssets/Images/login_bg.png")) return false;
    if (!menuBgTexture.loadFromFile("SnowBrosAssets/Images/menu_bg.jpeg")) return false;
    if (!leaderboardBgTexture.loadFromFile("SnowBrosAssets/Images/leaderboard_bg.png")) return false;
    if (!levelSelectBgTexture.loadFromFile("SnowBrosAssets/Images/shop_bg.png")) return false;
    if (!shopBgTexture.loadFromFile("SnowBrosAssets/Images/shop_bg.png")) return false;
    return true;
}
UIManager::UIManager(sf::RenderWindow& win, sf::Font& f)
    : window(win), font(f), isMultiplayer(false), shopSystem(nullptr)
{
    if (!loadAssets()) {}

    loginScreen = nullptr;
    mainMenu = nullptr;
    pauseScreen = nullptr;
    leaderboardScreen = nullptr;
    splash = nullptr;
    levelSelect = nullptr;
    shop = nullptr;
    hud = nullptr;
    levelComplete = nullptr;
    gameOver = nullptr;
    modeChoice = nullptr;

    splash = new SplashScreen(win, f, &bgTexture);
    levelSelect = new LevelChoiceScreen(win, f, &levelSelectBgTexture, &buttonTexture);
    shop = new ShopScreen(win, f, &shopBgTexture, &buttonTexture);
    hud = new HUDScreen(win, f);
    levelComplete = new LevelCompleteScreen(win, f, &buttonTexture);
    gameOver = new GameOverScreen(win, f, &buttonTexture);
    loginScreen = new LoginScreen(win, f, loginSystem, &loginBgTexture);
    pauseScreen = new PauseScreen(win, f, &buttonTexture);
    leaderboardScreen = new LeaderboardScreen(win, f, &buttonTexture, &leaderboardBgTexture);
    modeChoice = new ModeChoiceScreen(win, f, &menuBgTexture, &buttonTexture);

    currentUser = "";
    player2Name = "";
    currentLevel = 1;
    playerGems = 0;
    playerLives = 2;
    playerScore = 0;
    player2Lives = 2;
    player2Score = 0;

    player1Stats = new stats();
    player2Stats = nullptr;
    scoreSystem = nullptr;
    levelManager = nullptr;
    player1 = nullptr;
    player2 = nullptr;
    player1Progress = nullptr;
    player2Progress = nullptr;

    checkSession();

    menuMusic.openFromFile("SnowBrosAssets/Sounds/snow_bros_theme_02.ogg");
    gameMusic.openFromFile("SnowBrosAssets/Sounds/snow_bros_level.ogg");

    menuMusic.setLoop(true);
    gameMusic.setLoop(true);


    menuMusic.play();
}

UIManager::~UIManager() {
    delete loginScreen;
    delete mainMenu;
    delete pauseScreen;
    delete leaderboardScreen;
    delete splash;
    delete levelSelect;
    delete shop;
    delete hud;
    delete levelComplete;
    delete gameOver;
    delete modeChoice;

    if (shopSystem) delete shopSystem;

    delete player1Stats;
    if (player2Stats) delete player2Stats;
    if (scoreSystem) delete scoreSystem;
    if (levelManager) delete levelManager;
    if (player1) delete player1;
    if (player2) delete player2;
}

void UIManager::checkSession() {
    if (Session::hasSession()) {
        Session::loadSession(currentUser, player2Name, isMultiplayer);

        if (mainMenu != nullptr) delete mainMenu;
        mainMenu = new MainMenuScreen(window, font, &buttonTexture, &menuBgTexture,
            currentUser, player2Name, isMultiplayer);

        if (shopSystem) delete shopSystem;
        if (isMultiplayer)
            shopSystem = new Shop(currentUser, 100, player2Name, 100);
        else
            shopSystem = new Shop(currentUser, 100);

        if (scoreSystem) delete scoreSystem;
        if (player2Stats) delete player2Stats;

        if (isMultiplayer) {
            player2Stats = new stats();
            scoreSystem = new ScoreSystem(player1Stats, player2Stats);
        }
        else {
            player2Stats = nullptr;
            scoreSystem = new ScoreSystem(player1Stats, nullptr);
        }

        hud->setMulti(isMultiplayer);
        levelComplete->setMulti(isMultiplayer);
        gameOver->setMulti(isMultiplayer);

        state = 10;
    }
    else {
        state = 0;
    }
}

void UIManager::logout() {
    Session::clearSession();
    currentUser = "";
    player2Name = "";
    isMultiplayer = false;
    loginScreen->reset();
    state = 1;
}

void UIManager::handleEvents(const sf::Event& event) {
    switch (state) {
    case 0: splash->handleEvents(event); break;
    case 1: modeChoice->handleEvents(event); break;
    case 2: levelSelect->handleEvents(event); break;
    case 4: shop->handleEvents(event); break;
    case 5: levelComplete->handleEvents(event); break;
    case 6: gameOver->handleEvents(event); break;
    case 9: loginScreen->handleEvents(event); break;
    case 10: mainMenu->handleEvents(event); break;
    case 11: pauseScreen->handleEvents(event); break;
    case 12: leaderboardScreen->handleEvents(event); break;
    }
}

void UIManager::update() {
    if (state == 0) {
        splash->update();
        if (splash->isComplete()) {
            state = 1;
        }
    }

    else if (state == 1) {
        modeChoice->update();
        int choice = modeChoice->getChoice();

        if (choice == 1) {
            isMultiplayer = false;
            loginScreen->setMultiMode(false);
            modeChoice->resetChoice();
            state = 9;
        }
        else if (choice == 2) {
            isMultiplayer = true;
            loginScreen->setMultiMode(true);
            modeChoice->resetChoice();
            state = 9;
        }
    }

    else if (state == 9) {
        loginScreen->update();

        if (loginScreen->login()) {
            currentUser = loginScreen->getLoggedInUser();
            PlayerProgress* prog = loginSystem.getProgress(currentUser);
            if (prog) {
                currentLevel = prog->getCurrentLevel();
            }
            if (isMultiplayer) {
                player2Name = loginScreen->getLoggedInUser2();
            }

            Session::saveSession(currentUser, player2Name, isMultiplayer);

            if (shopSystem) delete shopSystem;
            if (isMultiplayer)
                shopSystem = new Shop(currentUser, 100, player2Name, 100);
            else
                shopSystem = new Shop(currentUser, 100);

            if (scoreSystem) delete scoreSystem;
            if (player2Stats) delete player2Stats;

            if (isMultiplayer) {
                player2Stats = new stats();
                scoreSystem = new ScoreSystem(player1Stats, player2Stats);
            }
            else {
                player2Stats = nullptr;
                scoreSystem = new ScoreSystem(player1Stats, nullptr);
            }

            hud->setMulti(isMultiplayer);
            levelComplete->setMulti(isMultiplayer);
            gameOver->setMulti(isMultiplayer);

            if (mainMenu != nullptr) delete mainMenu;
            mainMenu = new MainMenuScreen(window, font, &buttonTexture, &menuBgTexture,
                currentUser, player2Name, isMultiplayer);

            state = 10;
        }
    }

    else if (state == 10) {

        if (gameMusic.getStatus() == sf::Music::Playing) {
            gameMusic.stop();
            menuMusic.play();
        }
        mainMenu->update();
        int btnClick = mainMenu->getButtonClicked();

        if (btnClick == 1) {
            currentLevel = 1;

            player1Stats->reset();
            if (isMultiplayer) player2Stats->reset();

            playerLives = player1Stats->getLives();
            playerScore = player1Stats->getScore();
            if (isMultiplayer) {
                player2Lives = player2Stats->getLives();
                player2Score = player2Stats->getScore();
            }

            hud->setLives(playerLives);
            hud->setScore(playerScore);
            hud->setLevel(currentLevel);
            if (isMultiplayer) {
                hud->setLives2(player2Lives);
                hud->setScore2(player2Score);
            }

            state = 3;
            mainMenu->resetButtonClicked();
        }
        else if (btnClick == 2) {
            levelSelect->setMaxLevel(currentLevel);
            state = 2;
            mainMenu->resetButtonClicked();
        }
        else if (btnClick == 3) {
            shop->setShop(shopSystem, isMultiplayer);
            shop->setup();
            state = 4;
            mainMenu->resetButtonClicked();
        }
        else if (btnClick == 4) {
            leaderboardScreen->setup();
            state = 12;
            mainMenu->resetButtonClicked();
        }
        else if (btnClick == 5) {
            logout();
            mainMenu->resetButtonClicked();
        }
    }

    else if (state == 2) {
        levelSelect->update();

        int chosenLevel = levelSelect->getChosenLevel();

        if (chosenLevel > 0) {
            currentLevel = chosenLevel;

            hud->setLives(playerLives);
            hud->setScore(playerScore);
            hud->setLevel(currentLevel);
            if (isMultiplayer) {
                hud->setLives2(player2Lives);
                hud->setScore2(player2Score);
            }

            levelSelect->resetChoice();
            state = 3;
        }

        if (levelSelect->backClicked()) {
            levelSelect->resetChoice();
            state = 10;
        }
    }

    else if (state == 3) {
        static int lastP1Lives = 2;
        static int lastP2Lives = 2;
        if (menuMusic.getStatus() == sf::Music::Playing) {
            menuMusic.stop();
            gameMusic.play();
        }

        if (!levelManager) {
            levelManager = new LevelManager();
            levelManager->setLevel(currentLevel);
            player1 = new Player();
            player1->setControls(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, sf::Keyboard::Space);

            if (isMultiplayer) {
                player2 = new Player();
                player2->setControls(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::J);
                player2->setPosition(150, 530);
            }

            if (isMultiplayer)
                levelManager->load(*player1, *player2, scoreSystem);
            else
                levelManager->load(*player1, *player1, scoreSystem);

            lastP1Lives = player1Stats->getLives();
            lastP2Lives = isMultiplayer ? player2Stats->getLives() : 2;
        }

        player1->handleInput();
        player1->update();

        if (isMultiplayer) {
            player2->handleInput();
            player2->update();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            state = 11;
            return;
        }

        if (isMultiplayer)
            levelManager->update(*player1, *player2);
        else
            levelManager->update(*player1, *player1);

        if (player1->getLives() < lastP1Lives) {
            scoreSystem->playerLoseLife(1);
            lastP1Lives = player1->getLives();
        }
        if (isMultiplayer && player2->getLives() < lastP2Lives) {
            scoreSystem->playerLoseLife(2);
            lastP2Lives = player2->getLives();
        }

        hud->setLives(player1->getLives());
        hud->setScore(player1Stats->getScore());
        if (isMultiplayer) {
            hud->setLives2(player2->getLives());
            hud->setScore2(player2Stats->getScore());
        }

        hud->update();

        if (levelManager->isLevelComplete()) {
            ofstream lb("Leaderboard.txt", ios::app);
            if (lb.is_open()) {
                lb << currentUser << " "
                    << player1Stats->getScore() << " "
                    << currentLevel << "\n";
                lb.close();
            }
            PlayerProgress* prog = loginSystem.getProgress(currentUser);
            if (prog) {
                prog->setCurrentLevel(currentLevel + 1);

                if (player1Stats->getScore() > prog->getHighScore()) {
                    prog->setHighScore(player1Stats->getScore());
                }

                loginSystem.saveToFile();
            }
            if (isMultiplayer)
                levelComplete->setData2(currentLevel, player1Stats->getScore(), player2Stats->getScore());
            else
                levelComplete->setData(currentLevel, player1Stats->getScore());
            state = 5;
        }
        else if (levelManager->isGameOver()) {
            PlayerProgress* prog = loginSystem.getProgress(currentUser);
            if (prog) {
                if (player1Stats->getScore() > prog->getHighScore()) {
                    prog->setHighScore(player1Stats->getScore());
                }

                loginSystem.saveToFile();
            }
            ofstream lb("Leaderboard.txt", ios::app);
            if (lb.is_open()) {
                lb << currentUser << " "
                    << player1Stats->getScore() << " "
                    << currentLevel << "\n";
                lb.close();
            }
            if (isMultiplayer)
                gameOver->setData2(player1Stats->getScore(), player2Stats->getScore(), currentLevel);
            else
                gameOver->setData(player1Stats->getScore(), currentLevel);
            state = 6;
        }
    }
    else if (state == 4) {
        shop->update();

        if (shop->exitClicked()) {
            shop->resetExit();
            state = 10;
        }
    }

    else if (state == 5) {
        levelComplete->update();

        if (levelComplete->getBtnClicked() == 1 || levelComplete->goNext) {  // CHECK BOTH
            if (levelManager->getCurrentIndex() < 10) {
                levelManager->nextLevel(*player1, isMultiplayer ? *player2 : *player1);
                currentLevel++;
                hud->setLevel(currentLevel);
                state = 3;
            }
            else {
                delete levelManager;
                delete player1;
                if (player2) delete player2;
                levelManager = nullptr;
                player1 = nullptr;
                player2 = nullptr;
                state = 10;
            }
        }
    }
    else if (state == 6) {
        gameOver->update();

        if (gameOver->menuClicked()) {
            delete levelManager;
            delete player1;
            if (player2) delete player2;
            levelManager = nullptr;
            player1 = nullptr;
            player2 = nullptr;
            state = 10;
        }
    }

    else if (state == 11) {
        pauseScreen->update();
        int pauseBtn = pauseScreen->getButtonClicked();

        if (pauseBtn == 1) {
            state = 3;
            pauseScreen->resetButtonClicked();
        }
        else if (pauseBtn == 2) {
            delete levelManager;
            delete player1;
            if (player2) delete player2;
            levelManager = nullptr;
            player1 = nullptr;
            player2 = nullptr;
            state = 10;
            pauseScreen->resetButtonClicked();
        }
    }

    else if (state == 12) {
        leaderboardScreen->update();

        if (leaderboardScreen->isBackClicked()) {
            leaderboardScreen->resetBackButton();
            state = 10;
        }
    }
}

void UIManager::draw() {
    switch (state) {
    case 0: splash->draw(); break;
    case 1: modeChoice->draw(); break;
    case 2: levelSelect->draw(); break;
    case 3:
    {

        if (levelManager)
            levelManager->draw(window);

        // DRAW PLAYER 1
        if (player1)
            player1->draw(window);


        if (isMultiplayer && player2)
            player2->draw(window);
        if (hud)
            hud->draw();

        break;
    }
    case 4: shop->draw(); break;
    case 5:
        if (levelManager) levelManager->draw(window);
        levelComplete->draw();
        break;
    case 6:
        if (levelManager) levelManager->draw(window);
        gameOver->draw();
        break;
    case 9: loginScreen->draw(); break;
    case 10: mainMenu->draw(); break;
    case 11:
        if (levelManager) levelManager->draw(window);
        pauseScreen->draw();
        break;
    case 12: leaderboardScreen->draw(); break;
    }
}