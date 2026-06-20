#pragma once
#include <SFML/Graphics.hpp>
#include "Botom.h"
#include <cstdlib>
#include <ctime>

class FlyngFoogaFoog : public Botom {
protected:
    bool  flight;
    float flightTime;
    float groundTime;
    float groundDuration;
    float flightDuration;
    int   flightPhase;
    int   hoverTime;
    static sf::Texture foogaTexture;
public:
    FlyngFoogaFoog(float x, float y, float spd);
    void update() override;
    void draw(sf::RenderWindow& window) override;
    void checkPlatform(sf::RectangleShape& platform) override;
    void setFlight(bool val);
};