#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "TCPCommunicator.h"
#include <memory>

class GameEngine
{
private:
	Grid gridA = Grid(sf::Vector2i(80, 100));
    Grid gridB = Grid(sf::Vector2i(560, 100));
	uint8_t gameState;

public:
	GameEngine();
	void run(sf::RenderWindow&/*,std::shared_ptr<TCPCommunicator> c*/);
};

