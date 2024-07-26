//
// Created by toby on 26.07.24.
//

#include "include/window.hpp"
#include <cmath>

Window::Window()
{
    window.create(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "SFML Algorithmus", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    // Grid in den background zeichnen
    backgroundGrid();// Initiale Erstellung des Gitters mit zufälligen Farben
}

// Wenn das Fenster läuft
void Window::run() {
    while (window.isOpen())
    {
        while (window.isOpen())
        {
            ProcessEvents();
            render();
        }
    }
}

// Löscht den Bildschirm
void Window::clear()
{
    window.clear(sf::Color::Transparent);
}

// Rendert das Fenster
void Window::render() {
    clear();
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
    sf::Event event{};
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
    int gridSize = 100;
    sf::Vector2u windowSize = window.getSize(); // Dynamische abfrage für Fenstergröße

    gridCells.clear();

    for (int x = 0; x < windowSize.x; x += gridSize)
    {
        for (int y = 0; y < windowSize.y; y += gridSize)
        {
            sf::RectangleShape cell(sf::Vector2f(gridSize, gridSize));
            cell.setPosition(x, y);
            cell.setOutlineColor(sf::Color::White);
            cell.setOutlineThickness(1);

            gridCells.push_back(cell);
        }
    }
}
