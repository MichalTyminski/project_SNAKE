#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include "SNAKE_class.h"
#include "Board_class.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SNAKE by Michal Tyminski");

    std::vector<Snake*> snakes;
    Snake snake(sf::Color::Green);
    snakes.push_back(&snake);
    Snake snake2(sf::Color::Blue);
    //snakes.push_back(&snake2);
    Board board;
    snake.board = &board;
    snake2.board = &board;
    board.snakes = snakes;
    board.game();
    return 0;
}
