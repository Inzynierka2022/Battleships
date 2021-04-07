#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <array>


struct NetworkParameters
{
    std::string playerName;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    unsigned short port = 8888;
    std::array<char, 4> pin = { '0', '0', '0', '0' };
};

extern NetworkParameters globalParameters;

class Runnable
{
public:
	virtual void run(sf::RenderWindow&) = 0;
	virtual void draw(sf::RenderWindow&) = 0;
};

