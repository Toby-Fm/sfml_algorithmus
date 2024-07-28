//
// Created by toby on 26.07.24.
//

#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <deque>
#include <cstdlib>
#include <ctime>

#define WINDOW_HEIGHT 1400
#define WINDOW_WIDTH 800

enum class Key
{
    Escape
};

class Window {
public:
    Window();
    void run();
    void clear();
    void render();
    void destroy();

private:
    void ProcessEvents();
    void drawObjectsOnScreen();
    void backgroundGrid();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); // Key inputs

    sf::RenderWindow window;
    std::vector<sf::RectangleShape> gridCells;
};



#endif //WINDOW_HPP
