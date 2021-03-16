#include "Grid.h"

void Grid::draw_on_position(uint8_t, sf::Vector2f)
{
}

Grid::Grid(sf::Vector2i position)
{
	this->position = position;
	tiles.resize(gridRows, std::vector<sf::RectangleShape>());
	for (int x = 0; x < gridRows; x++)
	{
		tiles[x].resize(gridColumns, sf::RectangleShape());
		for (int y = 0; y < gridColumns; y++) {
			tiles[x][y].setSize(sf::Vector2f(gridSize, gridSize));
			tiles[x][y].setFillColor(sf::Color::Cyan);
			tiles[x][y].setOutlineThickness(-2.f);
			tiles[x][y].setOutlineColor(sf::Color(255,0,0,127));
			tiles[x][y].setPosition(x * gridSize + position.x, y * gridSize + position.y);
		}
	}
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (int x = 0; x < gridRows; x++) {
		for (int y = 0; y < gridColumns; y++) {
			window.draw(tiles[x][y]);
		}
	}
}

void Grid::TileSelect(sf::Vector2i mousePos)
{
	//reset previously selected tile
	tiles[selectedTile.x][selectedTile.y].setFillColor(sf::Color::Cyan);
	//check if mouse is inside of the grid
	if (mousePos.x > position.x && mousePos.x < position.x + (gridColumns * gridSize) && mousePos.y > position.y && mousePos.y < position.y + (gridRows * gridSize)) {
		int tileX = (mousePos.x - position.x) / gridSize;
		int tileY = (mousePos.y - position.y) / gridSize;
		selectedTile = sf::Vector2i(tileX, tileY);
		tiles[tileX][tileY].setFillColor(sf::Color::Yellow);
	}
}
