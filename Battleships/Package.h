#pragma once
#include <SFML/Network.hpp>
#include <string>
#include <array>

class Package
{
private:
	std::string content;
	friend sf::Packet& operator>>(sf::Packet&, Package&);
	friend sf::Packet& operator<<(sf::Packet&, Package&);
public:
	sf::Packet asPacket();

	Package();
	Package(sf::Packet&);

	void set_type_ping();
	void set_type_pong();
	void set_type_request_pin();
	void set_type_send_pin(std::array<char, 4>);
	void set_type_validate_pin();
	std::string get_content() const;
};