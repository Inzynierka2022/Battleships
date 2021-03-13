#pragma once
#include "Button.h"




class Menu
{
public:
	Button join_button;
	Button create_game_button;
	Button scoreboard;
public:
	Menu();
	void draw(sf::RenderWindow&);
	bool changeColor(sf::RenderWindow&);
};

