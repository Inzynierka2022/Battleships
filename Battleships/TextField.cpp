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
	this->text1.setFillColor(TextField::color1);
	this->text1.setString("_");
	this->text1.setCharacterSize(this->text.getCharacterSize());
	
	this->text1.setFont(this->font);
	this->text1.setPosition(this->text.getPosition()+sf::Vector2f(1,0));
}
void TextField::draw(sf::RenderWindow& window)
{
	window.draw(this->rectangle);
	window.draw(this->text);
	if (active) window.draw(this->text1);
}

void TextField::backspace()
{
	std::string tmp = this->text.getString();
	if (tmp.size() > 0)
	{
		tmp.pop_back();
		this->text.setString(tmp);
		display_promt();

	}
	else
	{
		this->text.setString("");
		display_promt();

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
	display_promt();
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

void TextField::display_promt()
{
	this->text1.setPosition(this->text.findCharacterPos(this->text.getString().getSize() + 2) /*- sf::Vector2f(text.getCharacterSize(), 0)*/);
}
