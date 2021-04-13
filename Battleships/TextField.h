#pragma once
#include "Button.h"
#include <string>
#include <iostream>

class TextField : public Button
{
private:
	void backspace();
	//std::function<void(std::string)> functionality = [](std::string text) {return ButtonState::Maintain; };
protected:
	sf::Text text1;
	sf::Text text2;
public:
	void add_character(const char&);
	void draw(sf::RenderWindow& );
	bool is_active() const;
	
	TextField(const sf::Vector2f&, std::string, std::string);

	static sf::Color rectangleOutlineColor;
	static sf::Color rectangleColor;
	static sf::Color color1;
	static sf::Color transparent_color;

	virtual void setPosition(const sf::Vector2f&);
	void hover();
	void restoreColors();
	ButtonState click(sf::RenderWindow&, NetworkParameters);
	void display_promt();
	std::function<void(std::string&)>& on_update();


};

