#include "Menu.h"

Menu::Menu(Stored_menu menu,const sf::Vector2u &windowSize) : menu_class(menu)
{
	this->terminate = 0;

	if (this->menu_class == Menu::Stored_menu::main)
	{
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x/2, windowSize.y / 2), "TYPE NAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*1), "JOIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*2), "CREATE GAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*3), "SCOREBOARD"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*4), "EXIT"));
		
		for (unsigned int i = 0; i < this->elements.size(); i++)
		{
			elements[i]->setPosition(sf::Vector2f(windowSize.x / 2, 140 + (70 * i)));
		}
		//Agata tutaj dajesz odpalenie kolejnego menu na przycisk
		this->elements[1]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			Menu m(Menu::Stored_menu::join, window.getSize());
			m.run(window);
			return Button::ButtonState::Maintain;
		};
		this->elements[2]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			Menu m(Menu::Stored_menu::host, window.getSize());
			m.run(window);
			return Button::ButtonState::Maintain;
		};
		this->elements[3]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			Menu m(Menu::Stored_menu::scoreboard, window.getSize());
			m.run(window);
			return Button::ButtonState::Maintain;
		};
		this->elements[4]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};
	}
	else if (this->menu_class == Menu::Stored_menu::join)
	{
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), "IP address"));
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70), "PIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 + 70), "join"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 + 70 + 70), "back"));

		//Agata tutaj dodajesz zamkniêcie menu przycisk
		this->elements[3]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};

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
	while (!this->terminate)
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
				NetworkParameters parameters;
				if (elem->click(window, parameters) == Button::ButtonState::Terminate)
				{
					this->terminate = true;
				}
			}
		}
		else
		{
			elem->restoreColors();
		}
	}
}


