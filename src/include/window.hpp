//
// Created by toby on 26.07.24.
//

#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "button.hpp"

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

#define BUTTON_X 1100
#define BUTTON_Y 50
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

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

    bool isMouseInGrid(sf::Vector2i mousePosition);
    void checkMouseInGrid(sf::Vector2i mousePosition);
    void drawMousePointer();
    void toggleGridTypeAtMousePosition(sf::Vector2i mousePosition, gridType type);

    sf::RenderWindow window;
    Button myButton{BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, sf::Color::Blue}; // Positionierung des Buttons

    std::vector<std::vector<gridType>> gridMap;
    std::vector<sf::RectangleShape> gridCells;
    bool isLeftMouseButtonPressed{}; // Status der linken Maustaste
    bool isRightMouseButtonPressed{}; // Status der linken Maustaste
};

#endif //WINDOW_HPP
