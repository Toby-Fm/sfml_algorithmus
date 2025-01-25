//
// Created by toby on 03.08.24.
//

#include "button.hpp"
#include <iostream>


void Button::draw(sf::RenderWindow& window)
{
    sf::RectangleShape buttonShape(sf::Vector2f(bounds.width, bounds.height));
    buttonShape.setPosition(bounds.left, bounds.top);
    buttonShape.setFillColor(isPressed ? sf::Color::Red : fillColor);
    window.draw(buttonShape);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        auto mousePos = sf::Mouse::getPosition(window);
        if (bounds.contains(mousePos.x, mousePos.y)) {
            isPressed = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        auto mousePos = sf::Mouse::getPosition(window);
        if (bounds.contains(mousePos.x, mousePos.y) && isPressed) {
            isPressed = false;
            std::cout << "Button clicked!" << std::endl;
            if (onClick) { // Überprüfen, ob eine Callback-Funktion vorhanden ist
                onClick(); // Aktion hier ausführen
            }
        }
    }
}