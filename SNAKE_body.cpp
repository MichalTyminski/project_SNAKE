#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ostream>
#include <iostream>
#include <sstream>
#include "SNAKE_class.h"
#include "Board_class.h"
#include <vector>
#include <map>
#include <fstream>

Snake::Snake(sf::Texture texture_, int control_)
{
    snake_texture = texture_;
    control = control_;
    lenght = 1;
    direction = 1;
    lifes = 3;
    direction_changed = false;

    apple_buffer.loadFromFile("./apple_music.wav");
    apple_sound.setBuffer(apple_buffer);

    rock_buffer.loadFromFile("./rock_music.wav");
    rock_sound.setBuffer(rock_buffer);

    bonus_buffer.loadFromFile("./bonus_music.wav");
    bonus_sound.setBuffer(bonus_buffer);
}

Snake::~Snake()
{
}

Board::Board(){
    size = 30;
    fallen = 0;
    window_size_x = 600;
    window_size_y = 600;
    time_to_delay = 0;
    time_delay = 0.1;
    time_between_colision = 1;
    time_to_colison = 0;
    show_rock_time = 0;
    show_rock_time_variable = 0.0001;
    show_bonus_time = 0;
    show_bonus_time_variable = 0;
    variable_of_speed = 0;
    constant_of_speed = 10;
    level = 1;
    size_to_next_level = 10;
    level_change = false;
    every_snake_is_alive = true;
    is_paused = false;

    apple.x = rand() % window_size_x/size;
    apple.y = rand() % window_size_y/size;

    rock.x = rand() % window_size_x/size;
    rock.y = rand() % window_size_y/size;

    bonus.x = rand() % window_size_x/size;
    bonus.y = rand() % window_size_y/size;

    level_complete_buffer.loadFromFile("./level_complete_music.wav");
    level_complete_sound.setBuffer(level_complete_buffer);
}

Board::~Board()
{
}

void Snake::set_direction(int control){
    if(control == 1){ //sterowanie za pomoca strzalek
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = 4;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = 3;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = 2;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = 1;
            direction_changed = true;
        }else {}
    }else if(control == 2){ //sterowanie za pomoca wasd
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction = 4;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction = 3;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction = 2;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = 1;
            direction_changed = true;
        }else {}
    }else if(control == 3){ //sterowanie za pomoca strzalek (odwrocone)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            direction = 3;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            direction = 4;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            direction = 1;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            direction = 2;
            direction_changed = true;
        }else {}
    }else if(control == 4){ //sterowanie za pomoca wasd (odwrocone)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction = 3;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction = 4;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction = 1;
            direction_changed = true;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction = 2;
            direction_changed = true;
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
            rock_sound.play();
            lenght --;
            lifes --;
            board -> position_of_rock_x[i] = rand() % board -> window_size_x/board -> size;
            board -> position_of_rock_y[i] = rand() % board -> window_size_y/board -> size;
        }
    }
}

void Snake::feed_me(){
    if(ssnake[0].x == board -> apple.x && ssnake[0].y == board -> apple.y){
        apple_sound.play();
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

void Snake::get_bonus(){
    int surprise = 0;
    if(ssnake[0].x == board -> bonus.x && ssnake[0].y == board -> bonus.y && board -> show_bonus_time > 0.5){
        bonus_sound.play();
        surprise = rand() % 4;

        if(surprise == 0){ // dodanie 3 punktow zycia
            lifes = lifes + 3;
        }else if(surprise == 1){ // dodanie 5 punktow (dlugosci)
            lenght = lenght + 5;
        }else if(surprise == 2){ // zmiana sterowania
            if(control == 1){
                control = 3;
            }else if(control == 2){
                control = 4;
            }else if(control == 3){
                control = 1;
            }else if(control == 4){
                control = 2;
            }
        }else if(surprise == 3 && lenght > 1){ // odjecie po 1 pkt zycia i dlugosci
            lifes --;
            lenght --;
        }
        board -> bonus.x = rand() % board -> window_size_x/board -> size;
        board -> bonus.y = rand() % board -> window_size_y/board -> size;
        board -> show_bonus_time = 0;
    }
}

void Snake::snakes_collision(){
    for(unsigned long long i = 0; i < board -> snakes.size(); i++){
        for(unsigned long long j = 0; j < board -> snakes.size(); j++){
            if(board -> snakes[0]->ssnake[i].x == board -> snakes[1]->ssnake[j].x &&
                    board -> snakes[0]->ssnake[i].y == board -> snakes[1]->ssnake[j].y){
                for(auto snake : board -> snakes){
                    snake->lifes --;
                    snake->lenght = 1;
                    board -> time_to_colison = 0;
                }
            }
        }
    }
}


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
        if(snake -> lenght >= size_to_next_level){
            snake -> lenght = 1;
            level ++;
            level_change = true;
            level_complete_sound.play();
        }
    }
}

void Board::set_rock_position(){
    if(show_rock_time > time_delay){
        do{
            rock.x = rand() % (window_size_x/size);
            rock.y = rand() % (window_size_y/size);
        }while(rock.x != apple.x && rock.y != apple.y);

        position_of_rock_x.emplace_back(rock.x);
        position_of_rock_y.emplace_back(rock.y);
        show_rock_time = 0.0001;
    }
}

void Board::apple_rock_bonus(){
    for(unsigned long long i = 0; i < position_of_rock_x.size(); i++){
        if((apple.x == position_of_rock_x[i] && apple.y == position_of_rock_y[i])
                || (apple.x == bonus.x && apple.y == bonus.y)){
            apple.x = rand() % window_size_x/size;
            apple.y = rand() % window_size_y/size;
        }
    }
}

void Board::read_from_file(){
    std::string linia;
    std::fstream plik;
    int count = 0;
    std::vector<float> dane;

    plik.open("./parametry.txt", std::ios::in);
    while(!plik.eof()){
        count ++;
        getline(plik, linia);
        std::cout << linia << std::endl;
        if(count%2 == 0){
            float linia_float = std::stof(linia);
            dane.push_back(linia_float);
        }
    }
    plik.close();

    variable_of_speed = dane[0];
    show_bonus_time_variable = dane[1];
    for(auto snake : snakes){
        snake->lifes = dane[2];
    }
    size_to_next_level = dane[3];
}

void Board::game(){
    read_from_file();
    set_size();

    sf::RenderWindow window(sf::VideoMode(window_size_x, window_size_y+50), "SNAKE by Michal Tyminski");

    sf::Texture text_level_complete_, text_contiune_, text_exit_, text_win_, text_thanks_, text_gameover_, text_paused_;
    if (!text_level_complete_.loadFromFile("./level_complete.png"))
    {
        std::cout << "ERROR text_level_complete_" << std::endl;
    }
    sf::Sprite text_level_complete;
    text_level_complete.setTexture(text_level_complete_);
    text_level_complete.setPosition(window_size_x/2 - text_level_complete.getGlobalBounds().width/2, 100);

    if (!text_contiune_.loadFromFile("./contiune.png"))
    {
        std::cout << "ERROR text_contiune_" << std::endl;
    }
    sf::Sprite text_contiune;
    text_contiune.setTexture(text_contiune_);
    text_contiune.setPosition(window_size_x/2 - text_contiune.getGlobalBounds().width/2, 275);

    if (!text_exit_.loadFromFile("./exite.png"))
    {
        std::cout << "ERROR text_exit_" << std::endl;
    }
    sf::Sprite text_exit;
    text_exit.setTexture(text_exit_);
    text_exit.setPosition(window_size_x/2 - text_exit.getGlobalBounds().width/2, 350);

    if (!text_win_.loadFromFile("./win.png"))
    {
        std::cout << "ERROR text_win_" << std::endl;
    }
    sf::Sprite text_win;
    text_win.setTexture(text_win_);
    text_win.setPosition(window_size_x/2 - text_win.getGlobalBounds().width/2, 100);

    if (!text_thanks_.loadFromFile("./thanks.png"))
    {
        std::cout << "ERROR text_thanks_" << std::endl;
    }
    sf::Sprite text_thanks;
    text_thanks.setTexture(text_thanks_);
    text_thanks.setPosition(window_size_x/2 - text_thanks.getGlobalBounds().width/2, 480);

    if (!text_gameover_.loadFromFile("./gameover.png"))
    {
        std::cout << "ERROR text_gameover_" << std::endl;
    }
    sf::Sprite text_gameover;
    text_gameover.setTexture(text_gameover_);
    text_gameover.setPosition(window_size_x/2 - text_gameover.getGlobalBounds().width/2, 100);

    if (!text_paused_.loadFromFile("./paused.png"))
    {
        std::cout << "ERROR text_paused_" << std::endl;
    }
    sf::Sprite text_paused;
    text_paused.setTexture(text_paused_);
    text_paused.setPosition(window_size_x/2 - text_paused.getGlobalBounds().width/2, 100);

    sf::Texture rock_, apple_, bonus_;

    if (!rock_.loadFromFile("./rock.png")) {
        std::cerr << "Could not load texture rock.png" << std::endl;
    }

    if (!apple_.loadFromFile("./apple.jfif")) {
        std::cerr << "Could not load texture apple.jfif" << std::endl;
    }

    if (!bonus_.loadFromFile("./bonus.png")) {
        std::cerr << "Could not load texture bonus.png" << std::endl;
    }

    sf::Music game_music;
    if (!game_music.openFromFile("./game_music.ogg")) {
        std::cerr << "Could not load game_music.ogg" << std::endl;
    }
    game_music.setLoop(true);
    game_music.play();

//    sf::SoundBuffer game_over_buffer;
//    if (!game_over_buffer.loadFromFile("./lose_music.wav")) {
//        std::cerr << "Could not load lose_music.wav" << std::endl;
//    }
//    sf::Sound game_over_sound;
//    game_over_sound.setBuffer(game_over_buffer);

    //show data
    int points1, points2, lifes1, lifes2;

    sf::Font font;
    if(!font.loadFromFile("Padauk-Regular.ttf")){
        std::cout << "ERROR Padauk-Regular.ttf" << std::endl;
    }
    sf::Text text_points, text_points1, text_points2, text_lifes, text_lifes1, text_lifes2, gameover_youlost;
    sf::Vector2f rectanglesize(20,20);
    sf::RectangleShape rectangle1p, rectangle2p, rectangle1l, rectangle2l, gameover_snake1, gameover_snake2;

    text_points.setFont(font);
    text_points.setString("Points: ");
    text_points.setCharacterSize(24);
    text_points.setPosition(5,610);

    rectangle1p.setPosition(80, 615);
    rectangle1p.setSize(rectanglesize);
    rectangle1p.setTexture(&snakes[0]->snake_texture);

    rectangle2p.setPosition(130, 615);
    rectangle2p.setSize(rectanglesize);
    rectangle2p.setTexture(&snakes[1]->snake_texture);

    text_lifes.setFont(font);
    text_lifes.setString("Lifes: ");
    text_lifes.setCharacterSize(24);
    text_lifes.setPosition(250,610);

    rectangle1l.setPosition(315, 615);
    rectangle1l.setSize(rectanglesize);
    rectangle1l.setTexture(&snakes[0]->snake_texture);

    rectangle2l.setPosition(365, 615);
    rectangle2l.setSize(rectanglesize);
    rectangle2l.setTexture(&snakes[1]->snake_texture);

    gameover_youlost.setFont(font);
    gameover_youlost.setString("You lost becouse snake     died");
    gameover_youlost.setCharacterSize(24);
    gameover_youlost.setPosition(window_size_x/2 - gameover_youlost.getGlobalBounds().width/2, 280);

    gameover_snake1.setPosition(385, 285);
    gameover_snake1.setSize(rectanglesize);
    gameover_snake1.setTexture(&snakes[0]->snake_texture);

    gameover_snake2.setPosition(385, 285);
    gameover_snake2.setSize(rectanglesize);
    gameover_snake2.setTexture(&snakes[1]->snake_texture);

    sf::Clock clock;
    srand(time(NULL));

    sf::RectangleShape background, shape_snake, shape_apple, shape_rock, shape_bonus;

    background.setFillColor(sf::Color::Black);
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::White);

    shape_snake.setOutlineThickness(1);
    shape_snake.setOutlineColor(sf::Color::White);

    shape_apple.setTexture(&apple_);
    shape_rock.setTexture(&rock_);
    shape_bonus.setTexture(&bonus_);

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        set_size();
        variable_of_speed ++;

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
        sf::Vector2f SIZE_e(size-1, size-1);

        background.setSize(SIZE);
        shape_snake.setSize(SIZE_e);
        shape_apple.setSize(SIZE_e);
        shape_rock.setSize(SIZE_e);
        shape_bonus.setSize(SIZE_e);

        float time = clock.getElapsedTime().asSeconds();

        clock.restart();
        time_to_delay += time;
        time_to_colison += time;

        for(auto snake : snakes){
            snake -> set_direction(snake -> control);
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        show_rock_time += show_rock_time_variable;
        show_bonus_time += show_bonus_time_variable;

        window.clear(sf::Color::Black);

        for(unsigned long long i = 0; i < snakes.size(); i++){
            if(snakes[i]->lifes < 0){
                every_snake_is_alive = false;
                fallen = i;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                is_paused = true;
            }


        if(!every_snake_is_alive){
            level = 1;
            game_music.pause();
            //game_over_sound.play();
            window.draw(text_gameover);
            window.draw(text_exit);
            if(snakes.size() != 1){
                window.draw(gameover_youlost);
                if(fallen == 0){
                    window.draw(gameover_snake1);
                }else if(fallen == 1){
                    window.draw(gameover_snake2);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width
                            && mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                            window.close();
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
                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width
                            && mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                            window.close();
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
                    if(mouse_position.x > text_contiune.getGlobalBounds().left && mouse_position.x < text_contiune.getGlobalBounds().left + text_contiune.getGlobalBounds().width
                            && mouse_position.y > text_contiune.getGlobalBounds().top && mouse_position.y < text_contiune.getGlobalBounds().top + text_contiune.getGlobalBounds().height){
                            level_change = false;
                        }

                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width
                            && mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                            window.close();
                        }
                    }
                }

        }else if(is_paused == true){
            window.draw(text_paused);
            window.draw(text_exit);
            window.draw(text_contiune);
            if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if(mouse_position.x > text_exit.getGlobalBounds().left && mouse_position.x < text_exit.getGlobalBounds().left + text_exit.getGlobalBounds().width
                            && mouse_position.y > text_exit.getGlobalBounds().top && mouse_position.y < text_exit.getGlobalBounds().top + text_exit.getGlobalBounds().height){
                        window.close();
                    }
                    if(mouse_position.x > text_contiune.getGlobalBounds().left && mouse_position.x < text_contiune.getGlobalBounds().left + text_contiune.getGlobalBounds().width
                            && mouse_position.y > text_contiune.getGlobalBounds().top && mouse_position.y < text_contiune.getGlobalBounds().top + text_contiune.getGlobalBounds().height){
                        is_paused = false;
                    }
                }
            }

    }else{
            if(time_to_delay > time_delay){

                set_size();
                set_rock_position();

                if(variable_of_speed > constant_of_speed){
                    for(auto snake : snakes){
                        snake -> snake_move();
                        snake -> snake_direction();
                        snake -> suicide();
                        snake -> through_walls();
                        snake -> crash_with_rock();
                        snake -> feed_me();
                        snake -> get_bonus();
                        apple_rock_bonus();
                        if(snake -> direction_changed && time_between_colision < time_to_colison){
                            snake -> snakes_collision();
                        }
                    }
                    variable_of_speed = 0;
                }
                level_check();
                time_to_delay = 0;
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

            if(show_bonus_time > 0.5){
                shape_bonus.setPosition(bonus.x * size, bonus.y * size); // drawing bonus
                window.draw(shape_bonus);
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
