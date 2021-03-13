#pragma once
#include <SFML/Network.hpp>
#include "Package.h"
#include <vector>
#include <memory>
#include <mutex>

class TCPCommunicator
{
private:
	std::atomic_bool connected;

	std::mutex in_queue_mutex;
	std::vector<Package> in_queue;
	std::mutex out_queue_mutex;
	std::vector<Package> out_queue;

	std::shared_ptr<sf::TcpSocket> socket;

public:
	TCPCommunicator(std::shared_ptr<sf::TcpSocket>);
	void send(std::shared_ptr<std::vector<Package>>);
	void send(Package);
	std::shared_ptr<std::vector<Package>> receive();

	void run();
};

