#pragma once
#include <SFML/Network.hpp>
#include <string>

class Package
{
private:
	std::string content;
	friend sf::Packet& operator>>(sf::Packet&, Package&);
	friend sf::Packet& operator<<(sf::Packet&, Package&);
public:
	Package();
	void set_type_ping();
	void set_type_pong();
	std::string get_content() const;
};

sf::Packet& operator>>(sf::Packet& packet, Package& package)
{
	return packet >> package.content;
}

sf::Packet& operator<<(sf::Packet& packet, Package& package)
{
	return packet << package.content;
}