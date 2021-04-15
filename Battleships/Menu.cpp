#include "Menu.h"
#include <string>

std::string arr_to_string(std::array<char, 4> arr)
{
	std::string s = "";
	for (const auto& c : arr)
	{
		s += c;
	}
	return s;
}

Menu::Menu()
{
	this->menu_class = Menu::main;
	this->terminate = 0;
}

Menu::Menu(Stored_menu menu, const sf::Vector2u& windowSize) : menu_class(menu)
{
	this->terminate = 0;

	if (this->menu_class == Menu::Stored_menu::main)
	{
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 1), "USER", "TYPE NAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 2), "JOIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 3), "CREATE GAME"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 4), "SCOREBOARD"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 5), "EXIT"));

		/*for (unsigned int i = 0; i < this->elements.size(); i++)
			{
				elements[i]->setPosition(sf::Vector2f(windowSize.x / 2, 210 + (70 * i)));
			}
		*/
		this->elements[0]->on_update() = [](std::string& text)
		{
			globalParameters.playerName = text;
		};
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
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3), "IP address", "IP addres"));
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 + 35), std::to_string(globalParameters.remotePort), "PORT"));
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + (70 + 35) * 2), arr_to_string(globalParameters.pin), "PIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + (70 + 35) * 2 + 70), "join"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + (70 + 35) * 2 + (70 * 2)), "back"));


		this->elements[0]->on_update() = [](std::string& text)
		{
			std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");

			if (regex_match(text, ipv4))
			{
				globalParameters.remoteIP = (sf::IpAddress)text;
			}
		};
		this->elements[1]->on_update() = [](std::string& text)
		{
			text.erase(std::remove_if(text.begin(), text.end(), [](unsigned char x) {return (x < 48 || x>57); }));
			if (text.size() == 0) globalParameters.remotePort = 0;
			else if (std::stoi(text) > 65535)
			{
				text = "65535";
				globalParameters.remotePort = std::stoul(text, nullptr, 0);
			}
			else if (text.size() > 5)
			{
				text = text.substr(0, 5);
				globalParameters.remotePort = std::stoul(text, nullptr, 0);
			}
			else globalParameters.remotePort = std::stoul(text, nullptr, 0);
		};

		this->elements[2]->on_update() = [](std::string& text)
		{
			text.erase(std::remove_if(text.begin(), text.end(), [](unsigned char x) {return (x < 48 || x>57); }));
			if (text.size() > 4)text = text.substr(0, 4);
			if (text.size() == 4)
			{
				globalParameters.pin[0] = text[0];
				globalParameters.pin[1] = text[1];
				globalParameters.pin[2] = text[2];
				globalParameters.pin[3] = text[3];
			}

		};

		this->elements[3]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			Joiner joiner;
			try
			{
				joiner.connect();
			}
			catch (std::string e)
			{
				std::cout << e << std::endl;
			}
			return Button::ButtonState::Terminate;
		};

		//Agata tutaj dodajesz zamkniêcie menu przycisk
		this->elements[4]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};

	}
	else if (this->menu_class == Menu::Stored_menu::host)
	{
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 1), sf::IpAddress::getLocalAddress().toString()));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 2), std::to_string(globalParameters.localPort)));
		this->elements.push_back(std::make_shared<TextField>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 3 + 35), arr_to_string(globalParameters.pin), "PIN"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 4+35), "NEXT"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 + 70 * 5 + 35), "back"));

		this->elements[2]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{

			ListenerMenu menu(Menu::Stored_menu::waiting, window.getSize());
			menu.run(window);
			return Button::ButtonState::Terminate;
		};
		this->elements[4]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};

	}
	else if (this->menu_class == Menu::Stored_menu::scoreboard)
	{

		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(Button::rectangleSize.x / 1.75, windowSize.y - Button::rectangleSize.y), "back"));

		this->elements[0]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};
	}

}

void Menu::draw(sf::RenderWindow& window)
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

void Menu::mouseEvent(const sf::Vector2f& mousePosition, sf::RenderWindow& window)
{

	for (auto& elem : this->elements)
	{
		if (elem->getGlobalBounds().contains(mousePosition))
		{
			elem->hover();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (!is_pressed)
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
				is_pressed = true;

			}
			else
			{
				is_pressed = false;

			}
		}
		else
		{
			elem->restoreColors();
		}
	}
}



