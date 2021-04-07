#pragma once
#include "Menu.h"
#include "Listener.h"
class ListenerMenu : public Menu
{
private:
	
public:
	ListenerMenu(Stored_menu, const sf::Vector2u&);
	virtual void run(sf::RenderWindow&);
};

