//
// Created by toby on 26.07.24.
//

#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <deque>
#include <cstdlib>
#include <ctime>

#define WINDOW_HEIGHT 1400
#define WINDOW_WIDTH 800

enum class keyboardKey
{
    Escape
};

enum class gridType
{
    field,
    wall
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
    void handlePlayerInput(sf::Event event, bool isPressed); // Key inputs

    void drawMousePointer();
    void checkMouseInGrid(sf::Vector2i mousePosition);
    void drawGridType();

    sf::RenderWindow window;
    std::vector<sf::RectangleShape> gridCells;
    bool isLeftMouseButtonPressed{}; // Status der linken Maustaste
    bool isRightMouseButtonPressed{}; // Status der linken Maustaste
    int gridSize = 100;
};



#endif //WINDOW_HPP
