#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Grid.h"
#include <iostream>
#include "GameEngine.h"
#include "Button.h"
#include "Runnable.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

NetworkParameters globalParameters;




int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battleships");

    Menu menu(Menu::Stored_menu::main, window.getSize());
    menu.run(window);

    return 0;
}