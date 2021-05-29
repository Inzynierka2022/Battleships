#pragma once
#include "Ship.h"
#include <vector>
#include <array>
#include "Grid.h"
class Ships
{
private:
	std::vector<Ship> ships = std::vector<Ship>(10);

	//dragging
	int draggedShip = -1;
	bool dragging = false;
	sf::Vector2i draggedShipOffset;
	bool draggedShipOrientation = true;
	sf::Vector2f draggedShipStartingPosition;
public:
	Ships();
	void draw(sf::RenderWindow& window);
	Ship& getDraggedShip();
	bool checkIfPlaced();
	bool drag(sf::Vector2i mousePosition, sf::Vector2i tilePosition, bool legalTile = false);
	void stopDrag(bool canBePlaced);
	bool checkIfAllPlaced() const;
	void randomize(Grid& g);
	void resetShips();
};