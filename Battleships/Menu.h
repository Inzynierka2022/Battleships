#pragma once
#include "Button.h"
#include "TextField.h"
#include "Runnable.h"
#include <iostream>
#include <vector>
#include <memory>

class Menu : public Runnable
{


public:
	enum Stored_menu
	{
		main,
		join,
		host,
		scoreboard,
		waiting
	};


	/*Button join_button;
	Button create_game_button;
	Button scoreboard;
	TextField type_name;*/
	std::vector<std::shared_ptr<Button>> elements;

private:
	Stored_menu menu_class;
	bool terminate;
public:
	Menu(Stored_menu, const sf::Vector2u&);
	void draw(sf::RenderWindow&);
	void run(sf::RenderWindow&);
	void mouseEvent(const sf::Vector2f&, sf::RenderWindow&);
};

