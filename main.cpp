#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include<ctime>
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snow Bros");
    sf::Font font;
    if (!font.loadFromFile("SnowBrosAssets/Fonts/pixel.ttf")) {
        return -1;
    }
    window.setFramerateLimit(60);
    UIManager ui(window, font);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            ui.handleEvents(event);
        }
        ui.update();
        window.clear();
        ui.draw();
        window.display();
    }
    return 0;
}