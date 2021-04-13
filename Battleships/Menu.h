#pragma once
#include "Button.h"
#include "TextField.h"
#include "Runnable.h"
#include <iostream>
#include <vector>
#include <memory>

class ListenerMenu;

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

	std::vector<std::shared_ptr<Button>> elements;

protected:
	Menu();
	Stored_menu menu_class;
	bool terminate;
	bool is_pressed = true;
public:
	Menu(Stored_menu, const sf::Vector2u&);
	virtual void draw(sf::RenderWindow&);
	virtual void run(sf::RenderWindow&);
	void mouseEvent(const sf::Vector2f&, sf::RenderWindow&);
};

#include "ListenerMenu.h"

