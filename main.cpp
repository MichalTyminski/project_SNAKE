#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include "SNAKE_class.h"
#include "Board_class.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SNAKE by Michal Tyminski");

    sf::Event event;
    sf::Texture text_0, text_1, text_2, text_3;

    if (!text_0.loadFromFile("./welcome.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_welcome;
    text_welcome.setTexture(text_0);
    text_welcome.setPosition(window.getSize().x/2 - text_welcome.getGlobalBounds().width/2, 20);

    if (!text_1.loadFromFile("./number_of_players.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_number;
    text_number.setTexture(text_1);
    text_number.setPosition(window.getSize().x/2 - text_welcome.getGlobalBounds().width/2, 150);

    if (!text_2.loadFromFile("./one_player.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_1player;
    text_1player.setTexture(text_2);
    text_1player.setPosition(50, 300);

    if (!text_3.loadFromFile("./two_players.png"))
    {
        std::cout << "ERROR" << std::endl;
    }
    sf::Sprite text_2players;
    text_2players.setTexture(text_3);
    text_2players.setPosition(350, 300);

    sf::Texture snake_, snake2_;

    if (!snake_.loadFromFile("./SnakeSkin.jpeg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    if (!snake2_.loadFromFile("./snakeskin.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    while (window.isOpen()) {

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        if (event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if(mouse_position.x > text_1player.getGlobalBounds().left && mouse_position.x < text_1player.getGlobalBounds().left + text_1player.getGlobalBounds().width){
                    if(mouse_position.y > text_1player.getGlobalBounds().top && mouse_position.y < text_1player.getGlobalBounds().top + text_1player.getGlobalBounds().height){
                        std::vector<Snake*> snakes;
                        Snake snake(snake_, 1);
                        snakes.push_back(&snake);
                        Board board;
                        snake.board = &board;
                        board.snakes = snakes;
                        window.close();
                        board.game();
                    }
                }
                if(mouse_position.x > text_2players.getGlobalBounds().left && mouse_position.x < text_2players.getGlobalBounds().left + text_2players.getGlobalBounds().width){
                    if(mouse_position.y > text_2players.getGlobalBounds().top && mouse_position.y < text_2players.getGlobalBounds().top + text_2players.getGlobalBounds().height){
                        std::vector<Snake*> snakes;
                        Snake snake(snake_, 1);
                        snakes.push_back(&snake);
                        Snake snake2(snake2_, 2);
                        snakes.push_back(&snake2);
                        Board board;
                        snake.board = &board;
                        snake2.board = &board;
                        board.snakes = snakes;
                        window.close();
                        board.game();
                    }
                }
            }
        }
        window.draw(text_welcome);
        window.draw(text_number);
        window.draw(text_1player);
        window.draw(text_2players);
        window.display();
    }
    return 0;
}

// https://www.sharetextures.com/textures/animals/snake_skin/ <- miejsce skąd pobrałem tekstury
// https://mixkit.co/free-sound-effects/game/ <- miejsce skąd pobrałem dźwięki
