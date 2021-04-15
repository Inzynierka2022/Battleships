#include "ListenerMenu.h"

ListenerMenu::ListenerMenu(Stored_menu menu, const sf::Vector2u& windowSize)
{
	this->menu_class = menu;
	this->terminate = 0;

	if (this->menu_class == Menu::Stored_menu::waiting)
	{
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2), "WAITING"));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70), sf::IpAddress::getLocalAddress().toString()));
		this->elements.push_back(std::make_shared<Button>(sf::Vector2f(windowSize.x / 2, windowSize.y / 2 + 70 * 2), "back"));

		this->elements[2]->on_click() = [](sf::RenderWindow& window, NetworkParameters parameters)
		{
			return Button::ButtonState::Terminate;
		};
	}

}

void ListenerMenu::run(sf::RenderWindow& window)
{
	sf::Texture texture;
	if (!texture.loadFromFile("background.png"));
	sf::Sprite sprite;
	sprite.setTexture(texture);

	std::cout << "listening" << std::endl;
	Listener listener;
	std::thread listenerThread(&Listener::listen, &listener);
	

	while (!this->terminate)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					for (auto& elem : elements)
					{
						if (elem->is_active())
						{
							elem->add_character(static_cast<char>(event.text.unicode));
						}
					}


				}
			}
		}
		//Check for connected client
		if (listener.isConnected() == true)
		{
			std::cout << "Client connected" << std::endl;
			//Start game here
			std::shared_ptr<TCPCommunicator> communicator = std::make_shared<TCPCommunicator>(listener.getRemoteSocket());
			GameEngine game_engine(communicator);
			game_engine.run(window);
			this->terminate = true;
		}


		this->mouseEvent((sf::Vector2f)sf::Mouse::getPosition(window), window);
		window.clear();
		window.draw(sprite);
		this->draw(window);
		window.display();
	}

	listener.stopListening();
	std::cout << "Waiting for listener to stop" << std::endl;
	listenerThread.join();
	std::cout << "Listener terminated" << std::endl;
}