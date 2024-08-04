//
// Created by toby on 26.07.24.
//

#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1400

#define GRID_HEIGHT 700
#define GRID_WIDTH 1000
#define GRID_SIZE 90

#define BUTTON_X 1100
#define BUTTON_Y 50
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

#define BUTTON2_Y 150 // Y position for the second button

enum class keyboardKey
{
    Escape, S, E, D
};

enum class gridType
{
    field, wall, start, end, path
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

    static bool isMouseInGrid(sf::Vector2i mousePosition);
    static void checkMouseInGrid(sf::Vector2i mousePosition);
    void drawMousePointer();
    void toggleGridTypeAtMousePosition(sf::Vector2i mousePosition, gridType type);
    void reconstructPath(const std::vector<std::vector<sf::Vector2i>>& predecessors, sf::Vector2i start, sf::Vector2i end);

    sf::RenderWindow window;
    Button myButton; // Button for instant BFS
    Button myVisualButton; // Button for visual BFS

    std::vector<std::vector<gridType>> gridMap;
    std::vector<sf::RectangleShape> gridCells;
    bool isLeftMouseButtonPressed{}; // Status der linken Maustaste
    bool isRightMouseButtonPressed{}; // Status der linken Maustaste

    void breadthFirstSearch();
    void visualBreadthFirstSearch();

    std::vector<std::vector<sf::Vector2i>> predecessors; // Für Pfadrekonstruktion
};

#endif //WINDOW_HPP
