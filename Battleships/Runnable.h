#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

struct NetworkParameters
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	unsigned short port = 8888;
	char pin[4] = {'0', '0', '0', '0'};
};

class Runnable
{
public:
	virtual void run(sf::RenderWindow&) = 0;
	virtual void draw(sf::RenderWindow&) = 0;
};

