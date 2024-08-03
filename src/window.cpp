//
// Created by toby on 26.07.24.
//

#include "include/window.hpp"
#include <cmath>
#include <string>
#include <cmath>

/*
 * Konstruktor für das Window-Objekt, initialisiert das Fenster mit definierten Dimensionen und Eigenschaften.
 */
Window::Window() //: isLeftMouseButtonPressed(false)
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Algorithmus", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    gridMap.resize(WINDOW_HEIGHT / GRID_SIZE, std::vector<gridType>(WINDOW_WIDTH / GRID_SIZE, gridType::field));
    backgroundGrid();
}

/*
 * Hauptausführungsschleife des Fensters, behandelt Ereignisse und rendert die Szene.
 */
void Window::run()
{
    while (window.isOpen())
    {
        ProcessEvents();
        // Rufe die Funktion mit 'wall' auf beim dauerhaften klicken
        if (isRightMouseButtonPressed) {
            toggleGridTypeAtMousePosition(sf::Mouse::getPosition(window), gridType::wall);
        }
        render();
    }
}

/*
 * Löscht den Bildschirm, um für das neue Rendering vorzubereiten.
 */
void Window::clear()
{
    window.clear(sf::Color::Black);
}

/*
 * Verantwortlich für das Zeichnen aller Objekte im Fenster.
 */
void Window::render()
{
    clear();
    drawGridType();
    drawObjectsOnScreen();
    window.display();
}

/*
 * Schließt das Fenster und beendet das Programm.
 */
void Window::destroy()
{
    std::cout << "Fenster wird geschlossen" << std::endl;
    window.close();
}

/*
 * Zeichnet das Grid, basierend auf dem aktuellen Zustand der gridMap.
 */
void Window::drawGridType()
{
    for (int y = 0; y < gridMap.size(); ++y) {
        for (int x = 0; x < gridMap[y].size(); ++x) {
            sf::RectangleShape cell(sf::Vector2f(GRID_SIZE - 2, GRID_SIZE - 2)); // leichter Abstand für visuelle Trennung
            cell.setPosition(x * GRID_SIZE + 1, y * GRID_SIZE + 1);

            if (gridMap[y][x] == gridType::wall) { // Wand
                cell.setFillColor(sf::Color::White);
            } else if(gridMap[y][x] == gridType::start) { // Startpunkt
                cell.setFillColor(sf::Color::Green);
            } else if(gridMap[y][x] == gridType::end) { // Endpunkt
                cell.setFillColor(sf::Color::Red);
            } else if(gridMap[y][x] == gridType::field) { // Normales feld
                cell.setFillColor(sf::Color::Transparent); // Änderung zu transparentem Hintergrund
            }
            window.draw(cell);
        }
    }
}

/*
 * Verarbeitet alle eingehenden Ereignisse und leitet entsprechende Aktionen ein.
 */
void Window::ProcessEvents()
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        bool isPressed = (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed);
        handlePlayerInput(event, isPressed);
    }
}


/*
 * Zeichnet zusätzliche Objekte auf dem Bildschirm, die nicht Teil des Grids sind.
 */
void Window::drawObjectsOnScreen()
{
    for (const auto& cell : gridCells)
    {
        window.draw(cell);
    }
    // Zeichnet Mauspointer
    drawMousePointer();
}

/*
 * Erstellt das Hintergrundgitter des Fensters.
 */
void Window::backgroundGrid()
{
    sf::Vector2u windowSize = window.getSize();
    float startX = 0; // Startposition X
    float startY = 0; // Startposition Y
    sf::Color lineColor = sf::Color::White;
    gridCells.clear();

    // Horizontal
    for (float y = startY; y <= GRID_HEIGHT; y += GRID_SIZE)
    {
        sf::RectangleShape line(sf::Vector2f(GRID_WIDTH, 1)); // Beschränkt die Länge auf GRID_WIDTH
        line.setPosition(startX, y);
        line.setFillColor(lineColor);
        gridCells.push_back(line);
    }

    // Letzte horizontale Linie nur hinzufügen, wenn sie innerhalb der GRID_HEIGHT ist
    if constexpr (GRID_HEIGHT % GRID_SIZE != 0) {
        sf::RectangleShape lastHorizontalLine(sf::Vector2f(GRID_WIDTH, 1));
        lastHorizontalLine.setPosition(startX, GRID_HEIGHT - 1);
        lastHorizontalLine.setFillColor(lineColor);
        gridCells.push_back(lastHorizontalLine);
    }

    // Vertikale Linien
    for (float x = startX; x <= GRID_WIDTH; x += GRID_SIZE)
    {
        sf::RectangleShape line(sf::Vector2f(1, GRID_HEIGHT)); // Beschränkt die Höhe auf GRID_HEIGHT
        line.setPosition(x, startY);
        line.setFillColor(lineColor);
        gridCells.push_back(line);
    }

    // Letzte vertikale Linie nur hinzufügen, wenn sie innerhalb der GRID_WIDTH ist
    if constexpr (GRID_WIDTH % GRID_SIZE != 0) {
        sf::RectangleShape lastVerticalLine(sf::Vector2f(1, GRID_HEIGHT));
        lastVerticalLine.setPosition(GRID_WIDTH - 1, startY);
        lastVerticalLine.setFillColor(lineColor);
        gridCells.push_back(lastVerticalLine);
    }
}

/*
 * Behandelt die Eingaben der Spieler, sowohl von der Tastatur als auch von der Maus.
 */
void Window::handlePlayerInput(sf::Event event, bool isPressed)
{
    switch (event.type)
    {
        // Keyboard events (Ist Pressed or Not)
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
                case sf::Keyboard::S:
                {
                    if(isPressed)
                    {
                        // Rufe die Funktion mit 'start' auf beim einmaligen klicken
                        toggleGridTypeAtMousePosition(sf::Mouse::getPosition(window), gridType::start);
                    }
                    break;
                }
                case sf::Keyboard::E:
                {
                    if(isPressed)
                    {
                        // Rufe die Funktion mit 'end' auf beim einmaligen klicken
                        toggleGridTypeAtMousePosition(sf::Mouse::getPosition(window), gridType::end);
                    }
                    break;
                }
                case sf::Keyboard::D:
                {
                    if(isPressed)
                    {
                        // Rufe die Funktion mit 'field' auf beim einmaligen klicken
                        toggleGridTypeAtMousePosition(sf::Mouse::getPosition(window), gridType::field);
                    }
                    break;
                }
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
        // Maus events (Ist Pressed or Not)
        case sf::Event::MouseButtonPressed: // Maustaste ist gedrückt
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                isLeftMouseButtonPressed = true;
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = true;
            }
            break;
        }

        case sf::Event::MouseButtonReleased: // Maustaste ist losgelassen
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                isLeftMouseButtonPressed = false;
            }
            if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMouseButtonPressed = false;
            }
            break;
        }

        default:
        {
            break;
        }
    }
}

/*
 * Zeichnet den Mauszeiger, wenn die linke Maustaste gedrückt ist.
 */
void Window::drawMousePointer()
{
    // Überprüfen, ob die linke Maustaste gedrückt ist
    if (!isLeftMouseButtonPressed)
    {
        return; // Wenn nicht gedrückt, nichts zeichnen
    }

    // Holen der aktuellen Mausposition relativ zum Fenster
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    // Überprüfe, ob die Maus in einem Gitterfeld ist
    checkMouseInGrid(mousePosition);

    // Erstellen eines Kreis-Shape-Objekts für den Mauszeiger mit Radius 5
    sf::CircleShape mousePointer(5.f);
    mousePointer.setFillColor(sf::Color::Red);
    // Setzen der Position des Mauszeigers basierend auf der Mausposition
    mousePointer.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    // Zeichnen des Mauszeigers im Fenster
    window.draw(mousePointer);

    if (mousePosition.x < 0 || mousePosition.x > window.getSize().x || mousePosition.y < 0 || mousePosition.y > window.getSize().y)
    {
        std::cout << "Maus ist außerhalb des Fensters!" << std::endl;
    }
    else
    {
        // Ausgabe der aktuellen Mausposition, wenn sie innerhalb des Fensters ist
        std::cout << "X: " << mousePosition.x << " Y: " << mousePosition.y << std::endl;

        // Zeichnen von Linien vom Mauszeiger aus in verschiedene Richtungen
        constexpr int numberOfLines = 4; // Anzahl der Linien
        constexpr float angleStep = 2 * 3.14159f / numberOfLines; // Schrittweite für den Winkel in Radians

        for (int i = 0; i < numberOfLines; ++i)
        {
            // Berechnen des Winkels für die aktuelle Linie
            float angle = i * angleStep;
            // Berechnen der Richtungsvektoren der Linie (dx, dy) basierend auf dem Winkel
            float dx = std::cos(angle);
            float dy = std::sin(angle);

            // Initialisieren von tMax mit dem maximalen Float-Wert
            float tMax = std::numeric_limits<float>::max();

            // Berechnen des maximalen t-Wertes für die x-Richtung
            if (dx != 0)
            {
                float t1 = (0 - mousePosition.x) / dx;
                float t2 = (window.getSize().x - mousePosition.x) / dx;
                tMax = std::min(tMax, std::max(t1, t2));
            }
            // Berechnen des maximalen t-Wertes für die y-Richtung
            if (dy != 0)
            {
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

/*
 * Überprüft, ob die Maus innerhalb des Grids ist.
 */
void Window::checkMouseInGrid(sf::Vector2i mousePosition)
{
    const int gridX = mousePosition.x / GRID_SIZE;
    const int gridY = mousePosition.y / GRID_SIZE;

    sf::Vector2u windowSize = window.getSize();
    const unsigned int maxX = windowSize.x / GRID_SIZE;
    const unsigned int maxY = windowSize.y / GRID_SIZE;

    if (gridX >= 0 && gridX < maxX && gridY >= 0 && gridY < maxY)
    {
        std::cout << "Die Maus ist innerhalb des Gitters bei Grid Position: " << gridX << ", " << gridY << std::endl;
    }
    else
    {
        std::cout << "Maus außerhalb des Gitterbereichs!" << std::endl;
    }
}

/*
 * Schaltet GridType bei drücken einer bestimmten taste
 */
void Window::toggleGridTypeAtMousePosition(sf::Vector2i mousePosition, gridType type)
{
    int gridX = mousePosition.x / GRID_SIZE;
    int gridY = mousePosition.y / GRID_SIZE;

    if (gridX >= 0 && gridX < gridMap[0].size() && gridY >= 0 && gridY < gridMap.size())
    {
        gridMap[gridY][gridX] = type; // Setze die Zelle basierend auf dem übergebenen Typ
    }
}
