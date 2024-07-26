//
// Created by toby on 26.07.24.
//

#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string &title);
    void run();

private:
    sf::RenderWindow window;
};



#endif //WINDOW_HPP
