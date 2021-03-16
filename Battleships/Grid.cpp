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
	font.loadFromFile("SM.TTF");
	sf::Text t1;
	t1.setFont(font);
	std::string s1[] = { "A","B","C","D","E","F","G","H"," I","J" };
	std::string s2[] = { "1","2","3","4","5","6","7","8","9","10" };
	for (int i = 0; i < 10; i++)
	{
		t1.setString(s1[i]);
		t1.setPosition(tiles[i][0].getPosition() - sf::Vector2f(-5,gridSize));
		yColumn.push_back(t1);
		t1.setString(s2[i]);
		t1.setPosition(tiles[0][i].getPosition() - sf::Vector2f(gridSize+5, 0));
		xColumn.push_back(t1);
	}
}

void Grid::Draw(sf::RenderWindow& window)
{
	for (int x = 0; x < gridRows; x++) {
		for (int y = 0; y < gridColumns; y++) {
			window.draw(tiles[x][y]);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		window.draw(yColumn[i]);
		window.draw(xColumn[i]);
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
