#include "Label.h"

std::string Label::fontFile = "FELIXTI.ttf";
sf::Color Label::textColor = sf::Color::Red;

Label::Label()
{
}

Label::Label(sf::Vector2f pos, std::string s) : Label(pos)
{
    this->text.setString(s);

}

Label::Label(sf::Vector2f pos)
{
    this->text.setPosition(pos);
    if (!this->font.loadFromFile(Label::fontFile))
    {
        std::cout << "error, cannot load font" << std::endl;
    }
    this->text.setCharacterSize(20);
    sf::FloatRect textRect = text.getLocalBounds();
  
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    this->text.setFont(this->font);
    this->text.setFillColor(Label::textColor);
}

void Label::draw(sf::RenderWindow& window)
{
    window.draw(this->text);
}

void Label::setPosition(const sf::Vector2f &pos)
{
    this->text.setPosition(pos);
}

void Label::setString(const std::string &string)
{
    this->text.setString(string);
}

sf::Vector2f Label::getPosition() const
{
    return this->text.getPosition();
}

void Label::updateContent()
{
    this->text.setString(globalParameters.lastErrorCode);
}
