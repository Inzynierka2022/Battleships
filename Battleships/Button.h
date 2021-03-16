#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
class Button
{
private:


protected:
	sf::RectangleShape rectangle;
	sf::Text text;

public:
	sf::Font font;
	static std::string fontFile;
	static sf::Vector2f rectangleSize;
	static sf::Color rectangleOutlineColor;
	static sf::Color rectangleColor;
	static sf::Color textColor;
	static int8_t rectangleOutlineThickness;


	Button(const sf::Vector2f& position, std::string content);
	void draw(sf::RenderWindow& window);

	void setPosition(const sf::Vector2f&);
	sf::Vector2f getPosition() const;
	void setString(const std::string &);

	void invertColors();

	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();

	void restoreColors();
};

	

