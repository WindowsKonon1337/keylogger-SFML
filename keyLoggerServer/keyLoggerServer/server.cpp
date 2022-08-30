#include "server.hpp"

Server::Server(const sf::IpAddress& addr, const int& port) : port(port), currentIP(addr)
{
	file.open("./logs.txt", std::ios::app);
	listener.listen(port, addr);
}

void Server::start()
{
	std::thread connectThread(&Server::connectClients, this, std::ref(clients));

	clientManager();
}

void Server::connectClients(std::list<TYPE>& clients)
{
	while (true)
	{
		auto client = std::make_shared<sf::TcpSocket>();
		if (listener.accept(*client) == sf::Socket::Status::Done)
		{
			client->setBlocking(false);
			clients.push_back(client);
		}
	}
}

void Server::disconnectClients(std::stack<std::list<TYPE>::iterator>& trashbox)
{
	for (int i = 0; i < trashbox.size(); ++i)
	{
		(*trashbox.top())->disconnect();
		clients.erase(trashbox.top());
		trashbox.pop();
	}
}

void Server::clientManager()
{
	while (true)
	{
		for (auto it = clients.begin(); it != clients.end(); ++it)
		{
			clientController(it);
		}
		disconnectClients(trashbox);
	}
}

void Server::clientController(std::list<TYPE>::iterator& client)
{
	sf::Packet data;
	if ((*client)->receive(data) == sf::Socket::Status::Disconnected)
	{
		trashbox.push(client);
		return;
	}

	if (data.getDataSize() > 0)
	{
		save(data, file);
	}
}

void Server::save(sf::Packet& data, std::ofstream& file)
{
	std::string str;

	while (!data.endOfPacket())
	{
		data >> str;
		file << str;
	}
	data.clear();
}