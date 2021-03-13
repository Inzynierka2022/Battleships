#include "Menu.h"


Menu::Menu() : join_button(sf::Vector2f(200,50), "  join"), 
create_game_button(sf::Vector2f(200, 50+70), "  create game"),
scoreboard(sf::Vector2f(200, 50+70+70), "  scoreboard")
{

}

void Menu::draw(sf::RenderWindow &window)
{
	this->join_button.draw(window);
	this->create_game_button.draw(window);
	this->scoreboard.draw(window);
}
bool Menu::changeColor(sf::RenderWindow& window)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		//((sf::Mouse::getPosition().x > 200) && (sf::Mouse::getPosition().y > 50) &&
		//(sf::Mouse::getPosition().x < (200 + 350)) && (sf::Mouse::getPosition().y < (50 + 35)))
	{
		//if (!mouse_on_button)
		{
			this->join_button.rectangleColor = sf::Color::Red;
			this->join_button.draw(window);
			return 1;
			
		}
	}
}

