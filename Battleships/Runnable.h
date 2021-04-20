#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <array>
#include <iostream>


#define __WAITING_TIME_MS 2000
#define __PIN_VALIDATION_TIME_MS 5000

struct NetworkParameters
{
    std::string playerName;
    sf::IpAddress remoteIP = sf::IpAddress::getLocalAddress();
    unsigned short remotePort = 8888;
    unsigned short localPort = 8888;
    std::array<char, 4> pin = { '0', '0', '0', '0' };
    std::string lastErrorCode = "";
};

extern NetworkParameters globalParameters;

class Runnable
{
public:
	virtual void run(sf::RenderWindow&) = 0;
	virtual void draw(sf::RenderWindow&) = 0;
};

