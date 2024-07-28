//
// Created by toby on 26.07.24.
//

#include "include/window.hpp"
#include <string>
#include <cmath>

Window::Window()
{
    window.create(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "SFML Algorithmus", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    // Grid in den background zeichnen
    backgroundGrid();// Initiale Erstellung des Gitters mit zufälligen Farben
}

// Wenn das Fenster läuft
void Window::run()
{
    while (window.isOpen())
    {
        ProcessEvents();
        render();
    }
}

// Löscht den Bildschirm
void Window::clear()
{
    window.clear(sf::Color::Black);
}

// Rendert das Fenster
void Window::render()
{
    clear();
    drawObjectsOnScreen();
    window.display();
}

// Zerstört das Fenster
void Window::destroy()
{
    std::cout << "Fenster wird geschlossen" << std::endl;
    window.close();
}

void Window::ProcessEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
            {
                handlePlayerInput(event.key.code, true);
                break;
            }

            case sf::Event::KeyReleased:
            {
                handlePlayerInput(event.key.code, false);
                break;
            }

            default:
            {
                break;
            }
        }
    }
}

// Objekte on Screen
void Window::drawObjectsOnScreen()
{
    for (const auto& cell : gridCells)
    {
        window.draw(cell);
    }
}

// Grid in background
void Window::backgroundGrid()
{
    sf::Vector2u windowSize = window.getSize();
    int gridSize = 20;
    int startX = 0; // Startposition X
    int startY = 0; // Startposition Y

    sf::Color lineColor = sf::Color::Blue;
    gridCells.clear();

    // Horizontale Linien
    for (int y = startY; y < windowSize.y; y += gridSize)
    {
        sf::RectangleShape line(sf::Vector2f(windowSize.x, 1));
        line.setPosition(startX, y);
        line.setFillColor(lineColor);
        gridCells.push_back(line);
    }

    /*
     * Letzte Horizontale Linie hinzufügen
     * Das grid geht normal über den Bildschirmrand, habe noch nicht verstanden warum, damit geht es aber auch...
     */
    sf::RectangleShape lastHorizontalLine(sf::Vector2f(windowSize.x, 1));
    lastHorizontalLine.setPosition(startX, windowSize.y - 1);
    lastHorizontalLine.setFillColor(lineColor);
    gridCells.push_back(lastHorizontalLine);

    // Vertikale Linien
    for (int x = startX; x < windowSize.x; x += gridSize)
    {
        sf::RectangleShape line(sf::Vector2f(1, windowSize.y));
        line.setPosition(x, startY);
        line.setFillColor(lineColor);
        gridCells.push_back(line);
    }

    /*
     * Letzte vertikale Linie hinzufügen
     * Das grid geht normal über den Bildschirmrand, habe noch nicht verstanden warum, damit geht es aber auch...
     */
    sf::RectangleShape lastVerticalLine(sf::Vector2f(1, windowSize.y));
    lastVerticalLine.setPosition(windowSize.x - 1, startY);
    lastVerticalLine.setFillColor(lineColor);
    gridCells.push_back(lastVerticalLine);
}



void Window::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
        case sf::Keyboard::Escape:
        {
            destroy();
            break;
        }
        default:
        {
            break;
        }
    }
}