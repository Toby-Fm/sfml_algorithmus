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

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1400

#define GRID_HEIGHT 700
#define GRID_WIDTH 1000
#define GRID_SIZE 100

enum class keyboardKey
{
    Escape, S, E, D
};

enum class gridType
{
    field, wall, start, end
};


class Window {
public:
    Window();
    void run();
    void clear();
    void render();
    void destroy();
    void drawGridType();

private:
    void ProcessEvents();
    void drawObjectsOnScreen();
    void backgroundGrid();
    void handlePlayerInput(sf::Event event, bool isPressed); // Key inputs

    void drawMousePointer();
    void checkMouseInGrid(sf::Vector2i mousePosition);
    void toggleGridTypeAtMousePosition(sf::Vector2i mousePosition, gridType type);

    sf::RenderWindow window;
    std::vector<std::vector<gridType>> gridMap;
    std::vector<sf::RectangleShape> gridCells;
    bool isLeftMouseButtonPressed{}; // Status der linken Maustaste
    bool isRightMouseButtonPressed{}; // Status der linken Maustaste
};



#endif //WINDOW_HPP
