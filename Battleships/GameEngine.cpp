#include "GameEngine.h"

GameEngine::GameEngine()
{
	gameState = 0;
}

void GameEngine::run(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        
        gridA.TileSelect(sf::Mouse::getPosition(window));
        gridB.TileSelect(sf::Mouse::getPosition(window));

        gridA.Draw(window);
        gridB.Draw(window);

        window.display();
	}
}
