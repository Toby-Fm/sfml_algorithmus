//
// Created by toby on 26.07.24.
//

#include "include/window.hpp"

Window::Window(int width, int height, const std::string &title)
    : window(sf::VideoMode(width, height), title) {}

void Window::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        // Hier können Sie zeichnen
        window.display();
    }
}
