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
	
	sf::Texture texture;
	sf::Sprite bombed;
	//wektor pozosta³ych pól
public:
	Grid(sf::Vector2i);
	void draw(sf::RenderWindow& window);
	void tileSelect(sf::Vector2i mousePos);
	bool canPlaceShip(Ship& s);
	bool canPlaceShipOnPosition(Ship& s, int x, int y);
	void placeShip(Ship& s);
	void placeShipOnPosition(Ship& s, int x, int y);
	void clearSpace(Ship& s);
	sf::Vector2i getTilePosition(int x, int y);
	sf::Vector2i getHoveredTilePosition();
	void clearGrid();
	bool bomb_tile();
	int getTile();
	bool checkTile(const int&);
	void changeField(const int&,const bool&);
	bool checkShip(const int&);
	void drawMarkers(sf::RenderWindow& window);
	bool checkIfShipDestroyed(const int&, const int&);
	void destroyShip(const int&, const int&);
	void getDestroyedShipInfo(int tile, int& type, sf::Vector2i& position, bool& orientation);
	int findShipType(const int& tile, const int& tileThatCalledIt);
	sf::Vector2i findShipPosition(const int& tile, const int& tileThatCalledIt);
	bool findShipOrientation(const int& tile);
};

