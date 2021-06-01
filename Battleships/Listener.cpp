#include "Listener.h"

bool Listener::validatePin()
{
	bool pinSet = false;//pin is set or not
	for (unsigned int i = 0; i < 4; i++)
	{
		if (globalParameters.pin[i] != '0')
		{
			pinSet = true;
		}
	}

	Package package;
	sf::Packet packet;

	if (!pinSet)
	{
		//std::cout << "pin unset" << std::endl;
		package.set_type_validate_pin();
		//std::cout << "sending: " << package.get_content() << std::endl;
		packet = package.asPacket();
		this->remoteSocket->send(packet);
		return true;
	}

	
	package.set_type_request_pin();

	packet = package.asPacket();
	this->remoteSocket->send(packet);

	//std::cout << "sent: " << package.get_content() <<" to: "<<remoteSocket->getRemoteAddress().toString()<<":"<<remoteSocket->getRemotePort() <<std::endl;

	sf::Clock clock;

	clock.restart();
	while (clock.getElapsedTime().asMilliseconds() <= __PIN_VALIDATION_TIME_MS)
	{
		if (this->remoteSocket->receive(packet) == sf::Socket::Done)
		{
			Package remotePin(packet);

			//std::cout << "received: " << remotePin.get_content() << std::endl;
			remotePin.get_content();

			std::string localPin = "PIN;";
			localPin.push_back(globalParameters.pin[0]);
			localPin.push_back(globalParameters.pin[1]);
			localPin.push_back(globalParameters.pin[2]);
			localPin.push_back(globalParameters.pin[3]);

			//std::cout << remotePin.get_content() << " <> " << localPin << std::endl;
			return remotePin.get_content() == localPin;

			package.set_type_validate_pin();
			packet = package.asPacket();
			this->remoteSocket->send(packet);
			//std::cout << "sent: " << package.get_content() << std::endl;
			return true;
			break;

		}
	}
	return false;
}

Listener::Listener()
{
	this->remoteSocket = std::make_shared<sf::TcpSocket>();
	{
		std::lock_guard<std::mutex> lock(this->terminateFlagMutex);
		this->terminateFlag.store(false);
	}
	this->localPort = globalParameters.remotePort;
	this->pin = globalParameters.pin;
	this->connected.store(false);
}

bool Listener::isConnected()
{
	return this->connected.load();
}

void Listener::listen()
{
	sf::TcpListener listener;
	listener.setBlocking(false);
	listener.listen(this->localPort);

	while (true)
	{
		{
			std::lock_guard<std::mutex> lock(this->terminateFlagMutex);
			if (this->terminateFlag.load() == true) break;
		}
		
		if (listener.accept(*(this->remoteSocket)) == sf::Socket::Done)
		{
			if (this->validatePin())
			{
				this->connected.store(true);
				break;
			}
			else
			{
				//std::cout << "disconnecting" << std::endl;
				this->remoteSocket->disconnect();

				listener.close();
				listener.listen(this->localPort);

			}
		}
	}
}

void Listener::stopListening()
{
	std::lock_guard<std::mutex> lock(this->terminateFlagMutex);
	this->terminateFlag.store(true);
}

std::shared_ptr<sf::TcpSocket> Listener::getRemoteSocket()
{
	return this->remoteSocket;
}
