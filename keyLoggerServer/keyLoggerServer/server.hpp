#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <memory>
#include <stack>

#define TYPE std::shared_ptr<sf::TcpSocket>

class Server
{
private:
	sf::TcpListener listener;

	std::list<TYPE> clients;

	std::stack<std::list<TYPE>::iterator> trashbox;

	sf::IpAddress currentIP;

	int port;

	std::ofstream file;

	std::pair<std::string, std::string> clientDifference;

	void connectClients(std::list<TYPE>& clients);

	void disconnectClients(std::stack<std::list<TYPE>::iterator>& trashbox);

	void clientManager();

	void clientController(std::list<TYPE>::iterator& client);

	void save(sf::Packet& data, std::ofstream& file);

public:
	Server() = delete;

	Server(const sf::IpAddress& addr, const int& port);

	~Server()
	{
		file.close();
	}

	void start();
};
