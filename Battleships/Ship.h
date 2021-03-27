#pragma once
#include <SFML/Graphics.hpp>
class Ship
{
private:
	sf::RectangleShape rectangle;
	uint8_t type = 0;
	bool horizontal = true;
	sf::Texture* shipsTextures;
public:
	Ship();
	Ship(uint8_t type, sf::Vector2f position);
	void draw(sf::RenderWindow& window);
	bool checkMousePosition(sf::Vector2i mousePosition);
	void setPosition(sf::Vector2i position);
	sf::Vector2f getPosition() const;
	uint8_t getType() const;
	bool isHorizontal() const;
	void rotate();
	void setOrientation(bool _horizontal);
};

