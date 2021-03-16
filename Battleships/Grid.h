#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class Grid
{
private:
	float gridSize = 40;
	int gridColumns = 10;
	int gridRows = 10;
	sf::Vector2i position;
	std::vector<std::vector<sf::RectangleShape>> tiles;
	sf::Vector2i selectedTile;
	void draw_on_position(uint8_t, sf::Vector2f);
	sf::Font font;
	std::vector<sf::Text>xColumn;
	std::vector<sf::Text>yColumn;
public:
	Grid(sf::Vector2i);
	void Draw(sf::RenderWindow& window);
	void TileSelect(sf::Vector2i mousePos);
};

