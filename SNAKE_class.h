#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>
#include <ostream>
#include <iostream>
#include "Board_class.h"

class Board;

class Snake : public sf::RectangleShape{
public:
    Snake(sf::Texture texture, int control);
    virtual ~Snake();

    struct StructSnake
    {
        int x;
        int y;
    }ssnake[100];

    void set_direction(int control);
    void snake_move();
    void snake_direction();
    void crash_with_rock();
    void feed_me();
    void suicide();
    void snakes_collision();
    void through_walls();
    void get_bonus();
    Board *board;

    sf::Texture snake_texture;
    int control;
    int lenght;
    int direction;
    float lifes;
    bool direction_changed;


private:
    sf::SoundBuffer apple_buffer;
    sf::Sound apple_sound;
    sf::SoundBuffer rock_buffer;
    sf::Sound rock_sound;
    sf::SoundBuffer bonus_buffer;
    sf::Sound bonus_sound;
};
#endif // SNAKE_CLASS_H
