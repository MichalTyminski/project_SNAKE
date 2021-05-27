#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H

#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics/Text.hpp>
#include <ostream>
#include <iostream>
#include "Board_class.h"

class Board;

class Snake : public sf::RectangleShape{
public:
    Snake(sf::Color, int control);
    virtual ~Snake();

    struct StructSnake
    {
        int x;
        int y;
    }ssnake[100];



    sf::Color color;
    int control;
    void set_direction(int control);
    void snake_move();
    void snake_direction();
    void crash_with_rock();
    void feed_me();
    void suicide();
    void through_walls();
    Board *board;

    int lenght;
    int direction;

private:


};










//<a href="http://www.onlinewebfonts.com">oNline Web Fonts</a>
#endif // SNAKE_CLASS_H
