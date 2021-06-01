#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(std::shared_ptr<TCPCommunicator> s, bool hosting)
{
	isHost = hosting;
	communicator = s;
	gameState = 0;
	Button* readyButton = new Button(sf::Vector2f(700, 700), "not ready");
	buttons.push_back(readyButton);
	Button* timer = new Button(sf::Vector2f(700, 600), std::to_string(this->time_to_start));
	buttons.push_back(timer);
	Button* myName = new Button(sf::Vector2f(270, 33), globalParameters.playerName);
	buttons.push_back(myName);
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
	srand(time(NULL));
	bool dragShip = false;
	bool buttonPressed = false;
	//int time_counter = 0;
	std::thread communicator_thread(&TCPCommunicator::run, this->communicator);
	//receive
	//sf::Clock timer;
	//buttons pressed
	bool lpm = false;

	if (isHost)
	{
		turn = this->chooseStartingPlayer();
		/*if (turn)
		{
			Package package;
			package.set_type_starting_player(turn);
			this->communicator->send(package);
		}
		else
		{
			Package package("false");
			this->communicator->send(package);
		}*/
		writeToFile("name1", "name2", "3211349", "scoreboard.txt");
		Package package;
		if (turn) package.set_type_starting_player("F");
		else package.set_type_starting_player("T");
		this->communicator->send(package);
		package.set_type_player_name(globalParameters.playerName);
		this->communicator->send(package);
	}
	timer.restart();
	while (window.isOpen())
	{
		this->packages = this->communicator->receive();
		this->managePackages();
		sf::Event event;
		while (window.pollEvent(event))
		{
			gridA.tileSelect(sf::Mouse::getPosition(window));
			gridB.tileSelect(sf::Mouse::getPosition(window));

			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					if (this->gameState == 0)
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
					else if (this->gameState == 2 && turn)
					{
						if (!lpm)
						{
							lpm = true;
							int bomb_tile = gridB.getTile();
							std::cout << "klik\t" << bomb_tile << '\n';
							if (bomb_tile >= 0)
							{
								//leci poprawny strza�
								//reset tury
								Package package;
								package.set_type_hit(bomb_tile);
								this->communicator->send(package);
								time_counter = 0;
								remainingTime = turn_time;
								package.set_type_time(remainingTime);
								this->communicator->send(package);
								setTime(remainingTime);
								timer.restart();
							}
						}
					}
					else if (this->gameState == 3)
					{
						if (!lpm)
						{
							lpm = true;
							auto x = sf::Mouse::getPosition(window);

						}
					}
				}


				if (event.mouseButton.button == sf::Mouse::Button::Right)
				{
					if (this->gameState == 0)
					{
						if (dragShip) ships.getDraggedShip().rotate();
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				if (this->gameState == 0)
					ships.randomize(this->gridA);
			}
		}

		if (isHost)
		{
			if (gameState == 0 || gameState == 1)
			{
				if (timer.getElapsedTime().asSeconds() >= 1.f)
				{
					time_counter++;
					timer.restart();
					this->remainingTime = this->time_to_start - time_counter;
					Package package;
					if (remainingTime >= 0 && !(gameState == 1 && isOpponentReady))
					{
						package.set_type_time(this->remainingTime);
						this->setTime(this->remainingTime);
					}
					else
					{
						//tutaj automatyczne losowanie pozycji statk�w
						if (!ships.checkIfAllPlaced())
						{
							this->ships.randomize(gridA);
						}
						package.set_type_start_game();
						communicator->send(package);
						//je�eli niewylosowane
						//
						package.set_type_time(turn_time);
						this->setTime(turn_time);
						gameState = 2;
						time_counter = 0;
						if (turn) buttons[0]->setString("your turn");
						else buttons[0]->setString("wait");
					}
					communicator->send(package);
				}
			}
			else if (gameState == 2)
			{
				//trwa gra
				if (timer.getElapsedTime().asSeconds() >= 1.f)
				{
					time_counter++;
					timer.restart();
					this->remainingTime = turn_time - time_counter;
					Package package;
					if (remainingTime >= 0)
					{
						package.set_type_time(this->remainingTime);
						this->setTime(this->remainingTime);
					}
					else
					{
						//tutaj automatyczny ruch
						//je�eli nie wybrany
						//
						package.set_type_change_turn();
						this->communicator->send(package);
						package.set_type_time(turn_time);
						this->setTime(turn_time);
						time_counter = 0;
						this->turn = !turn;
						
						if (turn) buttons[0]->setString("your turn");
						else buttons[0]->setString("wait");
					}
					communicator->send(package);
				}
			}
			else if (gameState == 3)
			{

				//koniec gry
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			if (!buttonPressed && gameState < 2)
			{
				buttonPressed = true;
				ships.resetShips();
				gridA.clearGrid();
				buttons[0]->setString("not ready");
				std::cout << "reset\n";
			}
			else if (!buttonPressed && gameState == 3)
			{
				//wr�c do menu
				buttonPressed = true;
				break;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (!buttonPressed && gameState < 2 && ships.checkIfAllPlaced())
			{
				buttonPressed = true;
				gameState = (gameState + 1) % 2;
				std::cout << gameState << '\n';
				if (gameState) buttons[0]->setString("ready");
				else buttons[0]->setString("not ready");
				Package package;
				package.set_type_ready();
				this->communicator->send(package);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if (!buttonPressed && gameState < 2)
			{
				if (window.hasFocus())
				{
					buttonPressed = true;
					this->gridA.clearGrid();
					this->ships.randomize(gridA);
				}
			}
		}
		else
		{
			buttonPressed = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			lpm = false;
		}

		window.clear();



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
		enemyShips.draw(window);

		gridA.drawMarkers(window);
		gridB.drawMarkers(window);
		for (auto x : buttons)
		{
			x->draw(window);
		}

		window.display();
	}
	this->communicator->stop_listening();
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
		int tile_number = 0;
		switch (tmp[0])
		{
		case 'T':
		{
			//czas
			this->remainingTime = std::stoi(tmp.substr(1, tmp.size() - 1));
			this->setTime(this->remainingTime);
			/*if (this->remainingTime == turn_time)
			{
				changeTurn();
			}*/
			if (this->remainingTime == turn_time && gameState == 2)
			{
				//turn = !turn;

			}
			break;
		}
		case 'H':
		{
			//pozycja statku do zestrzelenia
			tile_number = std::stoi(tmp.substr(1, tmp.size() - 1));
			if (gridA.checkTile(tile_number))
			{
				Package package;
				package.set_type_answer("T" + std::to_string(tile_number));
				this->communicator->send(package);
				this->gridA.changeField(tile_number, true);
				if (this->gridA.checkIfShipDestroyed(tile_number, -1))
				{
					this->gridA.destroyShip(tile_number, -1);
					package.set_type_answer("D" + std::to_string(tile_number));
					this->communicator->send(package);
				}
			}
			else
			{
				Package package;
				package.set_type_answer("F" + std::to_string(tile_number));
				changeTurn();
				this->communicator->send(package);
				this->gridA.changeField(tile_number, false);
				this->buttons[1]->setString(std::to_string(remainingTime));
			}
			time_counter = 0;
			timer.restart();
			this->remainingTime = turn_time;
			break;
		}
		case 'A':
		{
			//odpowiedz na zestrzelenie pola
			if (tmp[1] == 'T')
			{
				tile_number = std::stoi(tmp.substr(2, tmp.size() - 2));
				//this->remainingTime += turn_time;
				gridB.changeField(tile_number, true);
				incHit();
				if (isFinished())
				{
					this->writeToFile(globalParameters.playerName, this->opponentName, std::to_string((hit * 200) - (miss * 100)),"scoreboard.txt");
					this->gameState = 3;
					buttons[0]->setString("winner");
					Package package;
					package.set_type_finish_game();
					this->communicator->send(package);
				}

			}
			else if (tmp[1] == 'D')
			{
				tile_number = std::stoi(tmp.substr(2, tmp.size() - 2));
				this->gridB.destroyShip(tile_number, -1);

				int type;
				sf::Vector2i position;
				bool orientation;
				this->gridB.getDestroyedShipInfo(tile_number, type, position, orientation);
				this->enemyShips.showShip(type, position, orientation);
			}
			else
			{
				tile_number = std::stoi(tmp.substr(2, tmp.size() - 2));
				gridB.changeField(tile_number, false);
				changeTurn();
				incMiss();
			}
			break;
		}
		case 'B':
		{
			//wylosowany zaczynaj�cy
			if (tmp[1] == 'F') turn = false;
			else turn = true;
			break;
		}
		case 'S':
		{
			//komunikat startu gry
			if (!ships.checkIfAllPlaced())
			{
				ships.randomize(gridA);
			}
			this->gameState = 2;
			if (turn) buttons[0]->setString("your turn");
			else buttons[0]->setString("wait");
			break;
		}
		case 'N':
		{
			//odebranie nazwy gracza i wys�anie swojej
			//Button* opponent_name = new Button(sf::Vector2f(750, 33),tmp.substr(1,tmp.size()-1));
			this->opponentName = tmp.substr(1, tmp.size() - 1);
			buttons.push_back(new Button(sf::Vector2f(750, 33), this->opponentName));
			if (!isHost)
			{
				Package package;
				package.set_type_player_name(globalParameters.playerName);
				this->communicator->send(package);
			}
			break;
		}
		case 'F':
		{
			//koniec gry przegra�e�
			this->gameState = 3;
			buttons[0]->setString("loser");
			break;
		}
		case 'D':
		{
			//koniec gry roz��czone
			this->gameState = 3;
			buttons[0]->setString("Disconnected");
			break;
		}
		case 'C':
		{
			changeTurn();
			break;
		}
		case 'R':
		{
			isOpponentReady = !isOpponentReady;
			break;
		}
		case 'P':
		{
			Package p;
			p.set_type_pong();
			this->communicator->send(p);
			break;
		}
		}
	}
}

void GameEngine::setTime(int time)
{
	buttons[1]->setString(std::to_string(time));
}

void GameEngine::changeTurn()
{
	this->turn = !turn;
	if (turn) buttons[0]->setString("your turn");
	else buttons[0]->setString("wait");
}

void GameEngine::incHit()
{
	hit++;
}

void GameEngine::incMiss()
{
	miss++;
}


void GameEngine::writeToFile(std::string name1, std::string name2, std::string score, const std::string& name)
{
	std::string txt;
	std::vector<std::string> vectorTxt;
	std::fstream MyReadFile;


	MyReadFile.open(name.c_str(), std::ios::out | std::ios::in);

	while (!MyReadFile.eof())
	{
		MyReadFile >> txt;
		vectorTxt.push_back((std::string)txt);
		std::cout << "dodaje: " << txt << std::endl;
	}
	MyReadFile.close();
	MyReadFile.open(name.c_str(), std::ios::out | std::ofstream::trunc);

	for (int i = 4; i < vectorTxt.size(); i++)
	{
		if ((i % 4 == 3) && (std::stoi(score) > (std::stoi(vectorTxt[i]))))
		{
			vectorTxt[i - 2] = name1;
			vectorTxt[i - 1] = name2;
			vectorTxt[i] = score;
			break;
		}
	}

	for (int i = 0; i < vectorTxt.size() - 1; i++)
	{
		//MyReadFile.write((char*)&vectorTxt[i], sizeof(std::string));
		//MyReadFile.write(vectorTxt[i].c_str(), sizeof(std::string));
		i % 4 == 3 ? MyReadFile << vectorTxt[i] << "\n" : MyReadFile << vectorTxt[i] << "\t";
	}
	MyReadFile.close();

}

bool GameEngine::isFinished() const
{
	return hit == 20 ? true : false;
}
