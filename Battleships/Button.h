#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
class Button
{
protected:
	void calculateOrigin();
	bool active;

public:
	sf::RectangleShape rectangle;
	sf::Text text;

public:
	sf::Font font;
	static std::string fontFile;
	static sf::Vector2f rectangleSize;
	static sf::Color rectangleOutlineColor;
	static sf::Color rectangleColor;
	static sf::Color textColor;
	static int8_t rectangleOutlineThickness;

	Button();
	Button(const sf::Vector2f& position, std::string content);
	virtual void draw(sf::RenderWindow& window);

	virtual void setPosition(const sf::Vector2f&);
	sf::Vector2f getPosition() const;
	void setString(const std::string &);

	void invertColors();

	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();

	void setSize(const sf::Vector2f&);

	virtual void restoreColors();
	virtual void hover();
	virtual void add_character(const char&);
	virtual bool is_active() const;
	virtual void click();
	virtual void deactivate();
};

