#include "Menu.h"


Menu::Menu() : 
type_name(sf::Vector2f(200, 50)),
join_button(sf::Vector2f(200,50+70), "  join"), 
create_game_button(sf::Vector2f(200, 50+70+70), "  create game"),
scoreboard(sf::Vector2f(200, 50+70+70+70), "  scoreboard")
{

}

void Menu::draw(sf::RenderWindow &window)
{
	this->type_name.draw(window);
	this->join_button.draw(window);
	this->create_game_button.draw(window);
	this->scoreboard.draw(window);
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
					if (this->type_name.is_active())
					{
						this->type_name.add_character(static_cast<char>(event.text.unicode));
					}
				}
			}
		}

		window.clear();
		this->mouseEvent((sf::Vector2f)sf::Mouse::getPosition(window));
		this->draw(window);
		window.display();
		
	}
}

void Menu::mouseEvent(const sf::Vector2f &mousePosition)
{
	if (type_name.getGlobalBounds().contains(mousePosition))
	{
		type_name.hover();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			type_name.click();
		}
	}
	else
	{
		type_name.restoreColors();
	}

	if (join_button.getGlobalBounds().contains(mousePosition))
	{
		join_button.invertColors();
	}
	else
	{
		join_button.restoreColors();
	}


	if (join_button.getGlobalBounds().contains(mousePosition))
	{
		join_button.invertColors();
	}
	else
	{
		join_button.restoreColors();
	}

	if (create_game_button.getGlobalBounds().contains(mousePosition))
	{
		create_game_button.invertColors();
	}
	else
	{
		create_game_button.restoreColors();
	}

	if (scoreboard.getGlobalBounds().contains(mousePosition))
	{
		scoreboard.invertColors();
	}
	else
	{
		scoreboard.restoreColors();
	}
}


