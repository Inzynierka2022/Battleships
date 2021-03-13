#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Battleships");

    sf::Text text;
    text.setCharacterSize(20);
    sf::Font sm;
    sm.loadFromFile("SM.TTF");
    text.setFont(sm);
    text.setString("Battleships");

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
        window.display();
    }

    return 0;
}