#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(std::shared_ptr<TCPCommunicator> s, bool hosting)
{
	isHost = hosting;
	communicator = s;
	gameState = 0;
	Button* readyButton = new Button(sf::Vector2f(700,700),"not ready");
	buttons.push_back(readyButton);
}

GameEngine::~GameEngine()
{
	for (auto x : this->buttons)
	{
		delete x;
		x = NULL;
	}
}

void GameEngine::run(sf::RenderWindow& window)
{
	bool dragShip = false;
	bool buttonPressed = false;
	int time_counter = 0;
	std::thread communicator_thread(&TCPCommunicator::run, this->communicator);
	//receive
	sf::Clock timer;
	if (isHost)
	{
		turn = this->chooseStartingPlayer();
		if (turn)
		{
			Package package("true");
			this->communicator->send(package);
		}
		else
		{
			Package package("false");
			this->communicator->send(package);
		}
		
	}
	timer.restart();
	while (window.isOpen())
	{
		this->packages = this->communicator->receive();
		this->managePackages();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left) 
				{
					if (ships.drag(sf::Mouse::getPosition(window), sf::Mouse::getPosition(window)))
					{
						dragShip = true;
						if (ships.checkIfPlaced())
						{
							gridA.clearSpace(ships.getDraggedShip());
						}
					}
				}

				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					if (dragShip) ships.getDraggedShip().rotate();
				}
			}
		}

		if (gameState < 2)
		{
			if (timer.getElapsedTime().asSeconds() >= 1.f)
			{
				time_counter++;
				timer.restart();
				//std::cout << this->time_to_start - time_counter << '\n';
				Package package;
				package.set_type_time(this->time_to_start - time_counter);
				communicator->send(package);
			}
			if (time_counter == this->time_to_start)
			{
				gameState = 3;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!buttonPressed && gameState<2)
			{
				buttonPressed = true;
				ships.resetShips();
				gridA.clearGrid();
				buttons[0]->setString("not ready");
				std::cout << "reset\n";
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!buttonPressed && gameState<2 && ships.checkIfAllPlaced())
			{
				buttonPressed = true;
				gameState = (gameState + 1) % 2;
				std::cout << gameState << '\n';
				if (gameState) buttons[0]->setString("ready");
				else buttons[0]->setString("not ready");
			}
		}
		else
		{
			buttonPressed = false;
		}

		window.clear();

		gridA.tileSelect(sf::Mouse::getPosition(window));
		gridB.tileSelect(sf::Mouse::getPosition(window));

		if (dragShip)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				ships.drag(sf::Mouse::getPosition(window), gridA.getHoveredTilePosition(), gridA.canPlaceShip(ships.getDraggedShip()));
			else
			{
				ships.stopDrag(gridA.canPlaceShip(ships.getDraggedShip()));
				gridA.placeShip(ships.getDraggedShip());
				dragShip = false;
			}
		}

		gridA.draw(window);
		gridB.draw(window);

		ships.draw(window);
		buttons[0]->draw(window);

		window.display();
	}
	communicator_thread.join();
}

bool GameEngine::chooseStartingPlayer()
{
	int count = 0;
	std::srand(time(NULL));
	for (int i = 0; i < 99; i++)
	{
		if (rand() % 2 == 1) count++;
	}
	std::cout << count << '\n';
	return count > 44;
}

void GameEngine::managePackages()
{
	for (auto& x : *this->packages)
	{
		std::string tmp = x.get_content();
		std::cout << tmp << '\n';
		switch (tmp[0])
		{
		case 'T':
			//czas
			this->remainingTime = std::stoi(tmp.substr(1, tmp.size() - 1));
			std::cout << this->remainingTime << '\n';
			break;
		case 'P':
			//pozycja statku
			break;
		}
	}
}

