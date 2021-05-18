#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include "SNAKE_class.h"
#include <vector>
#include <map>

Snake::Snake()
{
    size = 30;
    lenght = 1;
    level = 1;
    direction = 1;
    window_size_x = 600;
    window_size_y = 600;
    time_to_delay = 0;
    time_delay = 0.1;
    show_rock_time = 0.0001;
    show_rock_time_variable = 0.0001;

    apple.x = rand() % window_size_x/size;
    apple.y = rand() % window_size_y/size;

    rock.x = rand() % window_size_x/size;
    rock.y = rand() % window_size_y/size;
}

Snake::~Snake()
{
}

// Menu::Menu(int width, int height){
//    if(!font.loadFromFile("C:/Users/mtymi/OneDrive/Pulpit/Studia/2 semestr/PSiO/Labolatoria/projekt_SNAKE/TTF.ttf")){
//        std::cerr << "Could not load texture" << std::endl;
//    }

//    menu[0].setFont(font);
//    menu[0].setColor(sf::Color::Red);
//    menu[0].setString("PLAY");
//    menu[0].setPosition(sf::Vector2f(width/2 , height /(MAX_NUMBER_OF_ITEMS +1) * 1));

//    menu[0].setFont(font);
//    menu[0].setColor(sf::Color::White);
//    menu[0].setString("OPTIONS");
//    menu[0].setPosition(sf::Vector2f(width/2 , height /(MAX_NUMBER_OF_ITEMS +1) * 2));

//    menu[0].setFont(font);
//    menu[0].setColor(sf::Color::White);
//    menu[0].setString("EXIT");
//    menu[0].setPosition(sf::Vector2f(width/2 , height /(MAX_NUMBER_OF_ITEMS +1) * 3));
// }

// Menu::~Menu()
// {
// }

// void Menu::draw(sf::RenderWindow &window){
//     for(int i = 0; i < MAX_NUMBER_OF_ITEMS; i++){
//         window.draw(menu[i]);
//     }
// }

void Snake::set_size(){
    if(level == 1){
        size = 30;
        show_rock_time_variable = 0.0001;
    }else if(level == 2){
        size = 25;
        show_rock_time_variable = 0.0005;
    }else if(level == 3){
        size = 20;
        show_rock_time_variable = 0.001;
    }
}

void Snake::set_direction(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = 4;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = 3;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = 2;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = 1;
        }else {}
}

void Snake::set_rock_position(){
    if(show_rock_time > time_delay){
        rock.x = rand() % (window_size_x/size);
        rock.y = rand() % (window_size_y/size);
        position_of_rock_x.emplace_back(rock.x);
        position_of_rock_y.emplace_back(rock.y);
        show_rock_time = 0.0001;
    }
}

void Snake::snake_move(){
    for(int i = lenght; i > 0; i--){
        ssnake[i].x = ssnake[i - 1].x;
        ssnake[i].y = ssnake[i - 1].y;
    }
}

void Snake::snake_direction(){
    if(direction == 1){
        ssnake[0].x += 1;
    }else if(direction == 2){
        ssnake[0].x -= 1;
    }else if(direction == 3){
        ssnake[0].y -= 1;
    }else if(direction == 4){
        ssnake[0].y += 1;
    }
}

void Snake::crash_with_rock(){
    for(unsigned long long i = 0; i < position_of_rock_x.size(); i++){
        if(ssnake[0].x == position_of_rock_x[i] && ssnake[0].y == position_of_rock_y[i] && lenght > 1){
            lenght --;
            position_of_rock_x[i] = rand() % window_size_x/size;
            position_of_rock_y[i] = rand() % window_size_y/size;
        }
    }
}

void Snake::feed_me(){
    if(ssnake[0].x == apple.x && ssnake[0].y == apple.y){
        lenght ++;
        apple.x = rand() % window_size_x/size;
        apple.y = rand() % window_size_y/size;
    }
}

void Snake::apple__rock(){
    for(unsigned long long i = 0; i < position_of_rock_x.size(); i++){
        if(apple.x == position_of_rock_x[i] && apple.y == position_of_rock_y[i]){
            lenght --;
            apple.x = rand() % window_size_x/size;
            apple.y = rand() % window_size_y/size;
        }
    }
}

void Snake::suicide(){
    for(int i = 1; i < lenght; i++){
       if(ssnake[0].x == ssnake[i].x && ssnake[0].y == ssnake[i].y){
           lenght = 1;
       }
    }
}

void Snake::through_walls(){
    if(ssnake[0].x >= window_size_x/size){
        ssnake[0].x = 0;
    }

    if(ssnake[0].x < 0){
        ssnake[0].x = window_size_x/size;
    }

    if(ssnake[0].y >= window_size_y/size){
        ssnake[0].y = 0;
    }

    if(ssnake[0].y < 0){
        ssnake[0].y = window_size_y/size;
    }
}

void Snake::level_check(){
    if(lenght == 20){
        lenght = 1;
        level ++;
    }
}

void Snake::animated(){

    set_size();

    sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y), "SNAKE by Michal Tyminski");

//     Menu menu(window_size_x, window_size_y);
//     menu.draw(window);

    sf::Clock clock;
    srand(time(NULL));

    sf::RectangleShape background, shape_snake, shape_apple, shape_rock;
    sf::Vector2f SIZE(size, size);

    background.setSize(SIZE);
    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::White);

    shape_snake.setSize(SIZE);
    shape_snake.setFillColor(sf::Color::Green);
    shape_snake.setOutlineThickness(1);
    shape_snake.setOutlineColor(sf::Color::White);

    shape_apple.setSize(SIZE);
    shape_apple.setFillColor(sf::Color::Red);
    shape_apple.setOutlineThickness(1);
    shape_apple.setOutlineColor(sf::Color::White);

    shape_rock.setSize(SIZE);
    shape_rock.setFillColor(sf::Color::Yellow);
    shape_rock.setOutlineThickness(1);
    shape_rock.setOutlineColor(sf::Color::White);

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        time_to_delay += time;

        set_direction();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        show_rock_time += show_rock_time_variable;

        if(time_to_delay > time_delay){

            set_size();
            time_to_delay = 0;
            set_rock_position();
            snake_move();
            snake_direction();
            crash_with_rock();
            feed_me();
            suicide();
            through_walls();
            level_check();
        }

       window.clear(sf::Color::Black);

       for(int i = 0; i < window_size_x/size; i++){ // drawing background
           for (int j = 0; j < window_size_y/size; j++){
               background.setPosition(j * size, i * size);
               window.draw(background);
           }
       }

       shape_apple.setPosition(apple.x * size, apple.y * size); // drawing apple
       window.draw(shape_apple);

       for(unsigned long long i = 0; i < position_of_rock_x.size(); i++){ // drawing rocks
           shape_rock.setPosition(position_of_rock_x[i] * size, position_of_rock_y[i] * size);
           window.draw(shape_rock);
       }

       for(int i = 0; i < lenght; i++){ // drawing snake
           shape_snake.setPosition(ssnake[i].x * size, ssnake[i].y * size);
           window.draw(shape_snake);
       }

        window.display();
    }
}
