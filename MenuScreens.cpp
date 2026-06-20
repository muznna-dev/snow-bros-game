#include "MenuScreens.h"
#include<fstream>

LoginScreen::LoginScreen(sf::RenderWindow& win, sf::Font& f, LoginSystem& ls, sf::Texture* bgTex)
    : window(win), font(f), loginSystem(ls), bgTexture(bgTex)
{
    correctLogin = false;
    loggedInUsername = {};
    loggedInUsername2 = {};
    isMultiMode = false;
    setup();
}

void LoginScreen::setup() {
    if (bgTexture != nullptr) {
        bgSprite.setTexture(*bgTexture);
        sf::Vector2u texSize = bgTexture->getSize();
        bgSprite.setScale(800.0f / texSize.x, 600.0f / texSize.y);
    }

    titleText.setFont(font);
    titleText.setString("SNOW BROS");
    titleText.setCharacterSize(72);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(4);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.width / 2.f, 0);
    titleText.setPosition(600, 60);


    usernameBox = TextBox(420, 200, 350, 50, "P1 Username:", font, false);
    pwBox = TextBox(420, 280, 350, 50, "P1 Password:", font, true);


    usernameBox2 = TextBox(420, 360, 350, 50, "P2 Username:", font, false);
    pwBox2 = TextBox(420, 440, 350, 50, "P2 Password:", font, true);

    loginbtn = Button(450, 520, 140, 50, "LOGIN", font, nullptr);
    loginbtn.setImageEnabled(false);

    registerbtn = Button(610, 520, 140, 48, "REGISTER", font, nullptr);
    registerbtn.setImageEnabled(false);

    msgText.setFont(font);
    msgText.setString("");
    msgText.setCharacterSize(24);
    msgText.setFillColor(sf::Color::Red);
    sf::FloatRect msgBounds = msgText.getLocalBounds();
    msgText.setOrigin(msgBounds.width / 2.f, 0);
    msgText.setPosition(450, 565);
}

void LoginScreen::handleEvents(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed) {

        if (usernameBox.clicked(mousePos)) {
            usernameBox.setActive(true);
            pwBox.setActive(false);
            usernameBox2.setActive(false);
            pwBox2.setActive(false);
        }
        else if (pwBox.clicked(mousePos)) {
            pwBox.setActive(true);
            usernameBox.setActive(false);
            usernameBox2.setActive(false);
            pwBox2.setActive(false);
        }
        else if (isMultiMode && usernameBox2.clicked(mousePos)) {
            usernameBox2.setActive(true);
            pwBox2.setActive(false);
            usernameBox.setActive(false);
            pwBox.setActive(false);
        }
        else if (isMultiMode && pwBox2.clicked(mousePos)) {
            pwBox2.setActive(true);
            usernameBox2.setActive(false);
            usernameBox.setActive(false);
            pwBox.setActive(false);
        }
        else if (loginbtn.clicked(mousePos)) {
            string username = usernameBox.getText();
            string password = pwBox.getText();

            if (isMultiMode) {
                if (isMultiMode) {
                    string username2 = usernameBox2.getText();
                    string password2 = pwBox2.getText();

                    bool r1 = loginSystem.registerUser(username, password);
                    bool r2 = loginSystem.registerUser(username2, password2);

                    if (r1 && r2) {
                        msgText.setString("Both players registered!");
                    }
                }
                string username2 = usernameBox2.getText();
                string password2 = pwBox2.getText();

                if (loginSystem.loginUser(username, password) &&
                    loginSystem.loginUser(username2, password2)) {
                    correctLogin = true;
                    loggedInUsername = username;
                    loggedInUsername2 = username2;
                    Session::saveSession(username, username2, true);
                    msgText.setString("Login successful!");
                    msgText.setFillColor(sf::Color::Green);
                }
                else {
                    msgText.setString("Invalid username/password!");
                    msgText.setFillColor(sf::Color::Red);
                    msgText.setOutlineColor(sf::Color::Black);
                    msgText.setOutlineThickness(2);
                }
            }
            else {
                if (loginSystem.loginUser(username, password)) {
                    correctLogin = true;
                    loggedInUsername = username;
                    Session::saveSession(username, "", false);
                    msgText.setString("Login successful!");
                    msgText.setFillColor(sf::Color::Green);
                }
                else {
                    msgText.setString("Invalid username or password!");
                    msgText.setFillColor(sf::Color::Red);
                    msgText.setOutlineColor(sf::Color::Black);
                    msgText.setOutlineThickness(2);
                }
            }
        }
        else if (registerbtn.clicked(mousePos)) {
            string username = usernameBox.getText();
            string password = pwBox.getText();

            if (username.empty() || password.empty()) {
                msgText.setString("Username and password required!");
                msgText.setFillColor(sf::Color::Red);
                msgText.setOutlineColor(sf::Color::Black);
                msgText.setOutlineThickness(2);
            }
            else if (loginSystem.registerUser(username, password)) {
                msgText.setString("Registration successful!");
                msgText.setFillColor(sf::Color::Green);
                msgText.setOutlineColor(sf::Color::Black);
                msgText.setOutlineThickness(2);

            }
            else {
                msgText.setString("Username already exists!");
                msgText.setFillColor(sf::Color::Red);
                msgText.setOutlineColor(sf::Color::Black);
                msgText.setOutlineThickness(2);
            }
        }
        else {
            usernameBox.setActive(false);
            pwBox.setActive(false);
            usernameBox2.setActive(false);
            pwBox2.setActive(false);
        }
    }

    usernameBox.controlInput(event);
    pwBox.controlInput(event);
    if (isMultiMode) {
        usernameBox2.controlInput(event);
        pwBox2.controlInput(event);
    }
}
void LoginScreen::reset() {
    correctLogin = false;
    loggedInUsername = "";
    loggedInUsername2 = "";

    usernameBox.clear();
    pwBox.clear();
    usernameBox2.clear();
    pwBox2.clear();

    msgText.setString("");
}
void LoginScreen::update() {
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    loginbtn.updateHover(mouse);
    registerbtn.updateHover(mouse);
}

void LoginScreen::draw() {
    window.draw(bgSprite);
    window.draw(titleText);
    usernameBox.draw(window);
    pwBox.draw(window);

    if (isMultiMode) {
        usernameBox2.draw(window);
        pwBox2.draw(window);
    }

    loginbtn.draw(window);
    registerbtn.draw(window);
    window.draw(msgText);
}

bool LoginScreen::login() const {
    return correctLogin;
}

string LoginScreen::getLoggedInUser() const {
    return loggedInUsername;
}

string LoginScreen::getLoggedInUser2() const {
    return loggedInUsername2;
}

void LoginScreen::setMultiMode(bool multi) {
    isMultiMode = multi;
}
MainMenuScreen::MainMenuScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btnTex,
    sf::Texture* bgTex, const string& username,
    string& username2, bool isMulti) : window(win), font(f), btnTexture(btnTex), bgTexture(bgTex) {
    currentUser = username;
    currentUser2 = username2;
    buttonNumber = 0;
    multi = isMulti;
    setup();
}

void MainMenuScreen::setup() {
    if (bgTexture != nullptr) {
        bgSprite.setTexture(*bgTexture);
        sf::Vector2u texSize = bgTexture->getSize();
        bgSprite.setScale(800.0f / texSize.x, 600.0f / texSize.y);
    }

    usernameLayout.setFont(font);
    if (multi) {
        usernameLayout.setString("Welcome, " + currentUser + " and " + currentUser2 + "!");
    }
    else {
        usernameLayout.setString("Welcome, " + currentUser + "!");
    }
    usernameLayout.setCharacterSize(28);
    usernameLayout.setFillColor(sf::Color::White);
    usernameLayout.setOutlineColor(sf::Color::Black);
    usernameLayout.setOutlineThickness(2);
    sf::FloatRect userBounds = usernameLayout.getLocalBounds();
    usernameLayout.setOrigin(userBounds.width / 2.f, userBounds.height / 2.f);
    usernameLayout.setPosition(400, 170);
    float btnWidth = 300;
    float btnHeight = 100;
    float btnX = 250;

    newGamebtn = Button(btnX, 180, btnWidth, btnHeight, "New Game", font, btnTexture);
    continuebtn = Button(btnX, 260, btnWidth, btnHeight, "Continue", font, btnTexture);
    shopbtn = Button(400, 400, btnWidth, btnHeight, "Shop", font, btnTexture);
    Leaderboardbtn = Button(btnX, 420, btnWidth, btnHeight, "Leaderboard", font, btnTexture);
    logoutbtn = Button(btnX, 500, btnWidth, btnHeight, "Logout", font, btnTexture);
}

void MainMenuScreen::handleEvents(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed) {
        if (newGamebtn.clicked(mousePos)) {
            buttonNumber = 1;
        }
        else if (continuebtn.clicked(mousePos)) {
            buttonNumber = 2;
        }
        else if (shopbtn.clicked(mousePos)) {
            buttonNumber = 3;
        }
        else if (Leaderboardbtn.clicked(mousePos)) {
            buttonNumber = 4;
        }
        else if (logoutbtn.clicked(mousePos)) {
            buttonNumber = 5;
        }
    }
}

void MainMenuScreen::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    newGamebtn.updateHover(mousePos);
    continuebtn.updateHover(mousePos);
    shopbtn.updateHover(mousePos);
    Leaderboardbtn.updateHover(mousePos);
    logoutbtn.updateHover(mousePos);
}



void MainMenuScreen::draw() {

    window.draw(bgSprite);
    window.draw(title);
    window.draw(usernameLayout);
    newGamebtn.draw(window);
    continuebtn.draw(window);
    shopbtn.draw(window);
    Leaderboardbtn.draw(window);
    logoutbtn.draw(window);
}

int MainMenuScreen::getButtonClicked() const {
    return buttonNumber;
}

void MainMenuScreen::resetButtonClicked() {
    buttonNumber = 0;
}
PauseScreen::PauseScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btnTex)
    : window(win), font(f), btnTexture(btnTex)
{
    btnNumber = 0;
    setup();
}

void PauseScreen::setup() {
    overlay.setFillColor(sf::Color(0, 0, 0, 165));
    overlay.setSize(sf::Vector2f(800, 600));
    overlay.setPosition(0, 0);
    pTitle.setFont(font);
    pTitle.setString("PAUSE");
    pTitle.setCharacterSize(70);
    pTitle.setFillColor(sf::Color::White);
    pTitle.setOutlineColor(sf::Color::Black);
    pTitle.setOutlineThickness(3);

    sf::FloatRect titleBounds = pTitle.getLocalBounds();
    pTitle.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    pTitle.setPosition(400, 150);
    resumebtn = Button(225, 250, 350, 90, "Resume", font, btnTexture);
    mainMenubtn = Button(225, 360, 350, 90, "Back to Menu", font, btnTexture);

}
void PauseScreen::handleEvents(const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed) {
        if (resumebtn.clicked(mousePos)) {
            btnNumber = 1;
        }
        else if (mainMenubtn.clicked(mousePos)) {
            btnNumber = 2;
        }
    }
}
void PauseScreen::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    resumebtn.updateHover(mousePos);
    mainMenubtn.updateHover(mousePos);
}
void PauseScreen::draw() {
    window.draw(overlay);
    window.draw(pTitle);
    resumebtn.draw(window);
    mainMenubtn.draw(window);
}

int PauseScreen::getButtonClicked() const {
    return btnNumber;
}
void PauseScreen::resetButtonClicked() {
    btnNumber = 0;
}

LeaderboardScreen::LeaderboardScreen(sf::RenderWindow& win, sf::Font& f, sf::Texture* btnTex,
    sf::Texture* bgTex) : window(win), font(f), btnTexture(btnTex), bgTexture(bgTex),
    backbtn(5, 5, 200, 100, "BACK", f, btnTex), count(0) {

    backPressed = false;

    if (bgTexture != nullptr) {
        bgSprite.setTexture(*bgTexture);
        sf::Vector2u texSize = bgTexture->getSize();
        bgSprite.setScale(800.0f / texSize.x, 600.0f / texSize.y);
    }
}

void LeaderboardScreen::setup() {
    loadLeaderboard();
}
void LeaderboardScreen::handleEvents(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (backbtn.clicked(mousePos)) {
            backPressed = true;
        }
    }
}
void LeaderboardScreen::update() {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    backbtn.updateHover(mousePos);
}
void LeaderboardScreen::draw() {
    window.draw(bgSprite);
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setOutlineThickness(3);
    title.setOutlineColor(sf::Color::Black);
    title.setString("Leaderboard");
    title.setCharacterSize(38);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    title.setPosition(405, 120);
    window.draw(title);
    for (int i = 0; i < count && i < 10; i++) {
        window.draw(top[i]);

    }
    backbtn.draw(window);
}

void LeaderboardScreen::loadLeaderboard() {
    ifstream file("Leaderboard.txt");
    count = 0;

    if (!file.is_open()) {
        top[0].setFont(font);
        top[0].setString("No entries yet");
        top[0].setCharacterSize(28);
        top[0].setFillColor(sf::Color::White);
        top[0].setPosition(300, 200);
        count = 1;
        return;
    }

    struct Entry {
        string name;
        int score;
        int level;
    };

    Entry entries[100];
    int total = 0;

    while (file >> entries[total].name >> entries[total].score >> entries[total].level) {
        total++;
    }
    file.close();


    for (int i = 0; i < total; i++) {
        for (int j = i + 1; j < total; j++) {
            if (entries[i].name == entries[j].name) {
                if (entries[j].score > entries[i].score) {
                    entries[i] = entries[j];
                }


                for (int k = j; k < total - 1; k++) {
                    entries[k] = entries[k + 1];
                }

                total--;
                j--;
            }
        }
    }


    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (entries[j].score > entries[i].score) {
                swap(entries[i], entries[j]);
            }
        }
    }


    int y = 200;
    count = min(total, 10);

    for (int i = 0; i < count; i++) {
        string entry = to_string(i + 1) + ". " +
            entries[i].name + " " +
            to_string(entries[i].score) +
            " Level " + to_string(entries[i].level);

        top[i].setFont(font);
        top[i].setString(entry);
        top[i].setCharacterSize(24);
        top[i].setFillColor(sf::Color::White);
        top[i].setOutlineThickness(2);
        top[i].setOutlineColor(sf::Color::Black);
        top[i].setPosition(250, y);

        y += 40;
    }
}
bool LeaderboardScreen::isBackClicked() const {
    return backPressed;
}
void LeaderboardScreen::resetBackButton() {
    backPressed = false;
}