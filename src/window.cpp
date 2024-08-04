//
// Created by toby on 26.07.24.
//

#include "include/window.hpp"

#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <thread>
#include <chrono> // For adding delays

/*
 * Konstruktor für das Window-Objekt, initialisiert das Fenster mit definierten Dimensionen und Eigenschaften.
 */
Window::Window()
: myButton(BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, sf::Color::Blue, [this]() { this->breadthFirstSearch(); }),
  myVisualButton(BUTTON_X, BUTTON2_Y, BUTTON_WIDTH, BUTTON_HEIGHT, sf::Color::Green, [this]() { this->visualBreadthFirstSearch(); })
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Algorithmus", sf::Style::None | sf::Style::Titlebar | sf::Style::Close);
    gridMap.resize(GRID_HEIGHT / GRID_SIZE, std::vector<gridType>(GRID_WIDTH / GRID_SIZE, gridType::field));
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
    myButton.draw(window); // Zeichne den Button
    myVisualButton.draw(window); // Zeichne den Visual Button
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
                cell.setFillColor(sf::Color::Black); // Änderung zu transparentem Hintergrund
            } else if(gridMap[y][x] == gridType::path) {
                cell.setFillColor(sf::Color::Cyan);
            }
            window.draw(cell);
        }
    }
}

/*
 * Verarbeitet alle eingehenden Ereignisse und leitet entsprechende Aktionen ein.
 */
void Window::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        myButton.handleEvent(event, window);
        myVisualButton.handleEvent(event, window);
        handlePlayerInput(event, (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed));
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
    float startX = 0; // Startposition X
    float startY = 0; // Startposition Y
    sf::Color lineColor = sf::Color::Blue;
    gridCells.clear();

    // Horizontal
    for (float y = startY; y <= GRID_HEIGHT; y += GRID_SIZE)
    {
        sf::RectangleShape line(sf::Vector2f(GRID_WIDTH, 1)); // Beschränkt die Länge auf GRID_WIDTH
        line.setPosition(startX, y);
        line.setFillColor(lineColor);
        gridCells.push_back(line);
    }

    // Vertikale Linien
    for (float x = startX; x <= GRID_WIDTH; x += GRID_SIZE)
    {
        sf::RectangleShape line(sf::Vector2f(1, GRID_HEIGHT)); // Beschränkt die Höhe auf GRID_HEIGHT
        line.setPosition(x, startY);
        line.setFillColor(lineColor);
        gridCells.push_back(line);
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
 * Überprüft, ob die Maus innerhalb des Grids ist.
 */
bool Window::isMouseInGrid(sf::Vector2i mousePosition) {
    int gridX = mousePosition.x / GRID_SIZE;
    int gridY = mousePosition.y / GRID_SIZE;
    return gridX >= 0 && gridX < (GRID_WIDTH / GRID_SIZE) && gridY >= 0 && gridY < (GRID_HEIGHT / GRID_SIZE);
}

void Window::checkMouseInGrid(sf::Vector2i mousePosition)
{
    if (isMouseInGrid(mousePosition)) {
        std::cout << "Maus ist innerhalb des Gitters bei Position: " << mousePosition.x / GRID_SIZE << ", " << mousePosition.y / GRID_SIZE << std::endl;
    } else {
        std::cout << "Maus ist außerhalb des Gitterbereichs!" << std::endl;
    }
}

/*
 * Zeichnet den Mauszeiger, wenn die linke Maustaste gedrückt ist.
 */
void Window::drawMousePointer()
{
    // Holen der aktuellen Mausposition relativ zum Fenster
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    // Überprüfen, ob die linke Maustaste gedrückt ist
    if (!isLeftMouseButtonPressed || !isMouseInGrid(mousePosition))
    {
        return; // Wenn nicht gedrückt, nichts zeichnen
    }
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
 * Schaltet GridType bei drücken einer bestimmten taste
 */
void Window::toggleGridTypeAtMousePosition(sf::Vector2i mousePosition, gridType type)
{
    if (isMouseInGrid(mousePosition))
    {
        int gridX = mousePosition.x / GRID_SIZE;
        int gridY = mousePosition.y / GRID_SIZE;
        if (gridMap.size() > gridY && gridMap[gridY].size() > gridX) {
            gridMap[gridY][gridX] = type;
        }
    }
}

void Window::reconstructPath(const std::vector<std::vector<sf::Vector2i>>& predecessors, sf::Vector2i start, sf::Vector2i end) {
    sf::Vector2i step = end;
    while (step != start) {
        gridMap[step.y][step.x] = gridType::path; // Zeichne den Pfad
        step = predecessors[step.y][step.x];
        render();
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Visualisiere jeden Schritt der Pfadrekonstruktion
    }
}

void Window::breadthFirstSearch() {
    sf::Vector2i start(-1, -1);
    sf::Vector2i end(-1, -1);

    for (int y = 0; y < gridMap.size(); ++y) {
        for (int x = 0; x < gridMap[y].size(); ++x) {
            if (gridMap[y][x] == gridType::start) {
                start = {x, y};
            } else if (gridMap[y][x] == gridType::end) {
                end = {x, y};
            }
        }
    }

    if (start.x == -1 || end.x == -1) {
        std::cerr << "Start oder End Punkt wurde nicht gesetzt." << std::endl;
        return;
    }

    std::vector<std::vector<bool>> visited(gridMap.size(), std::vector<bool>(gridMap[0].size(), false));
    std::vector<std::vector<sf::Vector2i>> predecessors(gridMap.size(), std::vector<sf::Vector2i>(gridMap[0].size(), {-1, -1}));
    std::queue<sf::Vector2i> queue;
    queue.push(start);
    visited[start.y][start.x] = true;

    std::vector<sf::Vector2i> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    bool found = false;

    while (!queue.empty() && !found) {
        sf::Vector2i current = queue.front();
        queue.pop();

        for (const auto& dir : directions) {
            sf::Vector2i neighbor = {current.x + dir.x, current.y + dir.y};

            if (neighbor.x >= 0 && neighbor.x < gridMap[0].size() &&
                neighbor.y >= 0 && neighbor.y < gridMap.size() &&
                !visited[neighbor.y][neighbor.x] &&
                (gridMap[neighbor.y][neighbor.x] == gridType::field || gridMap[neighbor.y][neighbor.x] == gridType::end)) {

                visited[neighbor.y][neighbor.x] = true;
                predecessors[neighbor.y][neighbor.x] = current;
                queue.push(neighbor);

                if (gridMap[neighbor.y][neighbor.x] == gridType::end) {
                    found = true;
                    break;
                }
            }
        }
    }

    if (found) {
        sf::Vector2i step = end;
        while (step != start) {
            gridMap[step.y][step.x] = gridType::path;
            step = predecessors[step.y][step.x];
        }
    } else {
        std::cerr << "Kein Pfad gefunden." << std::endl;
    }
}

void Window::visualBreadthFirstSearch() {
    sf::Vector2i start(-1, -1);
    sf::Vector2i end(-1, -1);

    // Finde Start- und Endpunkte
    for (int y = 0; y < gridMap.size(); ++y) {
        for (int x = 0; x < gridMap[y].size(); ++x) {
            if (gridMap[y][x] == gridType::start) {
                start = {x, y};
            } else if (gridMap[y][x] == gridType::end) {
                end = {x, y};
            }
        }
    }

    if (start.x == -1 || end.x == -1) {
        std::cerr << "Start oder Endpunkt nicht gesetzt." << std::endl;
        return;
    }

    std::vector<std::vector<bool>> visited(gridMap.size(), std::vector<bool>(gridMap[0].size(), false));
    std::queue<sf::Vector2i> queue;
    queue.push(start);
    visited[start.y][start.x] = true;
    gridMap[start.y][start.x] = gridType::path; // Markiere den Startpunkt auf dem Grid
    render();
    window.display();

    bool found = false;
    std::vector<sf::Vector2i> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    while (!queue.empty() && !found) {
        sf::Vector2i current = queue.front();
        queue.pop();

        if (current == end) {
            found = true; // Endpunkt erreicht
            break;
        }

        for (const auto& dir : directions) {
            sf::Vector2i neighbor = {current.x + dir.x, current.y + dir.y};

            if (neighbor.x >= 0 && neighbor.x < gridMap[0].size() && neighbor.y >= 0 && neighbor.y < gridMap.size()) {
                if (!visited[neighbor.y][neighbor.x] && (gridMap[neighbor.y][neighbor.x] == gridType::field || neighbor == end)) {
                    visited[neighbor.y][neighbor.x] = true;
                    gridMap[neighbor.y][neighbor.x] = gridType::path;
                    queue.push(neighbor);
                    render();
                    window.display();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));

                    if (neighbor == end) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    if (found) {
        std::cout << "Endpunkt erreicht." << std::endl;
    } else {
        std::cout << "Kein Pfad zum Endpunkt gefunden." << std::endl;
    }
}


