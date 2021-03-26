#include "Ship.h"

Ship::Ship()
{
}

Ship::Ship(uint8_t type, sf::Vector2f position)
{
	this->type = type;
	rectangle.setSize(sf::Vector2f(type * 40, 40));
	rectangle.setPosition(position);
	rectangle.setFillColor(sf::Color::White);
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
	if (type == 1) return;
	horizontal = !horizontal;
	sf::Vector2f size = rectangle.getSize();
	rectangle.setSize(sf::Vector2f(size.y, size.x));
}

void Ship::setOrientation(bool _horizontal)
{
	horizontal = _horizontal;
	if (horizontal)
		rectangle.setSize(sf::Vector2f(type * 40, 40));
	else
		rectangle.setSize(sf::Vector2f(40, type * 40));
}
