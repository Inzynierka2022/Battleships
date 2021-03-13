#include <SFML/Graphics.hpp>
#include "Menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Battleships");

    sf::Text text;
    text.setCharacterSize(20);
    sf::Font sm;
    sm.loadFromFile("SM.TTF");
    text.setFont(sm);
    text.setString("Battleships");

    Menu menu;
    bool mouse_on_button = 0;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        menu.draw(window);
        window.draw(text);
        window.display();
        mouse_on_button = menu.changeColor(window);
    }

    return 0;
}