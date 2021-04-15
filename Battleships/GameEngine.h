#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "TCPCommunicator.h"
#include "Ships.h"
#include "Button.h"
#include <memory>
#include <thread>

class GameEngine
{
private:
	Grid gridA = Grid(sf::Vector2i(80, 100));
    Grid gridB = Grid(sf::Vector2i(560, 100));
	Ships ships = Ships();
	int gameState;	
	/*
	0 - placing ships
	1 - ready/waiting for opponent
	*/
	std::vector<Button*> buttons;
	std::shared_ptr<TCPCommunicator> communicator;

public:
	GameEngine(std::shared_ptr<TCPCommunicator>);
	void run(sf::RenderWindow&/*,std::shared_ptr<TCPCommunicator> c*/);
};

