#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Grid.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battleships");
    Menu menu;
    menu.run(window);
    return 0;
}