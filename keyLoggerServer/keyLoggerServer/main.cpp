#include "server.hpp"
int main(int argc, char* argv[])
{
	Server server(sf::IpAddress::LocalHost, 1337);

	server.start();
}