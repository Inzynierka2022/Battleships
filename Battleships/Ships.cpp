#include "Ships.h"
#include <iostream>

Ships::Ships(bool visible)
{
	if (visible)
	{
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
	else
	{
		ships[0] = Ship(4, sf::Vector2f(-1000, -1000), visible);
		ships[1] = Ship(3, sf::Vector2f(-1000, -1000), visible);
		ships[2] = Ship(3, sf::Vector2f(-1000, -1000), visible);
		ships[3] = Ship(2, sf::Vector2f(-1000, -1000), visible);
		ships[4] = Ship(2, sf::Vector2f(-1000, -1000), visible);
		ships[5] = Ship(2, sf::Vector2f(-1000, -1000), visible);
		ships[6] = Ship(1, sf::Vector2f(-1000, -1000), visible);
		ships[7] = Ship(1, sf::Vector2f(-1000, -1000), visible);
		ships[8] = Ship(1, sf::Vector2f(-1000, -1000), visible);
		ships[9] = Ship(1, sf::Vector2f(-1000, -1000), visible);
	}
}

void Ships::draw(sf::RenderWindow& window)
{
	for (auto ship : ships)
	{
		//ship.setShipTexture(ship.getType());
		ship.draw(window);
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
	ships[draggedShip].setPlaced(true);
}

bool Ships::checkIfPlaced()
{
	return ships[draggedShip].isPlaced();
}

bool Ships::checkIfAllPlaced() const
{
	for (auto x : ships)
	{
		if (!x.isPlaced())
		{
			return false;
		}
	}
	return true;
}

void Ships::randomize(Grid& g)
{
	g.clearGrid();
	this->resetShips();
	int x, y;
	bool placed, orientation;
	for (int i = 0; i < 10; i++)
	{
		placed = false;
		while (!placed)
		{
			x = rand() % 10;
			y = rand() % 10;
			orientation = rand() % 2;
			ships[i].setOrientation(orientation);
			if (g.canPlaceShipOnPosition(ships[i], x, y))
			{
				g.placeShipOnPosition(ships[i], x, y);
				ships[i].setPosition(g.getTilePosition(x,y));
				ships[i].setPlaced(true);
				placed = true;
			}
		}
	}
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
		ships[i].setPlaced(false);
		if (!ships[i].isHorizontal())
		{
			ships[i].setOrientation(true);
			//ships[i].rotate();
		}
	}
}

void Ships::showShip(int type, sf::Vector2i position, bool orientation)
{
	bool x = false;
	for (int i=0; i<10; i++)
	{
		if (!ships[i].isVisible() && ships[i].getType() == type)
		{
			ships[i].setOrientation(orientation);
			ships[i].setPosition(position);
			ships[i].setVisibility(true);
			break;
		}
		//std::cout << (int)ships[i].getType() << " "<<ships[i].getPosition().x << " " << ships[i].getPosition().y << std::endl;
	}
}
