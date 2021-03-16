#include <SFML/Graphics.hpp>
#include "Grid.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
const int GRID_SIZE = 32;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Battleships");

    sf::Text text;
    text.setCharacterSize(20);
    sf::Font sm;
    sm.loadFromFile("SM.TTF");
    text.setFont(sm);
    text.setString("Battleships");
    Grid gridA = Grid(sf::Vector2i(50, 100));
    Grid gridB = Grid(sf::Vector2i(500, 100));
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);

        //grids
        gridA.TileSelect(sf::Mouse::getPosition(window));
        gridB.TileSelect(sf::Mouse::getPosition(window));

        gridA.Draw(window);
        gridB.Draw(window);


        window.display();
    }

    return 0;
}