#include <SFML/Graphics.hpp>
#include "Menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Battleships");

    Menu menu;

    menu.run(window);

    return 0;
}