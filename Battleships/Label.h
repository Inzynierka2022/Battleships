#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <functional>
#include "Runnable.h"
class Label
{
public:
	Label();
	Label(sf::Vector2f, std::string);
	Label(sf::Vector2f);

	sf::Text text;
	sf::Font font;

	static std::string fontFile;
	static sf::Color textColor;


	virtual void draw(sf::RenderWindow& window);
	virtual void setPosition(const sf::Vector2f&);
	void setString(const std::string&);
	virtual sf::Vector2f getPosition() const;

	void updateContent();
};

