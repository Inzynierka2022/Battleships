#include "Menu.h"
#include <string>

Menu::Menu()
{
	this->terminate = 0;
}

Menu::Menu(Stored_menu menu,const sf::Vector2u &windowSize) : menu_class(menu)
{
	this->terminate = 0;

	if (this->menu_class == Menu::Stored_menu::main)
	{
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x/2, windowSize.y / 2+70*1), "TYPE NAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*1), "JOIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*2), "CREATE GAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*3), "SCOREBOARD"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*4), "EXIT"));
		
		for (unsigned int i = 0; i < this->elements.size(); i++)
		{
			elements[i]->setPosition(sf::Vector2f(windowSize.x / 2, 210 + (70 * i)));
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
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2+70), "port number"));
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*2), "PIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 *3), "join"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*4), "back"));

		//Agata tutaj dodajesz zamkniêcie menu przycisk
		this->elements[4]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};

	}
	else if (this->menu_class == Menu::Stored_menu::host)
	{
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2),sf::IpAddress::getLocalAddress().toString()));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2+70*1),std::to_string(globalParameters.port)));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70*2), "NEXT"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 * 3), "back"));

		this->elements[2]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			ListenerMenu menu(Menu::Stored_menu::waiting, window.getSize());
			menu.run(window);
			return Button::ButtonState::Terminate;
		};
		this->elements[3]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};

	}
	else if (this->menu_class == Menu::Stored_menu::waiting)
	{
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), "WRONG MENU CLASS, USE ListenerMenu Instead"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2+70), "ERR"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 * 2), std::to_string(globalParameters.port)));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 * 3), "back"));

		this->elements[3]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};
	}
	else if (this->menu_class == Menu::Stored_menu::scoreboard)
	{

		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(Button::rectangleSize.x/1.75, windowSize.y-Button::rectangleSize.y), "back"));

		this->elements[0]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};
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
	sf::Texture texture;
	if (!texture.loadFromFile("background.png"));
	sf::Sprite sprite;
	sprite.setTexture(texture);

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

		this->mouseEvent((sf::Vector2f)sf::Mouse::getPosition(window), window);
		window.clear();
		window.draw(sprite);
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


