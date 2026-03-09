/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/09 19:16:31 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ft_irc.hpp"
#include "Client.hpp"
/* for exception runtime_error */
#include <cerrno>
#include <stdexcept>
#include <sys/poll.h>
#include <sys/socket.h>
/* for fcntl */
#include <fcntl.h>
/* for close */
#include <unistd.h>
#include <iostream>

/* ======================== parameter constructor =========================== */
Server::Server(int port, const std::string& pass) :
	_port(port),
	_serSocketFd(-1),
	_pass(pass),
	//_clients(),
	_pollFds()
{}

/* ================================ destructor ============================== */
Server::~Server(void)
{}

/* ================== private methods for createSocket ====================== */
void	Server::createSocket(void)
{
	_serSocketFd = socket(AF_INET, SOCK_STREAM, 0); //socket creation
	if (_serSocketFd == -1)
		throw std::runtime_error("Error: socket creation failed");
	std::cout << SUCCESS <<"[SERVER] socket successfuly created" << RST << std::endl;
	if (fcntl(_serSocketFd, F_SETFL, O_NONBLOCK) == -1) // put it in non-blocking
		throw std::runtime_error("Error: fcntl failed");
}

void	Server::configureSocket(void)
{
	// Configure the server address:
	_socketAddress.sin_family = AF_INET; 
	_socketAddress.sin_port = htons(_port);;
	_socketAddress.sin_addr.s_addr = INADDR_ANY;
}

void	Server::setSocketOptions(void)
{
    int yes = 1;
    // to use the port, without having to wait for TIME_WAIT
    if (setsockopt(_serSocketFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
        throw std::runtime_error("Error: setsockopt failed");
}

void	Server::bindSocket(void)
{
	if (bind(_serSocketFd, (struct sockaddr *)&_socketAddress, sizeof(_socketAddress)) != 0)
		throw std::runtime_error("Error: socket bind failed");
	std::cout << SUCCESS << "[SERVER] socket successfuly binded" << RST << std::endl;
}

void	Server::listenSocket(void)
{
	struct	pollfd	newPoll;

	if (listen(_serSocketFd, SOMAXCONN) != 0)
		throw std::runtime_error("Error: listen failed");
	std::cout << SUCCESS << "[SERVER] listening on SERV_PORT: " << _port << RST << std::endl;
	newPoll.fd = _serSocketFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;
	_pollFds.push_back(newPoll);
}

/* ==================== private methods for runServer ======================= */
void	Server::acceptClient(void)
{
	while (true)
	{
		struct sockaddr_in	clientAddress;
		socklen_t			lenClientAddress = sizeof(clientAddress);
		Client					newClient;

		int acceptFd = accept(_serSocketFd, (sockaddr*)&(clientAddress), &lenClientAddress);
		if (acceptFd == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break ;
			throw std::runtime_error("Error: accept failed");
		}
		if (fcntl(acceptFd, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("Error: fcntl failed");
		struct pollfd newPoll;
		newPoll.fd = acceptFd;
		newPoll.events = POLLIN;
		newPoll.revents = 0;
		_pollFds.push_back(newPoll); // add the Poll inside the map container
		newClient.setFdClient(acceptFd);
		_clients.insert(std::pair<int, Client>(acceptFd, newClient));
		std::cout << SUCCESS << "[SERVER] New client connected (fd: " << acceptFd << ")" << RST << std::endl;
	}
}

void Server::removeClient(int fd)
{
	close(fd);

	_clients.erase(fd);
	for (size_t i = 0; i < _pollFds.size(); i++) {
		if (_pollFds[i].fd == fd) {
			_pollFds.erase(_pollFds.begin() + i);
			break;
		}
	}
	std::cout << INFO << "[SERVER] client disconnected fd: " << fd << RST << std::endl;
}

void Server::handleClientData(int fd)
{
	char buffer[512];
	int bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
	
	if (bytes <= 0) {
		removeClient(fd);
		return ;
	}
	//_clients[fd].buffer += message; me falta meter el mensaje completo en el buffer del cliente
	buffer[bytes] = '\0';
	std::string message(buffer);
	std::cout << INFO << "[CLIENT " << fd << "] " << message << RST << std::endl;
}

/* ============================ public methods ============================== */
void	Server::initServer(void)
{
	createSocket();
	configureSocket();
	setSocketOptions();
	bindSocket();
	listenSocket();
}

void	Server::runServer(void)
{
	std::cout << SUCCESS << "[SERVER] Waiting to accept a connection..." << RST << std::endl;

	while (1) {
		if(poll(&_pollFds[0],_pollFds.size(),-1) == -1)
			throw std::runtime_error("Error: poll failed");
		for (size_t i = 0; i < _pollFds.size(); i++)
			if (_pollFds[i].revents & POLLIN) {
				if (_pollFds[i].fd == _serSocketFd)
					acceptClient();
				else
					handleClientData(_pollFds[i].fd);
			}
	}
}
