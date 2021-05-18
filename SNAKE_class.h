#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H

#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics/Text.hpp>
#include <ostream>
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 3

class Snake : public sf::RectangleShape{
public:
    Snake();
    virtual ~Snake();

    struct StructSnake
    {
        int x;
        int y;
    }ssnake[100];

    struct StructFruit
    {
        int x;
        int y;
    }apple;

    struct StructRock
    {
        int x;
        int y;
    }rock;

    void set_size();
    void set_direction();
    void animated();
    void set_rock_position();
    void snake_move();
    void snake_direction();
    void crash_with_rock();
    void feed_me();
    void apple__rock();
    void suicide();
    void through_walls();
    void level_check();

private:

    int size;
    int lenght;
    int level;
    int direction;
    int window_size_x;
    int window_size_y;
    float time_to_delay;
    float time_delay;
    std::vector<int> position_of_rock_x;
    std::vector<int> position_of_rock_y;
    float show_rock_time;
    float show_rock_time_variable;
};

// class Menu{
// public:
//     Menu(int width, int height);
//     ~Menu();

//     void draw(sf::RenderWindow &window);
//     void MoveUp();
//     void MoveDown();

// private:
//     int selecteditemindex;
//     sf::Font font;
//     sf::Text menu[MAX_NUMBER_OF_ITEMS];

// };








//<a href="http://www.onlinewebfonts.com">oNline Web Fonts</a>
#endif // SNAKE_CLASS_H
