#include "Menu.h"

Menu::Menu(Stored_menu menu,const sf::Vector2u &windowSize) : menu_class(menu)
{
	if (this->menu_class == Menu::Stored_menu::main)
	{
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x/2, windowSize.y / 2), "TYPE NAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70), "JOIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 + 70), "CREATE GAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 + 70 + 70), "SCOREBOARD"));
		
		for (unsigned int i = 0; i < this->elements.size(); i++)
		{
			elements[i]->setPosition(sf::Vector2f(windowSize.x / 2, 140 + (70 * i)));
		}

		this->sub_menus.push_back(std::make_shared<Menu>(Menu::Stored_menu::join, windowSize));
		this->sub_menus.push_back(std::make_shared<Menu>(Menu::Stored_menu::host, windowSize));
	}
	else if (this->menu_class == Menu::Stored_menu::join)
	{
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), "IP address"));
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70), "PIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 + 70), "join"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 + 70 + 70), "back"));
	}
	else if (this->menu_class == Menu::Stored_menu::host)
	{
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), "127.0.0.1"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70), "NEXT"));
	}
	else if (this->menu_class == Menu::Stored_menu::waiting)
	{
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), "WAITING"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2+70), "127.0.0.1"));
	}
	
}

void Menu::draw(sf::RenderWindow &window)
{
	for (auto& elem : this->elements)
	{
		elem->draw(window);
	}
}

void Menu::run(sf::RenderWindow& window)
{
	while (1)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					for (auto& elem : elements)
					{
						if (elem->is_active())
						{
							elem->add_character(static_cast<char>(event.text.unicode));
						}
					}
					
					
				}
			}
		}

		window.clear();
		this->mouseEvent((sf::Vector2f)sf::Mouse::getPosition(window), window);
		this->draw(window);
		window.display();
		
	}
}

void Menu::mouseEvent(const sf::Vector2f &mousePosition, sf::RenderWindow& window)
{
	if (elements[1]->getGlobalBounds().contains(mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (auto& elem : this->elements)
			{
				elem->deactivate();
			}
			this->sub_menus[0]->run(window);
		}
	}


	for (auto& elem : this->elements)
	{
		if (elem->getGlobalBounds().contains(mousePosition))
		{
			elem->hover();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (auto& elem : this->elements)
				{
					elem->deactivate();
				}
				elem->click();
			}
		}
		else
		{
			elem->restoreColors();
		}
	}
}


