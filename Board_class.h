#ifndef BOARD_CLASS_H
#define BOARD_CLASS_H

#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics/Text.hpp>
#include <ostream>
#include <iostream>
#include "SNAKE_class.h"

class Snake;

class Board
{
public:
    Board();
    virtual ~Board();

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

    struct StruckBonus
    {
        int x;
        int y;
    }bonus;

    void set_size();
    void level_check();
    void set_rock_position();
    void apple_rock_bonus();
    void game();
    void read_from_file();

    int size;
    int level;
    int window_size_x;
    int window_size_y;
    std::vector<int> position_of_rock_x;
    std::vector<int> position_of_rock_y;
    float time_to_delay;
    float time_delay;
    float time_between_colision;
    float time_to_colison;
    float show_rock_time;
    float show_rock_time_variable;
    float show_bonus_time;
    float show_bonus_time_variable;
    std::vector<Snake*> snakes;
    bool level_change;
    bool every_snake_is_alive;
    int fallen;
    float variable_of_speed;
    float constant_of_speed;
    int size_to_next_level;
    bool is_paused;

private:
};
#endif // BOARD_CLASS_H
