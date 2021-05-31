#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "TCPCommunicator.h"
#include "Ships.h"
#include "Button.h"
#include <memory>
#include <thread>
//#include <ctime>

class GameEngine
{
private:
	Grid gridA = Grid(sf::Vector2i(80, 100));
    Grid gridB = Grid(sf::Vector2i(560, 100));
	Ships ships = Ships();
	int gameState;	//0 not ready //1 ready //2 game running
	bool turn = false;
	bool isHost = false;
	int remainingTime = 0;
	/*
	0 - placing ships
	1 - ready/waiting for opponent
	2 - playing game
	3 - game finished
	*/
	std::vector<Button*> buttons;
	std::shared_ptr<TCPCommunicator> communicator;
	std::shared_ptr<std::vector<Package>> packages;

	sf::Clock timer;
	int time_counter = 0;
	int hit = 0;
	int miss = 0;

public:
	const int time_to_start = 10; //60
	const int turn_time = 10; //30
	GameEngine(std::shared_ptr<TCPCommunicator>,bool);
	~GameEngine();
	void run(sf::RenderWindow&/*,std::shared_ptr<TCPCommunicator> c*/);
	bool chooseStartingPlayer();
	void managePackages();
	void setTime(int);
	void changeTurn();
	void incHit();
	void incMiss();
	bool isFinished() const;
};

