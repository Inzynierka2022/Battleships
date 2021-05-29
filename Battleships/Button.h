#pragma once
#include "Label.h"
class Button : public Label
{
protected:
	void calculateOrigin();
	bool active;
	bool canHover;

	std::function<void(std::string&)> functionality2 = [](std::string &text) {return; };

public:
	//Used to return button status after click. Exit and back buttons return ButtonState::terminate
	enum ButtonState
	{
		Terminate = 0,
		Maintain,
		Error
	};

	sf::RectangleShape rectangle;
	sf::Text text;

private:
	std::shared_ptr<Runnable> runnable;
	std::function<Button::ButtonState(sf::RenderWindow&, NetworkParameters)> functionality = [](sf::RenderWindow&, NetworkParameters) {return Button::ButtonState::Maintain; };
	

public:


	static sf::Vector2f rectangleSize;
	static sf::Color rectangleOutlineColor;
	static sf::Color rectangleColor;
	static sf::Color textColor;
	static int8_t rectangleOutlineThickness;

	Button();
	Button(const sf::Vector2f& position, std::string content);
	virtual void draw(sf::RenderWindow& window);
	virtual void setPosition(const sf::Vector2f&);


	void invertColors();

	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();

	void setString(const std::string& string);
	void setCanHover(bool);
	void setSize(const sf::Vector2f&);

	virtual std::function<ButtonState(sf::RenderWindow&, NetworkParameters)>& on_click();
	virtual std::function<void(std::string&)>& on_update();
	sf::Vector2f getPosition() const;
	virtual void restoreColors();
	virtual void hover();
	virtual void add_character(const char&);
	virtual bool is_active() const;
	virtual ButtonState click(sf::RenderWindow&, NetworkParameters);
	virtual void deactivate();

};

