#pragma once
#include "Button.h"
#include "TextField.h"
#include <iostream>




class Menu
{
public:
	Button join_button;
	Button create_game_button;
	Button scoreboard;
	TextField type_name;
public:
	Menu();
	void draw(sf::RenderWindow&);
	void run(sf::RenderWindow&);
	void mouseEvent(const sf::Vector2f&);
};

