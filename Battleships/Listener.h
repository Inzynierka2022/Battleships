#pragma once
#include <SFML/Network.hpp>
#include "Runnable.h"
#include <mutex>
#include <memory>

class Listener
{
private:
	unsigned short localPort;
	std::array<char, 4> pin;

	std::mutex terminateFlagMutex;
	std::atomic<bool> terminateFlag;

	std::shared_ptr<sf::TcpSocket> remoteSocket;
	std::atomic<bool> connected;

	bool validatePin();
public:
	Listener();
	bool isConnected();
	void listen();
	void stopListening();
	std::shared_ptr<sf::TcpSocket> getRemoteSocket();
};

