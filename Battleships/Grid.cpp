#include "Grid.h"
#include <iostream>

void Grid::draw_on_position(uint8_t, sf::Vector2f)
{
}

bool Grid::isFree(sf::Vector2i coordinates)
{
	if (coordinates.x < 0 || coordinates.x > 9 || coordinates.y < 0 || coordinates.y > 9)
		return false;
	uint8_t tempX, tempY;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			tempX = coordinates.x + x - 1;
			tempY = coordinates.y + y - 1;
			if (tempX >= 0 && tempX < 10 && tempY >= 0 && tempY < 10)
			{
				if (fields[tempX][tempY] != fieldType::Empty)
					return false;
			}
		}
	}
	return true;
}

void Grid::clearGrid()
{
	for (int i = 0; i < gridRows; i++)
	{
		for (int j = 0; j < gridColumns; j++)
		{
			fields[i][j] = fieldType::Empty;
		}
	}
}

bool Grid::bomb_tile() // do wywalenia
{
	if (this->isAnySelected)
	{
		int tile_number = (selectedTile.y * 10) + selectedTile.x;
	}
	return false;
}

int Grid::getTile()
{
	int tile_number = -1;
	//std::cout << "anyselected" << isAnySelected << '\n';
	if (fields[selectedTile.x][selectedTile.y] == fieldType::Hit || fields[selectedTile.x][selectedTile.y] == fieldType::Miss)
	{
		return tile_number;
	}
	/*for (int i = 0; i < gridColumns; i++)
	{
		for (int j = 0; j < gridRows; j++)
		{
			if (fields[selectedTile.x][selectedTile.y] == fieldType::Hit || fields[i][j] == fieldType::Miss)
			{
				return tile_number;
			}
		}
	}*/
	if (this->isAnySelected)
	{
		tile_number = (selectedTile.y * 10) + selectedTile.x;
		std::cout << tile_number << '\n';
	}
	return tile_number;
}

bool Grid::checkTile(const int &tile)
{
	bool result = false;
	if (fields[tile % 10][tile / 10] == fieldType::Ship)
	{
		result = true;
		fields[tile % 10][tile / 10] = fieldType::Hit;
	}
	else
	{
		result = false;
		fields[tile % 10][tile / 10] = fieldType::Empty;
	}
	return result;
}

void Grid::changeField(const int&i, const bool&b)
{
	if (b) fields[i % 10][i / 10] = fieldType::Hit;
	else fields[i % 10][i / 10] = fieldType::Miss;
}

void Grid::drawMarkers(sf::RenderWindow& window)
{
	for (int x = 0; x < gridRows; x++) 
	{
		for (int y = 0; y < gridColumns; y++) 
		{
			if (fields[x][y] == fieldType::Miss)
			{
				bombed.setTextureRect(sf::IntRect(240, 0, 40, 40));
				bombed.setPosition(tiles[x][y].getPosition());
				window.draw(bombed);
			}
			else if (fields[x][y] == fieldType::Hit)
			{
				bombed.setTextureRect(sf::IntRect(200, 0, 40, 40));
				bombed.setPosition(tiles[x][y].getPosition());
				window.draw(bombed);
			}
		}
	}
}

Grid::Grid(sf::Vector2i position)
{
	texture.loadFromFile("ships.png");
	bombed.setTexture(texture);
	this->position = position;
	tiles.resize(gridRows, std::vector<sf::RectangleShape>());
	fields.resize(gridRows, std::vector<fieldType>());
	for (int x = 0; x < gridRows; x++)
	{
		tiles[x].resize(gridColumns, sf::RectangleShape());
		fields[x].resize(gridColumns, fieldType::Empty);
		for (int y = 0; y < gridColumns; y++) {
			tiles[x][y].setSize(sf::Vector2f(gridSize, gridSize));
			tiles[x][y].setFillColor(sf::Color(0x39, 0x47, 0xb8, 0xff));
			tiles[x][y].setOutlineThickness(-2.f);
			//tiles[x][y].setOutlineColor(sf::Color(255, 0, 0, 127));
			tiles[x][y].setOutlineColor(sf::Color(0x2e, 0x3c, 0xac, 0xff));
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
		t1.setPosition(tiles[i][0].getPosition() - sf::Vector2f(-5, gridSize));
		yColumn.push_back(t1);
		t1.setString(s2[i]);
		t1.setPosition(tiles[0][i].getPosition() - sf::Vector2f(gridSize + 5, 0));
		xColumn.push_back(t1);
	}
}

void Grid::draw(sf::RenderWindow& window)
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

void Grid::tileSelect(sf::Vector2i mousePos)
{
	//reset previously selected tile
	tiles[selectedTile.x][selectedTile.y].setFillColor(sf::Color(0x39, 0x47, 0xb8, 0xff));
	isAnySelected = false;
	//check if mouse is inside of the grid
	if (mousePos.x > position.x && mousePos.x < position.x + (gridColumns * gridSize) && mousePos.y > position.y && mousePos.y < position.y + (gridRows * gridSize)) {
		int tileX = (mousePos.x - position.x) / gridSize;
		int tileY = (mousePos.y - position.y) / gridSize;
		selectedTile = sf::Vector2i(tileX, tileY);
		tiles[tileX][tileY].setFillColor(sf::Color::Yellow);
		isAnySelected = true;
	}
}

bool Grid::canPlaceShip(Ship& s)
{
	if (!isAnySelected) return false;
	if (s.getType() == 1)
	{
		if (isFree(selectedTile)) return true;
	}
	else
	{
		if (s.isHorizontal())
		{
			if (isFree(selectedTile) && isFree(sf::Vector2i(selectedTile.x + s.getType() - 1, selectedTile.y)))
				return true;
		}
		else {
			if (isFree(selectedTile) && isFree(sf::Vector2i(selectedTile.x, selectedTile.y + s.getType() - 1)))
				return true;
		}
	}
	return false;
}


bool Grid::canPlaceShipOnPosition(Ship& s, int x, int y)
{
	if (s.getType() == 1)
	{
		if (isFree(sf::Vector2i(x,y))) return true;
	}
	else
	{
		if (s.isHorizontal())
		{
			if (isFree(sf::Vector2i(x, y)) && isFree(sf::Vector2i(x + s.getType() - 1, y)))
				return true;
		}
		else {
			if (isFree(sf::Vector2i(x, y)) && isFree(sf::Vector2i(x, y + s.getType() - 1)))
				return true;
		}
	}
	return false;
}

sf::Vector2i Grid::getTilePosition(int x, int y)
{
	return (sf::Vector2i)tiles[x][y].getPosition();
}

sf::Vector2i Grid::getHoveredTilePosition()
{
	return (sf::Vector2i)tiles[selectedTile.x][selectedTile.y].getPosition();
}


void Grid::placeShip(Ship& s)
{	
	if (s.isPlaced())
	{
		int tileX = (s.getPosition().x - position.x) / gridSize;
		int tileY = (s.getPosition().y - position.y) / gridSize;
		for (int i = 0; i < s.getType(); i++)
		{
			if (s.isHorizontal())
			{
				fields[tileX + i][tileY] = fieldType::Ship;
			}
			else
			{
				fields[tileX][tileY + i] = fieldType::Ship;
			}
		}
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; i++) {
				std::cout << (int)fields[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}


void Grid::placeShipOnPosition(Ship& s, int x, int y)
{
	for (int i = 0; i < s.getType(); i++)
	{
		if (s.isHorizontal())
		{
			fields[x + i][y] = fieldType::Ship;
		}
		else
		{
			fields[x][y + i] = fieldType::Ship;
		}
	}
}

void Grid::clearSpace(Ship& s)
{
	int tileX = (s.getPosition().x - position.x) / gridSize;
	int tileY = (s.getPosition().y - position.y) / gridSize;
	for (int i = 0; i < s.getType(); i++)
	{
		if (s.isHorizontal())
		{
			fields[tileX + i][tileY] = fieldType::Empty;
		}
		else
		{
			fields[tileX][tileY + i] = fieldType::Empty;
		}
	}
}