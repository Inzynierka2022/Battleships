#include "Ship.h"

Ship::Ship()
{
}

Ship::Ship(uint8_t type, sf::Vector2f position)
{
	shipsTextures = new sf::Texture;
	shipsTextures->loadFromFile("ships.png");
	this->type = type;
	rectangle.setSize(sf::Vector2f(type * 40, 40));
	rectangle.setPosition(position);
	rectangle.setTexture(shipsTextures);
	rectangle.setTextureRect(sf::IntRect(0, 40 * (type - 1), 40 * type, 40));
}

void Ship::draw(sf::RenderWindow& window)
{
	window.draw(rectangle);
}

bool Ship::checkMousePosition(sf::Vector2i mousePosition)
{
	if (rectangle.getGlobalBounds().contains((sf::Vector2f)mousePosition))
		return true;
	return false;
}

void Ship::setPosition(sf::Vector2i position)
{
	rectangle.setPosition((sf::Vector2f)position);
}

sf::Vector2f Ship::getPosition() const
{
	return rectangle.getPosition();
}

uint8_t Ship::getType() const
{
	return type;
}

bool Ship::isHorizontal() const
{
	return horizontal;
}

void Ship::rotate()
{
	//if (type == 1) return;
	horizontal = !horizontal;
	sf::Vector2f size = rectangle.getSize();
	rectangle.setSize(sf::Vector2f(size.y, size.x));
	if (horizontal) rectangle.setTextureRect(sf::IntRect(0, 40 * (type - 1), 40 * type, 40));
	else rectangle.setTextureRect(sf::IntRect(40 * type, 0, 40, 40 * type));
}

void Ship::setOrientation(bool _horizontal)
{
	horizontal = _horizontal;
	if (horizontal)
	{
		rectangle.setSize(sf::Vector2f(type * 40, 40));
		rectangle.setTextureRect(sf::IntRect(0, 40 * (type - 1), 40 * type, 40));
	}
	else
	{
		rectangle.setSize(sf::Vector2f(40, type * 40));
		rectangle.setTextureRect(sf::IntRect(40 * type, 0, 40, 40 * type));
	}
}

void Ship::setPlaced(bool _placed)
{
	placed = _placed;
}

bool Ship::isPlaced()
{
	return placed;
}
