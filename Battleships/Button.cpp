#include "Button.h"

sf::Vector2f Button::rectangleSize = sf::Vector2f(350, 55);
//std::string Button::fontFile = "SM.TTF";
sf::Color Button::rectangleOutlineColor = sf::Color(50, 50, 100, 200);
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

	this->rectangle.setOrigin({this->rectangle.getSize().x / 2, this->rectangle.getSize().y / 2});
	this->calculateOrigin();
}

void Button::calculateOrigin()
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(this->rectangle);
	window.draw(this->text);
}

std::function<Button::ButtonState(sf::RenderWindow&, NetworkParameters)>& Button::on_click()
{
	return this->functionality;
}

std::function<void(std::string&)>& Button::on_update()
{
	return this->functionality2;
}

sf::Vector2f Button::getPosition() const
{
	return this->rectangle.getPosition();
}

Button::Button()
{
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

void Button::deactivate()
{
	this->active = false;
}

void Button::add_character(const char&)
{
}

bool Button::is_active() const
{
	return false;
}

void Button::setSize(const sf::Vector2f &s)
{
	this->rectangle.setSize(s);
	this->calculateOrigin();
}

void Button::hover()
{
	if(this->canHover)this->invertColors();
}

Button::ButtonState Button::click(sf::RenderWindow& window, NetworkParameters parameters)
{
	return this->functionality(window, parameters);
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

void Button::setCanHover(bool b)
{
	this->canHover = b;
}

void Button::setPosition(const sf::Vector2f& pos)
{
	this->rectangle.setPosition(pos);
	this->text.setPosition(pos);
}
