#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine()
{
	gameState = 0;
	Button* readyButton = new Button(sf::Vector2f(700,700),"not ready");
	buttons.push_back(readyButton);
}

void GameEngine::run(sf::RenderWindow& window)
{
	bool dragShip = false;
	bool buttonPressed = false;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!buttonPressed && gameState<2)
			{
				buttonPressed = true;
				ships.resetShips();
				gridA.clearGrid();
				buttons[0]->setString("not ready");
				std::cout << "reset\n";
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!buttonPressed && gameState<2 && ships.checkIfAllPlaced())
			{
				buttonPressed = true;
				gameState = (gameState + 1) % 2;
				std::cout << gameState << '\n';
				if (gameState) buttons[0]->setString("ready");
				else buttons[0]->setString("not ready");
			}
		}
		else
		{
			buttonPressed = false;
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
		buttons[0]->draw(window);

		window.display();
	}
}
