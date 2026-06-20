#pragma once
#include <SFML/Graphics.hpp>

class Screen {
public:

    virtual ~Screen() {}

    virtual void setup() = 0;
    virtual void handleEvents(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
};