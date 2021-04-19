#include "TCPCommunicator.h"
#include <iostream>

void TCPCommunicator::send(std::shared_ptr<std::vector<Package>> messages)
{
	std::lock_guard<std::mutex> lock(this->out_queue_mutex);
	this->out_queue.insert(this->out_queue.end(), std::make_move_iterator(messages->begin()),
		std::make_move_iterator(messages->end()));

	messages->erase(messages->begin(), messages->end());
}

void TCPCommunicator::send(Package package)
{
	std::lock_guard<std::mutex> lock(this->out_queue_mutex);
	this->out_queue.push_back(package);
}

TCPCommunicator::TCPCommunicator(std::shared_ptr<sf::TcpSocket> socket)
{
	this->socket = socket;
	this->connected.store(true);
}

std::shared_ptr<std::vector<Package>> TCPCommunicator::receive()
{
	std::shared_ptr<std::vector<Package>> result = std::make_shared<std::vector<Package>>();

	std::lock_guard<std::mutex> lock(this->in_queue_mutex);

	result->insert(result->end(), std::make_move_iterator(this->in_queue.begin()),
		std::make_move_iterator(this->in_queue.end()));

	this->in_queue.erase(this->in_queue.begin(), this->in_queue.end());

	return result;
}

void TCPCommunicator::stop_listening()
{
	this->connected.store(true);
}

void TCPCommunicator::run()
{
	Package pack;
	sf::Packet packet;

	while (connected.load() == true)
	{
		if (this->socket->receive(packet) == sf::Socket::Done)
		{
			packet >> pack;
			{
				std::lock_guard<std::mutex> lock(this->in_queue_mutex);
				this->in_queue.push_back(pack);
				std::cout << pack.get_content() << '\n';
				continue;
			}
		}
		if (this->out_queue.size() > 0)
		{
			packet.clear();
			std::cout << out_queue.size() << '\n';
			std::lock_guard<std::mutex> lock(this->out_queue_mutex);
			packet << this->out_queue.front();
			this->out_queue.erase(this->out_queue.begin());
			this->socket->send(packet);

			continue;
		}
		packet.clear();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}


