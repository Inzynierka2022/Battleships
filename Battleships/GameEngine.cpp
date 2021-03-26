#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine()
{
	gameState = 0;
}

void GameEngine::run(sf::RenderWindow& window)
{
	bool dragShip = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left) 
				{
					if (ships.drag(sf::Mouse::getPosition(window), sf::Mouse::getPosition(window)))
					{
						dragShip = true;
						if (ships.checkIfPlaced())
						{
							gridA.clearSpace(ships.getDraggedShip());
						}
					}
				}

				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					if (dragShip) ships.getDraggedShip().rotate();
				}
			}
		}
		window.clear();

		gridA.tileSelect(sf::Mouse::getPosition(window));
		gridB.tileSelect(sf::Mouse::getPosition(window));

		if (dragShip)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				ships.drag(sf::Mouse::getPosition(window), gridA.getHoveredTilePosition(), gridA.canPlaceShip(ships.getDraggedShip()));
			else
			{
				ships.stopDrag(gridA.canPlaceShip(ships.getDraggedShip()));
				gridA.placeShip(ships.getDraggedShip());
				dragShip = false;
			}
		}

		gridA.draw(window);
		gridB.draw(window);

		ships.draw(window);

		window.display();
	}
}
