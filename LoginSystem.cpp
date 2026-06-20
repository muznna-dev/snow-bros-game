#include "LoginSystem.h"
#include <fstream>
#include <iostream>
using namespace std;

PlayerProgress::PlayerProgress() {
    currentLevel = 1;
    livesRemaining = 2;
    gemCount = 0;
    highScore = 0;
}


PlayerProgress* LoginSystem::getProgress(string username) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getUsername() == username) {
            return &accounts[i].getProgress();
        }
    }
    return nullptr;
}

int  PlayerProgress::getCurrentLevel()   const {
    return currentLevel;
}
int  PlayerProgress::getLivesRemaining() const {
    return livesRemaining;
}
int  PlayerProgress::getGemCount()       const {
    return gemCount;
}
int  PlayerProgress::getHighScore()      const {
    return highScore;
}

void PlayerProgress::setCurrentLevel(int val) {
    currentLevel = val;
}
void PlayerProgress::setLivesRemaining(int val) {
    livesRemaining = val;
}
void PlayerProgress::setGemCount(int val) {
    gemCount = val;
}
void PlayerProgress::setHighScore(int val) {
    highScore = val;
}



Account::Account() {
    username = "";
    hashedPassword = "";
}

Account::Account(string un, string pw) {
    username = un;
    hashedPassword = pw;
}

string Account::getUsername()      const {
    return username;
}
string           Account::getHashedPassword() const {
    return hashedPassword;
}
PlayerProgress& Account::getProgress() {
    return progress;
}



LoginSystem::LoginSystem() {
    accounts = new Account[100];
    capacity = 100;
    accountCount = 0;
    loadFromFile();
}

LoginSystem::~LoginSystem() {
    delete[] accounts;
}

string LoginSystem::hashPassword(string password) {
    unsigned int hash = 0;
    for (int i = 0; i < (int)password.length(); i++) {
        hash = hash * 37 + password[i];
    }
    return to_string(hash);
}

bool LoginSystem::registerUser(string username, string password) {
    if (accountCount >= capacity) {
        cout << "Account limit reached." << endl;
        return false;
    }

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getUsername() == username) {
            cout << "Username already exists." << endl;
            return false;
        }
    }
    string hashed = hashPassword(password);
    accounts[accountCount] = Account(username, hashed);
    accountCount++;

    saveToFile();
    return true;
}
bool LoginSystem::loginUser(string username, string password) {
    string hashed = hashPassword(password);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getUsername() == username &&
            accounts[i].getHashedPassword() == hashed) {
            return true;
        }
    }

    cout << "Invalid username or password." << endl;
    return false;
}
void LoginSystem::saveToFile() {
    ofstream file("accounts.txt");
    if (!file.is_open()) {
        cout << "Error! could not open accounts.txt for saving." << endl;
        return;
    }

    for (int i = 0; i < accountCount; i++) {
        PlayerProgress& p = accounts[i].getProgress();
        file << accounts[i].getUsername() << " "
            << accounts[i].getHashedPassword() << " "
            << p.getCurrentLevel() << " "
            << p.getLivesRemaining() << " "
            << p.getGemCount() << " "
            << p.getHighScore() << "\n";
    }

    file.close();
}

void LoginSystem::loadFromFile() {
    ifstream file("accounts.txt");

    if (!file.is_open())
        return;

    string username, hashedPassword;
    int currentLevel, livesRemaining, gemCount, highScore;

    while (file >> username >> hashedPassword
        >> currentLevel >> livesRemaining
        >> gemCount >> highScore) {

        if (accountCount >= capacity)
            break;

        accounts[accountCount] = Account(username, hashedPassword);

        PlayerProgress& p = accounts[accountCount].getProgress();
        p.setCurrentLevel(currentLevel);
        p.setLivesRemaining(livesRemaining);
        p.setGemCount(gemCount);
        p.setHighScore(highScore);

        accountCount++;
    }

    file.close();
}