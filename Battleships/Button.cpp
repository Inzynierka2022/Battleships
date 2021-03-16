#include "Button.h"

sf::Vector2f Button::rectangleSize = sf::Vector2f(350, 35);
std::string Button::fontFile = "SM.TTF";
sf::Color Button::rectangleOutlineColor = sf::Color::White;
sf::Color Button::rectangleColor = sf::Color(0,0,255,128);
sf::Color Button::textColor = sf::Color::White;
int8_t Button::rectangleOutlineThickness = -5;


Button::Button(const sf::Vector2f& position, std::string content)
{
	this->font.loadFromFile(Button::fontFile);

	this->rectangle.setSize(Button::rectangleSize);
	this->rectangle.setOutlineColor(Button::rectangleOutlineColor);
	this->rectangle.setFillColor(Button::rectangleColor);
	this->rectangle.setOutlineThickness(Button::rectangleOutlineThickness);
	this->text.setFont(Button::font);

	this->rectangle.setPosition(position);
	this->text.setPosition(position);

	this->text.setString(content);
	this->text.setFillColor(Button::textColor);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(this->rectangle);
	window.draw(this->text);
}

sf::Vector2f Button::getPosition() const
{
	return this->rectangle.getPosition();
}

void Button::invertColors()
{

	this->rectangle.setFillColor(Button::rectangleOutlineColor);
	this->rectangle.setOutlineColor(Button::rectangleColor);
}

void Button::restoreColors()
{
	this->rectangle.setFillColor(Button::rectangleColor);
	this->rectangle.setOutlineColor(Button::rectangleOutlineColor);
}

sf::FloatRect Button::getLocalBounds()
{
	return this->rectangle.getLocalBounds();
}

sf::FloatRect Button::getGlobalBounds()
{
	return this->rectangle.getGlobalBounds();
}

void Button::setString(const std::string& string)
{
	this->text.setString(string);
}

void Button::setPosition(const sf::Vector2f& pos)
{
	this->rectangle.setPosition(pos);
	this->text.setPosition(pos);
}

