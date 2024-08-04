//
// Created by toby on 03.08.24.
//

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

// Einführung der Button Klasse
class Button {
public:
    Button(float x, float y, float width, float height, sf::Color color, std::function<void()> onClick)
    : bounds(x, y, width, height), fillColor(color), isPressed(false), onClick(onClick) {}

    void draw(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
private:
    sf::FloatRect bounds;
    sf::Color fillColor;
    bool isPressed;
    std::function<void()> onClick; // Callback-Funktion für den Klick
};



#endif //BUTTON_HPP
