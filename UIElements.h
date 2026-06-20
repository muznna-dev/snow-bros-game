#pragma once
#include <SFML/Graphics.hpp>
#include<string>

using namespace std;

class Button {
private:
	sf::RectangleShape buttonBox;
	sf::Sprite sprite;
	sf::Text text;
	string label;
	bool mouseHover;
	bool image;
public:
	Button();
	Button(float x, float y, float w, float h, const string& Label, sf::Font& font, sf::Texture* buttonTexture);
	void draw(sf::RenderWindow& window);
	void updateHover(const sf::Vector2f& mouse);
	void setImageEnabled(bool enable);
	string getLabel() const;
	bool clicked(const sf::Vector2f& mouse) const;
};

class TextBox {
private:
	sf::RectangleShape rect;
	sf::Text displayed;
	sf::Text label;
	string input;
	bool isTyping;
	bool passwordHidden;
	int maxchar;
public:
	TextBox();
	TextBox(float x, float y, float width, float height, const std::string& labelText, sf::Font& font, bool isPwHide);
	void draw(sf::RenderWindow& window);
	void controlInput(const sf::Event& event);
	void setActive(bool val);
	bool clicked(const sf::Vector2f& mouse) const;

	string getText() const;
	void clear();

};
class Session {
public:
	static void saveSession(const string& player1);
	static void saveSession(const string& player1, const string& player2, bool multi);
	static void loadSession(string& player1, string& player2, bool& multi);
	static bool hasSession();
	static void clearSession();
};