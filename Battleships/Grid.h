#pragma once
#include <vector>
#include "Ship.h"
#include <SFML/Graphics.hpp>
class Grid
{
private:
	enum class fieldType {
		Empty, Ship, Hit, Miss
	};

	float gridSize = 40;
	int gridColumns = 10;
	int gridRows = 10;
	sf::Vector2i position;
	std::vector<std::vector<sf::RectangleShape>> tiles;
	std::vector<std::vector<fieldType>> fields;
	sf::Vector2i selectedTile;
	bool isAnySelected = false;
	void draw_on_position(uint8_t, sf::Vector2f);
	bool isFree(sf::Vector2i coordinates);
	sf::Font font;
	std::vector<sf::Text>xColumn;
	std::vector<sf::Text>yColumn;
	Ship lastCleared;
public:
	Grid(sf::Vector2i);
	void draw(sf::RenderWindow& window);
	void tileSelect(sf::Vector2i mousePos);
	bool canPlaceShip(Ship& s);
	void placeShip(Ship& s);
	void clearSpace(Ship& s);
	sf::Vector2i getHoveredTilePosition();
};

