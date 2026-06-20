#pragma once
#include <string>
using namespace std;

class PlayerProgress {
private:
    int currentLevel;
    int livesRemaining;
    int gemCount;
    int highScore;

public:
    PlayerProgress();
    int getCurrentLevel() const;
    int getLivesRemaining() const;
    int getGemCount() const;
    int getHighScore() const;
    void setCurrentLevel(int val);
    void setLivesRemaining(int val);
    void setGemCount(int val);
    void setHighScore(int val);
};

class Account {
private:
    string username;
    string hashedPassword;
    PlayerProgress progress;
public:
    Account();
    Account(string un, string pw);
    string getUsername() const;
    string getHashedPassword() const;
    PlayerProgress& getProgress();
};

class LoginSystem {
private:
    Account* accounts;
    int accountCount;
    int capacity;

public:
    PlayerProgress* getProgress(string username);
    LoginSystem();
    ~LoginSystem();
    string hashPassword(string password);
    bool registerUser(string username, string password);
    bool loginUser(string username, string password);
    void saveToFile();
    void loadFromFile();

};