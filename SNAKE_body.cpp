#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include <sstream>
#include "SNAKE_class.h"
#include "Board_class.h"
#include <vector>
#include <map>

Snake::Snake(sf::Texture texture_, int control_)
{
    snake_texture = texture_;
    control = control_;
    lenght = 1;
    direction = 1;
    lifes = 3;
}

Snake::~Snake()
{
}

Board::Board(){
    size = 30;
    window_size_x = 600;
    window_size_y = 600;
    time_to_delay = 0;
    time_delay = 0.1;
    show_rock_time = 0.0001;
    show_rock_time_variable = 0.0001;
    level = 1;
    level_change = false;
    every_snake_is_alive = true;

    apple.x = rand() % window_size_x/size;
    apple.y = rand() % window_size_y/size;

    rock.x = rand() % window_size_x/size;
    rock.y = rand() % window_size_y/size;
}

Board::~Board()
{
}

void Snake::set_direction(int control){
    if(control == 1){ //sterowanie za pomoca strzalek
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = 4;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = 3;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = 2;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = 1;
        }else {}
    }else if(control == 2){ //sterowanie za pomoca wasd
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction = 4;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction = 3;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction = 2;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = 1;
        }else {}
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
    for(unsigned long long i = 0; i < board -> position_of_rock_x.size(); i++){
        if(ssnake[0].x == board -> position_of_rock_x[i] && ssnake[0].y == board -> position_of_rock_y[i] && lenght > 1){
            lenght --;
            lifes --;
            board -> position_of_rock_x[i] = rand() % board -> window_size_x/board -> size;
            board -> position_of_rock_y[i] = rand() % board -> window_size_y/board -> size;
        }
    }
}

void Snake::feed_me(){
    if(ssnake[0].x == board -> apple.x && ssnake[0].y == board -> apple.y){
        lenght ++;
        board -> apple.x = rand() % board -> window_size_x/board -> size;
        board -> apple.y = rand() % board -> window_size_y/board -> size;
    }
}

void Snake::suicide(){
    for(int i = 1; i < lenght; i++){
        if(ssnake[0].x == ssnake[i].x && ssnake[0].y == ssnake[i].y){
            lenght = 1;
        }
    }
}

//void Snake::snakes_collision(int number_of_snakes, int lenght){
//    std::vector<Snake*> snakes_;
//    for(auto snake : board -> snakes){
//        snakes_.push_back(snake);
//    }
//    for(int i = 0; i = number_of_snakes; i++){
//        for(int j = 0; j = lenght; j++){
//            if(snakes_[i]->ssnake[0].x == snakes_[i+1]->ssnake[j].x && snakes_[i]->ssnake[0].y == snakes_[i+1]->ssnake[j].y){
//                snakes_[i]->lenght = 1;
//            }
//        }
//    }
//}

void Snake::through_walls(){
    if(ssnake[0].x >= board -> window_size_x/board -> size){
        ssnake[0].x = 0;
    }

    if(ssnake[0].x < 0){
        ssnake[0].x = board -> window_size_x/board -> size;
    }

    if(ssnake[0].y >= board -> window_size_y/board -> size){
        ssnake[0].y = 0;
    }

    if(ssnake[0].y < 0){
        ssnake[0].y = (board -> window_size_y/board -> size)-1;
    }
}

void Board::set_size(){
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

void Board::level_check(){
    for(auto snake : snakes){
        if(snake -> lenght == 5){
            snake -> lenght = 1;
            level ++;
            level_change = true;
        }
    }
}

void Board::set_rock_position(){
    if(show_rock_time > time_delay){
        rock.x = rand() % (window_size_x/size);
        rock.y = rand() % (window_size_y/size);
        position_of_rock_x.emplace_back(rock.x);
        position_of_rock_y.emplace_back(rock.y);
        show_rock_time = 0.0001;
    }
}

void Board::apple__rock(){
    for(unsigned long long i = 0; i < position_of_rock_x.size(); i++){
        if(apple.x == position_of_rock_x[i] && apple.y == position_of_rock_y[i]){
            apple.x = rand() % window_size_x/size;
            apple.y = rand() % window_size_y/size;
        }
    }
}

void Board::game(){

    set_size();

    sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y+50), "SNAKE by Michal Tyminski");

    sf::Texture text_1, text_2, text_3, text_4, text_5, text_6;
    if (!text_1.loadFromFile("./level_complete.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_level_complete;
    text_level_complete.setTexture(text_1);
    text_level_complete.setPosition(window_size_x/2 - text_level_complete.getGlobalBounds().width/2, 100);

    if (!text_2.loadFromFile("./contiune.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_contiune;
    text_contiune.setTexture(text_2);
    text_contiune.setPosition(window_size_x/2 - text_contiune.getGlobalBounds().width/2, 275);

    if (!text_3.loadFromFile("./exite.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_exit;
    text_exit.setTexture(text_3);
    text_exit.setPosition(window_size_x/2 - text_exit.getGlobalBounds().width/2, 350);

    if (!text_4.loadFromFile("./win.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_win;
    text_win.setTexture(text_4);
    text_win.setPosition(window_size_x/2 - text_win.getGlobalBounds().width/2, 100);

    if (!text_5.loadFromFile("./thanks.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_thanks;
    text_thanks.setTexture(text_5);
    text_thanks.setPosition(window_size_x/2 - text_thanks.getGlobalBounds().width/2, 480);

    if (!text_6.loadFromFile("./gameover.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_gameover;
    text_gameover.setTexture(text_6);
    text_gameover.setPosition(window_size_x/2 - text_gameover.getGlobalBounds().width/2, 100);

    sf::Texture snake_, snake2_, rock_;

    if (!snake_.loadFromFile("./SnakeSkin.jpeg")) {
        std::cerr << "Could not load texture" << std::endl;
    }

    if (!snake2_.loadFromFile("./snakeskin.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
    }

    if (!rock_.loadFromFile("./rock.png")) {
        std::cerr << "Could not load texture" << std::endl;
    }

    //show data
    int points1, points2, lifes1, lifes2;

    sf::Font font;
    if(!font.loadFromFile("Padauk-Regular.ttf")){
            std::cout << "ERROR" << std::endl;
    }
    sf::Text text_points, text_points1, text_points2, text_lifes, text_lifes1, text_lifes2;
    sf::Vector2f rectanglesize(20,20);
    sf::RectangleShape rectangle1p, rectangle2p, rectangle1l, rectangle2l;

    text_points.setFont(font);
    text_points.setString("Points: ");
    text_points.setCharacterSize(24);
    text_points.setPosition(5,610);

    rectangle1p.setPosition(80, 615);
    rectangle1p.setSize(rectanglesize);
    rectangle1p.setTexture(&snake_);

    rectangle2p.setPosition(130, 615);
    rectangle2p.setSize(rectanglesize);
    rectangle2p.setTexture(&snake2_);

    text_lifes.setFont(font);
    text_lifes.setString("Lifes: ");
    text_lifes.setCharacterSize(24);
    text_lifes.setPosition(250,610);

    rectangle1l.setPosition(315, 615);
    rectangle1l.setSize(rectanglesize);
    rectangle1l.setTexture(&snake_);

    rectangle2l.setPosition(365, 615);
    rectangle2l.setSize(rectanglesize);
    rectangle2l.setTexture(&snake2_);

    sf::Clock clock;
    srand(time(NULL));

    sf::RectangleShape background, shape_snake, shape_apple, shape_rock;


    while (window.isOpen()) {
        set_size();

        points1 = snakes[0]->lenght;
        std::stringstream points1_stringstream;
        points1_stringstream << points1;
        std::string points1_string;
        points1_stringstream >> points1_string;

        text_points1.setFont(font);
        text_points1.setString(points1_string);
        text_points1.setCharacterSize(24);
        text_points1.setPosition(105,610);

        lifes1 = snakes[0]->lifes;
        std::stringstream lifes1_stringstream;
        lifes1_stringstream << lifes1;
        std::string lifes1_string;
        lifes1_stringstream >> lifes1_string;

        text_lifes1.setFont(font);
        text_lifes1.setString(lifes1_string);
        text_lifes1.setCharacterSize(24);
        text_lifes1.setPosition(340,610);

        points2 = snakes[1]->lenght;
        std::stringstream points2_stringstream;
        points2_stringstream << points2;
        std::string points2_string;
        points2_stringstream >> points2_string;

        text_points2.setFont(font);
        text_points2.setString(points2_string);
        text_points2.setCharacterSize(24);
        text_points2.setPosition(155,610);

        lifes2 = snakes[1]->lifes;
        std::stringstream lifes2_stringstream;
        lifes2_stringstream << lifes2;
        std::string lifes2_string;
        lifes2_stringstream >> lifes2_string;

        text_lifes2.setFont(font);
        text_lifes2.setString(lifes2_string);
        text_lifes2.setCharacterSize(24);
        text_lifes2.setPosition(390,610);

        sf::Vector2f SIZE(size, size);

        background.setSize(SIZE);
        background.setFillColor(sf::Color::Black);
        background.setOutlineThickness(1);
        background.setOutlineColor(sf::Color::White);

        shape_snake.setSize(SIZE);
        shape_snake.setOutlineThickness(1);
        shape_snake.setOutlineColor(sf::Color::White);

        shape_apple.setSize(SIZE);
        shape_apple.setFillColor(sf::Color::Red);
        shape_apple.setOutlineThickness(1);
        shape_apple.setOutlineColor(sf::Color::White);

        shape_rock.setTexture(&rock_);
        shape_rock.setSize(SIZE);
        shape_rock.setOutlineThickness(1);
        shape_rock.setOutlineColor(sf::Color::White);

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        time_to_delay += time;

        for(auto snake : snakes){
            snake -> set_direction(snake -> control);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        show_rock_time += show_rock_time_variable;



        window.clear(sf::Color::Black);

        for(auto snake : snakes){
            if(snake->lifes < 0){
                every_snake_is_alive = false;
            }
        }

        if(!every_snake_is_alive){
            level = 1;
            window.draw(text_gameover);
            window.draw(text_exit);
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width){
                        if(mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                            window.close();
                        }
                    }
                }
            }
        }else if(level_change && level == 4){
            window.draw(text_win);
            window.draw(text_exit);
            window.draw(text_thanks);
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width){
                        if(mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                            window.close();
                        }
                    }
                }
            }
        }else if(level_change){
            window.draw(text_level_complete);
            window.draw(text_contiune);
            window.draw(text_exit);
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if(mouse_position.x > text_contiune.getGlobalBounds().left && mouse_position.x < text_contiune.getGlobalBounds().left + text_contiune.getGlobalBounds().width){
                        if(mouse_position.y > text_contiune.getGlobalBounds().top && mouse_position.y < text_contiune.getGlobalBounds().top + text_contiune.getGlobalBounds().height){
                            level_change = false;
                        }
                    }
                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width){
                        if(mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                            window.close();
                        }
                    }
                }
            }
        }else{
            if(time_to_delay > time_delay){

                set_size();
                time_to_delay = 0;
                set_rock_position();

                for(auto snake : snakes){
                    snake -> snake_move();
                    snake -> snake_direction();
                    snake -> crash_with_rock();
                    snake -> feed_me();
                    snake -> suicide();
                    snake -> through_walls();
                }
                level_check();
            }

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

            for(auto snake : snakes){
                  shape_snake.setTexture(&snake->snake_texture);
                for(int i = 0; i < snake -> lenght; i++){ // drawing snake
                    shape_snake.setPosition(snake -> ssnake[i].x * size, snake -> ssnake[i].y * size);
                    window.draw(shape_snake);
                }
            }

            window.draw(text_points);
            window.draw(text_lifes);

            if(snakes.size() == 1){
                window.draw(rectangle1p);
                window.draw(text_points1);
                window.draw(rectangle1l);
                window.draw(text_lifes1);
            }
            if(snakes.size() == 2){
                window.draw(rectangle1p);
                window.draw(text_points1);
                window.draw(rectangle1l);
                window.draw(text_lifes1);
                window.draw(rectangle2p);
                window.draw(text_points2);
                window.draw(rectangle2l);
                window.draw(text_lifes2);
            }
        }
        window.display();
    }
}
