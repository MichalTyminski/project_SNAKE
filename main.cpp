#include <C:/SFML-2.5.1/include/SFML/Window.hpp>
#include <C:/SFML-2.5.1/include/SFML/Graphics.hpp>
#include <ostream>
#include <iostream>
#include "SNAKE_class.h"
#include "Board_class.h"

using namespace std;

int main()
{
    Snake snake;
    Board board;
    snake.board = &board;
    board.snake = &snake;
    board.game();
    return 0;
}
