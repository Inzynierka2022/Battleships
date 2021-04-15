#pragma once
#include <SFML/Network.hpp>
#include <memory>
#include "Runnable.h"
#include "Package.h"

class Joiner
{
private:
	std::shared_ptr<sf::TcpSocket> socket;

public:
	std::shared_ptr<sf::TcpSocket> connect();
	bool validatePin();


};

