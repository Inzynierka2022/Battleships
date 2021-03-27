#include "Ships.h"
#include <iostream>

Ships::Ships()
{
	for (int i = 0; i < 10; i++)
	{
		shipsPlaced[i] = false;
	}
	ships[0] = Ship(4, sf::Vector2f(50, 550));
	ships[1] = Ship(3, sf::Vector2f(50, 600));
	ships[2] = Ship(3, sf::Vector2f(180, 600));
	ships[3] = Ship(2, sf::Vector2f(50, 650));
	ships[4] = Ship(2, sf::Vector2f(140, 650));
	ships[5] = Ship(2, sf::Vector2f(230, 650));
	ships[6] = Ship(1, sf::Vector2f(50, 700));
	ships[7] = Ship(1, sf::Vector2f(100, 700));
	ships[8] = Ship(1, sf::Vector2f(150, 700));
	ships[9] = Ship(1, sf::Vector2f(200, 700));

	
}

void Ships::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 10; i++)
	{
		//ships[i].setShipTexture(ships[i].getType());
		ships[i].draw(window);
	}
}

bool Ships::drag(sf::Vector2i mousePosition, sf::Vector2i tilePosition, bool legalTile)
{
	if (!dragging)
	{
		for (int i = 0; i < 10; i++)
		{
			if (ships[i].checkMousePosition(mousePosition))
			{
				draggedShip = i;
				draggedShipStartingPosition = ships[i].getPosition();
				draggedShipOffset = mousePosition - (sf::Vector2i)ships[i].getPosition();
				draggedShipOrientation = ships[i].isHorizontal();
				dragging = true;
				return true;
			}
		}
		return false;
	}
	else
	{
		if (legalTile)
			ships[draggedShip].setPosition(tilePosition);
		else
			ships[draggedShip].setPosition(mousePosition - draggedShipOffset);
	}
	return true;
}

Ship& Ships::getDraggedShip()
{
	return ships[draggedShip];
}


void Ships::stopDrag(bool canBePlaced)
{
	dragging = false;
	if (!canBePlaced)
	{
		ships[draggedShip].setPosition((sf::Vector2i)draggedShipStartingPosition);
		ships[draggedShip].setOrientation(draggedShipOrientation);
		return;
	}
	shipsPlaced[draggedShip] = true;
}

bool Ships::checkIfPlaced()
{
	return shipsPlaced[draggedShip];
}

bool Ships::checkIfAllPlaced() const
{
	for (auto x : shipsPlaced)
	{
		if (!x)
		{
			return false;
		}
	}
	return true;
}

void Ships::resetShips()
{
	ships[0].setPosition(sf::Vector2i(50, 550));
	ships[1].setPosition(sf::Vector2i(50, 600));
	ships[2].setPosition(sf::Vector2i(180, 600));
	ships[3].setPosition(sf::Vector2i(50, 650));
	ships[4].setPosition(sf::Vector2i(140, 650));
	ships[5].setPosition(sf::Vector2i(230, 650));
	ships[6].setPosition(sf::Vector2i(50, 700));
	ships[7].setPosition(sf::Vector2i(100, 700));
	ships[8].setPosition(sf::Vector2i(150, 700));
	ships[9].setPosition(sf::Vector2i(200, 700));
	for (int i = 0; i < 10; i++)
	{
		shipsPlaced[i] = false;
	}
}