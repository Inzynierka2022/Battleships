#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>
#include "GameEngine.h"
#include "Button.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int GRID_SIZE = 32;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battleships");

    GameEngine gameEngine;
    gameEngine.run(window/*,communicator*/);
    return 0;
}