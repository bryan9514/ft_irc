/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/03 17:50:16 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ft_irc.hpp"
/* for exception runtime_error */
#include <stdexcept>
#include <sys/poll.h>
#include <sys/socket.h>
/* for fcntl */
#include <fcntl.h>
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
	_serSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serSocketFd == -1)
		throw std::runtime_error("Error: socket creation failed");
	std::cout << SUCCESS <<"[SERVER] socket successfuly created" << RST << std::endl;
}

void	Server::configureSocket(void)
{
	_socketAddress.sin_family = AF_INET;
	_socketAddress.sin_port = htons(_port);;
	_socketAddress.sin_addr.s_addr = INADDR_ANY;
}

void	Server::setSocketOptions(void)
{
    int yes = 1;
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
	if (listen(_serSocketFd, SOMAXCONN) != 0)
		throw std::runtime_error("Error: listen failed");
	std::cout << SUCCESS << "[SERVER] listening on SERV_PORT: " << _port << RST << std::endl;
}

/* ==================== private methods for runServer ======================= */
void	Server::pollFds(void)
{
	
}

void	Server::acceptClient(void)
{

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
	pollFds();
	while (1) {
		if((poll(&_pollFds[0],_pollFds.size(),-1) == -1) != 0)
			throw std::runtime_error("Error: poll failed");
		for (size_t i = 0; i < _pollFds.size(); i++)
			if (_pollFds[i].revents & POLLIN) {
				if (_pollFds[i].fd == _serSocketFd)
					acceptClient();
				else
					handleClientData();
			}
	}
}
