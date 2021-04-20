#include "Joiner.h"
#include <iostream>

std::shared_ptr<sf::TcpSocket> Joiner::connect()
{
    this->socket = std::make_shared<sf::TcpSocket>();
    this->socket->setBlocking(true);
    sf::Clock clock;

    clock.restart();
    while(clock.getElapsedTime().asMilliseconds() <= __WAITING_TIME_MS)
    {
        std::cout << "connecting to: " << globalParameters.remoteIP << ":" << globalParameters.remotePort << std::endl;

        if (this->socket->connect(globalParameters.remoteIP, globalParameters.remotePort, sf::Time(sf::milliseconds(__WAITING_TIME_MS))) == sf::Socket::Done)
        {
            std::cout << socket->getLocalPort() << std::endl;
            std::cout << "done" << std::endl;
            if (this->validatePin() == true)
            {
                return this->socket;
            }
            else
            {
                std::string s = "Wrong pincode";
                throw s;
            }
        }
    }
    std::string errorCode = "Could not find server ";
    errorCode += globalParameters.remoteIP.toString();
    throw errorCode;
}

bool Joiner::validatePin()
{
    sf::Packet packet;

    sf::Clock clock;

    clock.restart();
    while (clock.getElapsedTime().asMilliseconds() <= __PIN_VALIDATION_TIME_MS)
    {
        if (this->socket->receive(packet) == sf::Socket::Done)
        {
            Package package(packet);
            std::cout << "received: " << package.get_content() << std::endl;
            if (package.get_content() == "PIN_VALID")return true;
            else if (package.get_content() == "PIN_REQUEST")
            {
                package.set_type_send_pin(globalParameters.pin);
                packet = package.asPacket();
                this->socket->send(packet);
            }
        }

    }
    return false;
}

std::shared_ptr<sf::TcpSocket> Joiner::getSocket()
{
    return this->socket;
}
