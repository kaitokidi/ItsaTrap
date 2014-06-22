#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include <SFML/Network.hpp>

class Socket{

public:

	Socket(char s);
	bool connect();
	bool send(char data[], size_t size, int p);
	bool recieve(char data[], size_t size, int p );

private:

	int port;
	bool is_server;
	sf::TcpSocket socket;
	sf::TcpSocket client;
	sf::TcpListener listener;
};

#endif // _SOCKET_HPP_
