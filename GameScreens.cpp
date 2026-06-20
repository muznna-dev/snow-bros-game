#include "GameScreens.h"
#include<string>
using namespace std;
SplashScreen::SplashScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg) :window(win), font(f), bgTex(bg) {
    progress = 0;
    complete = false;
    setup();
}
void SplashScreen::setup() {
    if (bgTex != nullptr) {
        bg.setTexture(*bgTex);

        sf::Vector2u size = bgTex->getSize();
        bg.setScale(800.0f / size.x, 600.0f / size.y);
    }
    logo.setFont(font);
    logo.setString("Loading...");
    logo.setCharacterSize(30);
    sf::FloatRect bounds = logo.getLocalBounds();
    logo.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    logo.setPosition(420.f, 400.0f);
    logo.setOutlineColor(sf::Color::Black);
    logo.setOutlineThickness(2);

    load.setSize(sf::Vector2f(300.0f, 20.0f));
    load.setFillColor(sf::Color::White);
    load.setPosition(250.0f, 350.0f);

    fullLoad.setSize(sf::Vector2f(0.0f, 20.0f));
    fullLoad.setFillColor(sf::Color::Blue);
    fullLoad.setPosition(250.0f, 350.0f);

    time.restart();
}
void SplashScreen::handleEvents(const sf::Event& event) {}
void SplashScreen::update() {
    float timeFinished = time.getElapsedTime().asSeconds();
    progress = timeFinished / 3.f;
    if (progress > 1.f)
        progress = 1.f;
    fullLoad.setSize(sf::Vector2f(300.f * progress, 20.f));
    if (timeFinished >= 3.f)
        complete = true;
}
void SplashScreen::draw() {
    window.clear();

    if (bgTex != nullptr)
        window.draw(bg);

    window.draw(logo);
    window.draw(load);
    window.draw(fullLoad);
}
bool SplashScreen::isComplete() {
    return complete;
}



LevelChoiceScreen::LevelChoiceScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg, sf::Texture* btn)
    :window(win), font(f), bgTex(bg), btnTex(btn),
    backBtn(600, 500, 150, 60, "BACK", f, btn)
{
    chosen = -1;

    for (int i = 0; i < 10; i++)
        unlocked[i] = false;

    setMaxLevel(1);  // Unlocks level 1 (sets max=1, unlocked[0]=true)
    setup();
}
void LevelChoiceScreen::setup() {
    if (bgTex != nullptr) {
        bg.setTexture(*bgTex);

        sf::Vector2u size = bgTex->getSize();
        bg.setScale(800.0f / size.x, 600.0f / size.y);
    }

    heading.setFont(font);
    heading.setCharacterSize(50);
    heading.setOutlineColor(sf::Color::Black);
    heading.setOutlineThickness(3);
    heading.setString("Select Level:");
    sf::FloatRect hBtn = heading.getLocalBounds();
    heading.setOrigin(hBtn.width / 2.f, hBtn.height / 2.f);
    heading.setPosition(360.f, 50.f);
    float startY = 150.0f;
    float gapY = 120.0f;
    float startX = 100.f;
    float gapX = 120.0f;
    for (int i = 0; i < 10; i++) {

        int row = i / 5;
        int col = i % 5;

        float x = startX + col * gapX;
        float y = startY + row * gapY;

        string label = to_string(i + 1);

        levelBtns[i] = Button(x, y, 80.0f, 80.0f, label, font, btnTex);
    }
}
int LevelChoiceScreen::getChosenLevel() const {
    return chosen;
}
void LevelChoiceScreen::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

        for (int i = 0; i < 10; i++) {
            if (unlocked[i] && levelBtns[i].clicked(mousePos)) {
                chosen = i + 1;
            }
        }

        if (backBtn.clicked(mousePos)) {
            chosen = -2; // special value for back
        }
    }
}

void LevelChoiceScreen::resetChoice() {
    chosen = -1; // Reset to no choice
}

void LevelChoiceScreen::update() {

    sf::Vector2f mousePos = window.mapPixelToCoords(
        sf::Mouse::getPosition(window));

    for (int i = 0; i < 10; i++) {

        if (unlocked[i])
            levelBtns[i].updateHover(mousePos);

    }

    backBtn.updateHover(mousePos);

}
void LevelChoiceScreen::draw() {
    window.clear();

    if (bgTex != nullptr)
        window.draw(bg);

    window.draw(heading);
    window.draw(progress);

    for (int i = 0; i < 10; i++) {
        levelBtns[i].draw(window);
    }

    backBtn.draw(window);
}
void LevelChoiceScreen::setMaxLevel(int level) {
    max = level;
    for (int i = 0; i < 10; i++) {
        if (i < max)
            unlocked[i] = true;
        else
            unlocked[i] = false;
    }
}
bool LevelChoiceScreen::backClicked() const {
    return chosen == -2;
}

ShopScreen::ShopScreen(sf::RenderWindow& win, sf::Font& f,
    sf::Texture* bg, sf::Texture* btn)
    : window(win), font(f), bgTex(bg), btnTex(btn),
    exitBtn(300.0f, 500.0f, 200.0f, 50.0f, "EXIT", f, btn),
    shop(nullptr), multi(false), msgBox(false), pendingItemIndex(-1) {

    itemsBought = -1;

    // Popup overlay
    popupOverlay.setSize(sf::Vector2f(400, 200));
    popupOverlay.setPosition(200, 200);
    popupOverlay.setFillColor(sf::Color::White);
    popupOverlay.setOutlineColor(sf::Color::Black);
    popupOverlay.setOutlineThickness(3);

    popupText.setFont(font);
    popupText.setString("Player?");
    popupText.setCharacterSize(25);
    popupText.setFillColor(sf::Color::White);
    popupText.setOutlineColor(sf::Color::Black);
    popupText.setOutlineThickness(2);
    sf::FloatRect ptb = popupText.getLocalBounds();
    popupText.setOrigin(ptb.width / 2.0f, ptb.height / 2.0f);
    popupText.setPosition(400, 230);

    player1ChoiceBtn = Button(180, 290, 240, 80, "PLAYER 1", font, btn);
    player2ChoiceBtn = Button(380, 290, 240, 80, "PLAYER 2", font, btn);

    setup();
}

void ShopScreen::resetExit() {
    itemsBought = -1;
}

void ShopScreen::setShop(Shop* s, bool m) {
    shop = s;
    multi = m;
}

void ShopScreen::setup() {
    if (bgTex != nullptr) {
        bg.setTexture(*bgTex);
        sf::Vector2u size = bgTex->getSize();
        bg.setScale(800.0f / size.x, 600.0f / size.y);
    }

    heading.setFont(font);
    heading.setString("SHOP");
    heading.setCharacterSize(30);
    heading.setOutlineColor(sf::Color::Black);
    heading.setOutlineThickness(2);
    sf::FloatRect hb = heading.getLocalBounds();
    heading.setOrigin(hb.width / 2.0f, hb.height / 2.0f);
    heading.setPosition(400.0f, 60.0f);

    
    gemDisplay.setFont(font);
    gemDisplay.setCharacterSize(22);
    gemDisplay.setFillColor(sf::Color::Cyan);
    gemDisplay.setOutlineColor(sf::Color::Black);
    gemDisplay.setOutlineThickness(2);
    gemDisplay.setPosition(50.0f, 100.0f);

    string itemNames[5] = {
        "EXTRA LIFE",
        "SPEED BOOST",
        "SNOWBALL POWER",
        "DISTANCE",
        "BALLOON MODE"
    };

    int costs[5] = { 50, 20, 30, 25, 35 };

    for (int i = 0; i < 5; i++) {
        items[i].setFont(font);
        items[i].setCharacterSize(20);
        items[i].setString(itemNames[i]);
        items[i].setPosition(150.0f, 150.0f + i * 60);
        items[i].setOutlineColor(sf::Color::Black);
        items[i].setOutlineThickness(2);

        price[i].setFont(font);
        price[i].setCharacterSize(18);
        price[i].setString(to_string(costs[i]) + " GEMS");
        price[i].setPosition(350.0f, 150.0f + i * 60);
        price[i].setOutlineColor(sf::Color::Black);
        price[i].setOutlineThickness(2);

        
        itemCounts[i].setFont(font);
        itemCounts[i].setCharacterSize(20);
        itemCounts[i].setFillColor(sf::Color::White);
        itemCounts[i].setOutlineColor(sf::Color::Black);
        itemCounts[i].setOutlineThickness(1);
        itemCounts[i].setPosition(350.0f, 170.0f + i * 60);

        buy[i] = Button(550.0f, 140.0f + i * 60,
            140.0f, 60.0f, "BUY", font, btnTex);
    }

    msgBox = false;
    pendingItemIndex = -1;
    refreshDisplay();
}

void ShopScreen::refreshDisplay() {
    if (!shop) return;

   
    if (multi) {
        gemDisplay.setString("P1 Gems: " + to_string(shop->getGems(1)) +
            "  |  P2 Gems: " + to_string(shop->getGems(2)));
    }
    else {
        gemDisplay.setString("Gems: " + to_string(shop->getGems(1)));
    }

   
    for (int i = 0; i < 5; i++) {
        if (multi) {
            int count1 = shop->getItemCount(i, 1);
            int count2 = shop->getItemCount(i, 2);
            itemCounts[i].setString("P1:" + to_string(count1) + " P2:" + to_string(count2));
        }
        else {
            int count = shop->getItemCount(i, 1);
            itemCounts[i].setString("Owned: " + to_string(count));
        }
    }
}

void ShopScreen::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

       
        if (msgBox) {
            if (player1ChoiceBtn.clicked(mousePos)) {
                if (shop) {
                    shop->purchaseItem(pendingItemIndex, 1);
                    itemsBought = pendingItemIndex;
                }
                msgBox = false;
                pendingItemIndex = -1;
                refreshDisplay();
            }

            if (player2ChoiceBtn.clicked(mousePos)) {
                if (shop) {
                    shop->purchaseItem(pendingItemIndex, 2);
                    itemsBought = pendingItemIndex;
                }
                msgBox = false;
                pendingItemIndex = -1;
                refreshDisplay();
            }
            return;
        }

     
        for (int i = 0; i < 5; i++) {
            if (buy[i].clicked(mousePos)) {
                if (shop) {
                    if (multi) {
                        // Show popup
                        msgBox = true;
                        pendingItemIndex = i;
                    }
                    else {
                        // Buy directly for player 1
                        if (shop->purchaseItem(i, 1)) {
                            itemsBought = i;
                            refreshDisplay();
                        }
                    }
                }
            }
        }

        if (exitBtn.clicked(mousePos)) {
            itemsBought = -2;
        }
    }
}

void ShopScreen::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(
        sf::Mouse::getPosition(window));

    if (msgBox) {
        player1ChoiceBtn.updateHover(mousePos);
        player2ChoiceBtn.updateHover(mousePos);
    }
    else {
        for (int i = 0; i < 5; i++)
            buy[i].updateHover(mousePos);
        exitBtn.updateHover(mousePos);
    }
}

void ShopScreen::draw() {
    window.clear();
    if (bgTex != nullptr)
        window.draw(bg);

    window.draw(heading);
    window.draw(gemDisplay);  

    for (int i = 0; i < 5; i++) {
        window.draw(items[i]);
        window.draw(price[i]);
        window.draw(itemCounts[i]);  
        buy[i].draw(window);
    }

    exitBtn.draw(window);

    // Draw popup if showing
    if (msgBox) {
        window.draw(popupOverlay);
        window.draw(popupText);
        player1ChoiceBtn.draw(window);
        player2ChoiceBtn.draw(window);
    }
}

int ShopScreen::getBoughtItem() const {
    return itemsBought;
}

bool ShopScreen::exitClicked() const {
    return itemsBought == -2;
}

HUDScreen::HUDScreen(sf::RenderWindow& win, sf::Font& f)
    : window(win), font(f) {

    lives = 0;
    score = 0;
    level = 1;

    multi = false;
    lives2 = 0;
    score2 = 0;

    setup();
}
void HUDScreen::setup() {

    livesLayout.setFont(font);
    livesLayout.setCharacterSize(18);
    livesLayout.setPosition(20.0f, 10.0f);

    scoreLayout.setFont(font);
    scoreLayout.setCharacterSize(18);
    scoreLayout.setPosition(20.0f, 30.0f);

    levelLayout.setFont(font);
    levelLayout.setCharacterSize(18);
    levelLayout.setPosition(400.0f, 10.0f);
    //secind player
    livesLayout2.setFont(font);
    livesLayout2.setCharacterSize(18);
    livesLayout2.setPosition(650.0f, 10.0f);

    scoreLayout2.setFont(font);
    scoreLayout2.setCharacterSize(18);
    scoreLayout2.setPosition(650.0f, 30.0f);
}
void HUDScreen::handleEvents(const sf::Event& event) {

}

void HUDScreen::update() {

    livesLayout.setString("Lives: " + to_string(lives));
    scoreLayout.setString("Score: " + to_string(score));
    levelLayout.setString("Level: " + to_string(level));
    if (multi) {
        livesLayout.setString("P1 Lives: " + to_string(lives));
        scoreLayout.setString("P1 Score: " + to_string(score));
        livesLayout2.setString("P2 Lives: " + to_string(lives2));
        scoreLayout2.setString("P2 Score: " + to_string(score2));
    }
}
void HUDScreen::draw() {



    window.draw(livesLayout);
    window.draw(scoreLayout);
    window.draw(levelLayout);

    if (multi) {
        window.draw(livesLayout2);
        window.draw(scoreLayout2);
    }
}
void HUDScreen::setLives(int l) {
    lives = l;
}

void HUDScreen::setScore(int s) {
    score = s;
}

void HUDScreen::setLevel(int lv) {
    level = lv;
}

void HUDScreen::setMulti(bool multiP) {
    multi = multiP;
}
void HUDScreen::setLives2(int l) {
    lives2 = l;
}

void HUDScreen::setScore2(int s) {
    score2 = s;
}


LevelCompleteScreen::LevelCompleteScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btn)
    : window(win), font(f), btnTex(btn),
    menuBtn(450.0f, 400.0f, 120.0f, 50.0f, "MENU", f, btn) {

    finalScore = 0;
    level = 1;
    btnClicked = 0;

    multi = false;
    finalScore2 = 0;

    setup();
}

void LevelCompleteScreen::setup() {

    title.setFont(font);
    title.setString("LEVEL COMPLETE");
    title.setCharacterSize(35);

    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2.0f, tb.height / 2.0f);
    title.setPosition(400.0f, 200.0f);

    score.setFont(font);
    score.setCharacterSize(25);
    score.setPosition(300.0f, 260.0f);

    //p2 
    score2.setFont(font);
    score2.setCharacterSize(25);
    score2.setPosition(300.0f, 290.0f);

    timer.restart();
    goNext = false;
}
void LevelCompleteScreen::setMulti(bool m) {
    multi = m;
}



void LevelCompleteScreen::setData(int lvl, int sc) {
    level = lvl;
    finalScore = sc;
    multi = false;
    timer.restart();
    goNext = false;
}

void LevelCompleteScreen::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {

        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

        if (menuBtn.clicked(mousePos)) {
            btnClicked = 1; // go to menu
        }
    }
}
void LevelCompleteScreen::update() {
    float timePassed = timer.getElapsedTime().asSeconds();
    timeLeft = 3.0f - timePassed;

    if (timeLeft <= 0.0f) {
        goNext = true;
    }

    score.setString("P1 Score: " + to_string(finalScore));

    if (multi) {
        score2.setString("P2 Score: " + to_string(finalScore2));
    }

    int display = (int)(timeLeft)+1;
    title.setString("NEXT LEVEL IN " + to_string(display));
}

void LevelCompleteScreen::setData2(int lvl, int sc1, int sc2) {
    level = lvl;
    finalScore = sc1;
    finalScore2 = sc2;
    multi = true;
    timer.restart();
    goNext = false;
}
int LevelCompleteScreen::getBtnClicked() const {
    return btnClicked;
}
void LevelCompleteScreen::draw() {

    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(800.0f, 600.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    window.draw(overlay);
    window.draw(title);
    window.draw(score);

    if (multi)
        window.draw(score2);
    menuBtn.draw(window);
}

GameOverScreen::GameOverScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btn)
    : window(win), font(f), btnTex(btn),
    menuBtn(300.0f, 400.0f, 200.0f, 60.0f, "MENU", f, btn) {

    finalScore = 0;
    finalLevel = 1;

    multi = false;
    finalScore2 = 0;

    setup();
}

void GameOverScreen::setup() {

    msg.setFont(font);
    msg.setString("GAME OVER");
    msg.setCharacterSize(40);

    sf::FloatRect mb = msg.getLocalBounds();
    msg.setOrigin(mb.width / 2.0f, mb.height / 2.0f);
    msg.setPosition(400.0f, 200.0f);

    score.setFont(font);
    score.setCharacterSize(25);
    score.setPosition(300.0f, 260.0f);

    level.setFont(font);
    level.setCharacterSize(25);
    level.setPosition(300.0f, 300.0f);

    score2.setFont(font);
    score2.setCharacterSize(25);
    score2.setPosition(300.f, 330.f);
}

void GameOverScreen::setData(int sc, int lvl) {
    finalScore = sc;
    finalLevel = lvl;
    multi = false;
}
void GameOverScreen::setData2(int sc1, int sc2, int lvl) {
    finalScore = sc1;
    finalScore2 = sc2;
    finalLevel = lvl;
    multi = true;
}

void GameOverScreen::handleEvents(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

        if (menuBtn.clicked(mousePos)) {
            finalLevel = -1; // signal exit
        }
    }
}

void GameOverScreen::update() {
    score.setString("P1 Score: " + to_string(finalScore));
    level.setString("Level Reached: " + to_string(finalLevel));

    if (multi) {
        score2.setString("P2 Score: " + to_string(finalScore2));
    }
}
void GameOverScreen::draw() {


    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(800.0f, 600.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));

    window.draw(overlay);
    window.draw(msg);
    window.draw(score);
    window.draw(level);
    if (multi)
        window.draw(score2);
    menuBtn.draw(window);
}


void GameOverScreen::setMulti(bool m) {
    multi = m;
}


bool GameOverScreen::menuClicked() const {
    return finalLevel == -1;
}

ModeChoiceScreen::ModeChoiceScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* bg, sf::Texture* btn)
    : window(win), font(f), bgTex(bg), btnTex(btn),
    singleBtn(180, 250, 300, 70, "SINGLE PLAYER", f, 0),
    multiBtn(350, 450, 300, 70, "MULTIPLAYER", f, 0)
{
    choice = 0;

    singleBtn.setImageEnabled(false);
    multiBtn.setImageEnabled(false);

    if (bgTex) {
        this->bg.setTexture(*bgTex);
        sf::Vector2u size = bgTex->getSize();
        this->bg.setScale(800.0f / size.x, 600.0f / size.y);
    }

    title.setFont(font);
    title.setString("SELECT MODE");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    sf::FloatRect tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2, tb.height / 2);
    title.setPosition(400, 170);
}

void ModeChoiceScreen::setup() {
    choice = 0;
}

void ModeChoiceScreen::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (singleBtn.clicked(mousePos))
            choice = 1;
        if (multiBtn.clicked(mousePos))
            choice = 2;
    }
}

void ModeChoiceScreen::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    singleBtn.updateHover(mousePos);
    multiBtn.updateHover(mousePos);
}

void ModeChoiceScreen::draw() {
    window.clear();
    if (bgTex)
        window.draw(bg);
    window.draw(title);
    singleBtn.draw(window);
    multiBtn.draw(window);
}

int ModeChoiceScreen::getChoice() const {
    return choice;
}

void ModeChoiceScreen::resetChoice() {
    choice = 0;
}