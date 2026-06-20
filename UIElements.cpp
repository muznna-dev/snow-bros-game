#include"UIElements.h"
#include <fstream>
#include<cstdio>
Button::Button() {
	label = {};
	mouseHover = false;
	image = false;
}
Button::Button(float x, float y, float w, float h, const string& Label, sf::Font& font, sf::Texture* buttonTexture) {
	label = Label;
	mouseHover = false;
	image = false;
	buttonBox.setSize(sf::Vector2f(w, h));
	buttonBox.setPosition(x, y);
	buttonBox.setFillColor(sf::Color(100, 200, 255));
	buttonBox.setOutlineThickness(3);
	buttonBox.setOutlineColor(sf::Color(50, 50, 50));
	text.setFont(font);
	text.setString(label);
	text.setCharacterSize(28);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);

	sf::FloatRect textBounds = text.getLocalBounds();


	text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 4.f);


	text.setPosition(x + w / 2.f, y + h / 2.f - 5);
	if (buttonTexture != nullptr) {
		sprite.setTexture(*buttonTexture);
		sprite.setPosition(x, y);


		sf::Vector2u texSize = buttonTexture->getSize();
		sprite.setScale(w / texSize.x, h / texSize.y);

		sprite.setColor(sf::Color(255, 255, 255, 255));
		image = true;
	}

}
void Button::draw(sf::RenderWindow& window) {
	if (image)
		window.draw(sprite);
	else
		window.draw(buttonBox);
	window.draw(text);
}
void Button::updateHover(const sf::Vector2f& mouse) {
	if (buttonBox.getGlobalBounds().contains(mouse)) {
		mouseHover = true;

		if (image) {
			sprite.setColor(sf::Color(180, 180, 180, 255));
		}
		else {
			buttonBox.setFillColor(sf::Color(80, 180, 235));
		}
	}
	else {
		mouseHover = false;

		if (image) {
			sprite.setColor(sf::Color(255, 255, 255, 255)); 
		}
		else {
			buttonBox.setFillColor(sf::Color(100, 200, 255));
		}
	}
}

bool Button::clicked(const sf::Vector2f& mouse) const {
	return buttonBox.getGlobalBounds().contains(mouse);
}
void Button::setImageEnabled(bool enable) {
	image = enable;
}
string Button::getLabel() const {
	return label;
}

TextBox::TextBox() {
	input = {};
	isTyping = false;
	passwordHidden = false;
	maxchar = 20;
}
TextBox::TextBox(float x, float y, float width, float height, const std::string& labelText, sf::Font& font, bool isPwHide) {
	input = {};
	isTyping = false;
	passwordHidden = isPwHide;
	maxchar = 20;
	label.setFont(font);
	label.setString(labelText);
	label.setCharacterSize(20);
	label.setFillColor(sf::Color::White);
	label.setOutlineColor(sf::Color::Black);
	label.setOutlineThickness(3);
	label.setPosition(x, y - 30);
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(sf::Color(240, 240, 240));
	rect.setOutlineThickness(3);
	rect.setOutlineColor(sf::Color(80, 80, 80));
	displayed.setFont(font);
	displayed.setCharacterSize(22);
	displayed.setFillColor(sf::Color::Black);
	displayed.setPosition(x + 10, y + 10);

}
void TextBox::draw(sf::RenderWindow& window) {
	window.draw(label);
	window.draw(rect);
	window.draw(displayed);
}
void TextBox::controlInput(const sf::Event& event) {
	if (!isTyping) return;

	if (event.type == sf::Event::TextEntered) {

		if (event.text.unicode == 8 && input.length() > 0) {
			input.pop_back();
		}

		else if (event.text.unicode >= 32 && event.text.unicode < 128
			&& input.length() < maxchar) {
			input += static_cast<char>(event.text.unicode);
		}

		if (passwordHidden) {
			displayed.setString(string(input.length(), '*'));
		}
		else {
			displayed.setString(input);
		}
	}
}
void TextBox::setActive(bool val) {
	isTyping = val;
	if (isTyping) {
		rect.setOutlineColor(sf::Color::Yellow);
		rect.setOutlineThickness(3);
	}
	else {
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(2);
	}
}
bool TextBox::clicked(const sf::Vector2f& mouse) const {
	return rect.getGlobalBounds().contains(mouse);
}

string TextBox::getText() const {
	return input;
}
void TextBox::clear() {
	input = {};
	displayed.setString(input);
}

void Session::saveSession(const string& player1, const string& player2, bool multi) {
	ofstream file("session.txt");
	if (file.is_open()) {
		if (multi) {
			file << "multi" << endl;
			file << player1 << endl;
			file << player2 << endl;
		}
		else {
			file << "single" << endl;
			file << player1 << endl;
		}
		file.close();
	}
}

void Session::loadSession(string& player1, string& player2, bool& multi) {
	ifstream file("session.txt");
	if (file.is_open()) {
		string mode;
		getline(file, mode);

		if (mode == "multi") {
			multi = true;
			getline(file, player1);
			getline(file, player2);
		}
		else {
			multi = false;
			getline(file, player1);
			player2 = "";
		}
		file.close();
	}
}
void Session::saveSession(const string& player1) {
	ofstream file("session.txt");
	if (file.is_open()) {
		file << "single" << endl;
		file << player1 << endl;
		file.close();
	}
}

bool Session::hasSession() {
	ifstream file("session.txt");
	return file.good();
}

void Session::clearSession() {
	remove("session.txt");
}