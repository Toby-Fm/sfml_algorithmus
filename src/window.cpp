//
// Created by toby on 26.07.24.
//

#include "include/window.hpp"
#include <cmath>
#include <string>
#include <cmath>

Window::Window() //: isLeftMouseButtonPressed(false)
{
    window.create(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "SFML Algorithmus", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    // Grid in den background zeichnen
    backgroundGrid();
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
        bool isPressed = (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed);
        handlePlayerInput(event, isPressed);
    }
}


// Objekte on Screen
void Window::drawObjectsOnScreen()
{
    for (const auto& cell : gridCells)
    {
        window.draw(cell);
    }
    // Zeichnet Mauspointer
    drawMousePointer();
}

// Grid in background
void Window::backgroundGrid()
{
    sf::Vector2u windowSize = window.getSize();
    int gridSize = 50;
    float startX = 0; // Startposition X
    float startY = 0; // Startposition Y

    sf::Color lineColor = sf::Color::White;
    gridCells.clear();

    // Horizontale Linien
    for (float y = startY; y < windowSize.y; y += gridSize)
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
    for (float x = startX; x < windowSize.x; x += gridSize)
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

void Window::handlePlayerInput(sf::Event event, bool isPressed)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                {
                    if (isPressed)
                        destroy();
                    break;
                }
            default:
                {
                    break;
                }
            }
            break;
        }

        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                isLeftMouseButtonPressed = isPressed;
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

void Window::drawMousePointer() {
    // Überprüfen, ob die linke Maustaste gedrückt ist
    if (!isLeftMouseButtonPressed) {
        return; // Wenn nicht gedrückt, nichts zeichnen
    }

    // Holen der aktuellen Mausposition relativ zum Fenster
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Erstellen eines Kreis-Shape-Objekts für den Mauszeiger mit Radius 5
    sf::CircleShape mousePointer(5.f);
    mousePointer.setFillColor(sf::Color::Red);
    // Setzen der Position des Mauszeigers basierend auf der Mausposition
    mousePointer.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    // Zeichnen des Mauszeigers im Fenster
    window.draw(mousePointer);

    if (mousePosition.x < 0 || mousePosition.x > window.getSize().x || mousePosition.y < 0 || mousePosition.y > window.getSize().y) {
        std::cout << "Maus ist außerhalb des Fensters!" << std::endl;
    } else {
        // Ausgabe der aktuellen Mausposition, wenn sie innerhalb des Fensters ist
        std::cout << "X: " << mousePosition.x << " Y: " << mousePosition.y << std::endl;

        // Zeichnen von Linien vom Mauszeiger aus in verschiedene Richtungen
        int numberOfLines = 4; // Anzahl der Linien
        float angleStep = 2 * 3.14159f / numberOfLines; // Schrittweite für den Winkel in Radians

        for (int i = 0; i < numberOfLines; ++i) {
            // Berechnen des Winkels für die aktuelle Linie
            float angle = i * angleStep;
            // Berechnen der Richtungsvektoren der Linie (dx, dy) basierend auf dem Winkel
            float dx = std::cos(angle);
            float dy = std::sin(angle);

            // Initialisieren von tMax mit dem maximalen Float-Wert
            float tMax = std::numeric_limits<float>::max();

            // Berechnen des maximalen t-Wertes für die x-Richtung
            if (dx != 0) {
                float t1 = (0 - mousePosition.x) / dx;
                float t2 = (window.getSize().x - mousePosition.x) / dx;
                tMax = std::min(tMax, std::max(t1, t2));
            }
            // Berechnen des maximalen t-Wertes für die y-Richtung
            if (dy != 0) {
                float t1 = (0 - mousePosition.y) / dy;
                float t2 = (window.getSize().y - mousePosition.y) / dy;
                tMax = std::min(tMax, std::max(t1, t2));
            }

            // Berechnen des Endpunkts der Linie basierend auf tMax
            sf::Vector2f endPoint(mousePosition.x + tMax * dx, mousePosition.y + tMax * dy);
            // Erstellen des Linien-Arrays mit Start- und Endpunkt
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)), sf::Color::Red),
                sf::Vertex(endPoint, sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
}

