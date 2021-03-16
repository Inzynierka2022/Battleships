#include "TextField.h"

sf::Color TextField::rectangleOutlineColor = sf::Color(0, 0, 255);
sf::Color TextField::rectangleColor = sf::Color(0, 0, 255, 128);
sf::Color TextField::color1 = sf::Color(0, 255, 0);
sf::Color TextField::transparent_color = sf::Color::Transparent;

TextField::TextField(const sf::Vector2f& position) : Button(position, "  Type name")
{
	this->active = 0;
	this->rectangle.setSize(Button::rectangleSize);
	this->rectangle.setOutlineColor(TextField::rectangleOutlineColor);
	this->rectangle.setFillColor(TextField::rectangleColor);
	this->rectangle.setOutlineThickness(-5);
	this->text.setFillColor(TextField::color1);
}
void TextField::backspace()
{
	std::string tmp = this->text.getString();
	if (tmp.size() > 0)
	{
		tmp.pop_back();
		this->text.setString(tmp);
	}
	else
	{
		this->text.setString("");
	}
}

void TextField::add_character(const char &c)
{
	if (c == '\u0008')
	{
		this->backspace();
		return;
	}
	if (c == 27 || c == 13)
	{
		this->active = false;
		return;
	}
	std::string tmp = this->text.getString();
	tmp += c;
	this->text.setString(tmp);
}

bool TextField::is_active() const
{
	return this->active;
}

void TextField::hover()
{
	if (active) return;
	this->rectangle.setFillColor(TextField::rectangleColor);
	this->rectangle.setOutlineColor(TextField::rectangleOutlineColor);
}

void TextField::restoreColors()
{
	if (this->active) return;
	this->rectangle.setFillColor(TextField::rectangleOutlineColor);
	this->rectangle.setOutlineColor(TextField::rectangleColor);
}

void TextField::click()
{
	this->active = 1;
	this->rectangle.setFillColor(TextField::transparent_color);
	this->rectangle.setOutlineColor(TextField::transparent_color);
}
