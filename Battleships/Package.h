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
	Package(const std::string&);
	
	void set_type_finish_game();
	void set_type_player_name(const std::string&);
	void set_type_hit(const int&);
	void set_type_answer(const std::string&);
	void set_type_start_game();
	void set_type_starting_player(const std::string&);
	void set_type_time(const int&);
	void set_type_ping();
	void set_type_pong();
	void set_type_request_pin();
	void set_type_send_pin(std::array<char, 4>);
	void set_type_validate_pin();
	std::string get_content() const;
};