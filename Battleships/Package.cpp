#include "Package.h"

Package::Package()
{
	this->content = "BLANK";
}

void Package::set_type_ping()
{
	this->content = "PING";
}

void Package::set_type_pong()
{
	this->content = "PONG";
}

std::string Package::get_content() const
{
	return this->content;
}
