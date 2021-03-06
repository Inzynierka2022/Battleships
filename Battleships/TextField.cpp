#include "TextField.h"

sf::Color TextField::rectangleOutlineColor = sf::Color(0, 0, 255,220);
sf::Color TextField::rectangleColor = sf::Color(0, 0, 255, 128);
sf::Color TextField::color1 = sf::Color(255, 215, 0);
sf::Color TextField::transparent_color = sf::Color(10, 10, 10);

TextField::TextField(const sf::Vector2f& position, std::string content, std::string constContent) : Button(position, content)
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
	this->display_promt();

	this->text2.setFont(this->font);
	this->text2.setCharacterSize(this->text.getCharacterSize());
	this->text2.setString(constContent);
	this->text2.setFillColor(sf::Color(50, 50, 50));
	sf::FloatRect textRect = text2.getLocalBounds();
	this->text2.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//this->text2.setPosition(text.getPosition()-text2.getOrigin() - text2.getOrigin());
	this->text2.setPosition({ position.x,position.y - rectangleSize.y });
	//this->text2.setPosition(text.getPosition());

}
void TextField::draw(sf::RenderWindow& window)
{
	window.draw(this->rectangle);
	window.draw(this->text);
	window.draw(this->text2);
	if (active) window.draw(this->text1);
}

void TextField::backspace()
{
	std::string tmp = this->text.getString();
	if (tmp.size() > 0)
	{
		tmp.pop_back();
		this->functionality2(tmp);
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
	this->calculateOrigin();
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

	this->functionality2(tmp);
	this->text.setString(tmp);
	display_promt();

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

Button::ButtonState TextField::click(sf::RenderWindow& unused1, NetworkParameters unused2)
{
	this->display_promt();
	this->active = 1;
	this->rectangle.setFillColor(TextField::transparent_color);
	this->rectangle.setOutlineColor(TextField::transparent_color);
	return Button::ButtonState::Maintain;
}

void TextField::setPosition(const sf::Vector2f& p)
{
	this->rectangle.setPosition(p);
	this->text.setPosition(p);
}

void TextField::display_promt()
{
	this->text1.setPosition(this->text.findCharacterPos(this->text.getString().getSize() + 2));
}

std::function<void(std::string&)>& TextField::on_update()
{
	return this->functionality2;
}
