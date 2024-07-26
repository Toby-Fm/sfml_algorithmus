//
// Created by toby on 26.07.24.
//

#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <deque>
#include <cstdlib>
#include <ctime>

#define WINDOW_HEIGHT 1400
#define WINDOW_WIDTH 800

class Window {
public:
    Window();
    void run();
    void clear();
    void render();
    void destroy();

private:
    static void ProcessEvents();
    void drawObjectsOnScreen();
    void backgroundGrid();

private:
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> gridCells;
    bool movingLeftCricle = false, movingRightCricle = false, movingUpCricle = false, movingDownCricle = false;
    bool movingLeftRec = false, movingRightRec = false, movingUpRec = false, movingDownRec = false;
};



#endif //WINDOW_HPP
