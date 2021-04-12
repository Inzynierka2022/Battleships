#include "Listener.h"

bool Listener::validatePin()
{
	return true;
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
			this->connected.store(true);
			break;
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
