#include "Package.h"

sf::Packet Package::asPacket()
{
	sf::Packet packet;
	packet << this->content;
	return packet;
}

Package::Package()
{
	this->content = "BLANK";
}

Package::Package(sf::Packet &packet)
{
	packet >> this->content;
}

Package::Package(const std::string&s)
{
	this->content = s;
}

void Package::set_type_ready()
{
	this->content = "R";
}

void Package::set_type_change_turn()
{
	this->content = "C";
}

void Package::set_type_finish_game()
{
	this->content = "F";
}

void Package::set_type_disconnect_game()
{
	this->content = "D";
}

void Package::set_type_player_name(const std::string& s)
{
	this->content = "N" + s;
}

void Package::set_type_hit(const int&i)
{
	this->content = "H" + std::to_string(i);
}

void Package::set_type_answer(const std::string&s)
{
	this->content = "A" + s;
}

void Package::set_type_start_game()
{
	this->content = "S";
}

void Package::set_type_starting_player(const std::string &s)
{
	this->content = "B" + s;
}

void Package::set_type_time(const int &i)
{
	this->content = "T"+std::to_string(i);
}

void Package::set_type_ping()
{
	this->content = "PING";
}

void Package::set_type_pong()
{
	this->content = "PONG";
}

void Package::set_type_request_pin()
{
	this->content = "PIN_REQUEST";
}

void Package::set_type_send_pin(std::array<char, 4> arr)
{
	this->content = "PIN;";
	this->content.push_back(arr[0]);
	this->content.push_back(arr[1]);
	this->content.push_back(arr[2]);
	this->content.push_back(arr[3]);
}

void Package::set_type_validate_pin()
{
	this->content = "PIN_VALID";
}

std::string Package::get_content() const
{
	return this->content;
}

sf::Packet& operator>>(sf::Packet& packet, Package& package)
{
	return packet >> package.content;
}

sf::Packet& operator<<(sf::Packet& packet, Package& package)
{
	return packet << package.content;
}
