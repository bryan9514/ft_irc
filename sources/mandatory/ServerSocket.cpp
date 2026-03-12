/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:54:43 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 23:24:53 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"   // definition of the Server class
#include "IrcCodes.hpp" // definition of colors
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <fcntl.h>      // fcntl() to configure the socket (e.g., O_NONBLOCK)
#include <unistd.h>     // close()
#include <stdexcept>    // std::runtime_error for throwing exceptions
#include <iostream>     // std::cout / std::cerr
#include <cstring>     // memset()

/* ======================= socket non-blocking ======================= */
/*
** set a file descriptor to non-blocking mode.
**
** - fcntl(): modifies the file descriptor flags
** - O_NONBLOCK: ensures I/O operations do not block the server
** - required so poll() can manage multiple clients simultaneously
*/
void Server::setNonBlocking(int fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error: fcntl failed");
}

/* ======================= socket creation ======================= */
/*
** create the main TCP socket used by the IRC server.
**
** - socket(): creates an IPv4 TCP socket
** - if creation fails, throw an exception
** - the socket is then configured as non-blocking using setNonBlocking()
*/
void	Server::createSocket(void)
{
	_serSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serSocketFd == -1)
		throw std::runtime_error("Error: socket creation failed");
	std::cout << SUCCESS << "[SERVER] socket created" << RST << std::endl;
	setNonBlocking(_serSocketFd);
}

/* ======================= socket configuration ======================= */
/*
** configure the server address structure used by bind().
**
** - reset the structure to avoid garbage values
** - AF_INET: use IPv4 protocol family
** - htons(_port): convert the port to network byte order
** - INADDR_ANY: allow the server to accept connections from any interface
*/
void	Server::configureSocket(void)
{
	memset(&_socketAddress, 0, sizeof(_socketAddress));

	_socketAddress.sin_family = AF_INET; 
	_socketAddress.sin_port = htons(_port);
	_socketAddress.sin_addr.s_addr = INADDR_ANY;
}

/* ======================= socket options ======================= */
/*
** configure options for the server socket.
**
** - setsockopt(): modifies socket behavior
** - SO_REUSEADDR: allows the server to reuse the port immediately
**   without waiting for the TIME_WAIT state after a restart
*/
void	Server::setSocketOptions(void)
{
	int yes = 1;

	if (setsockopt(_serSocketFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		throw std::runtime_error("Error: setsockopt failed");
}

/* ======================= socket binding ======================= */
/*
** bind the server socket to the configured address and port.
**
** - bind(): associates the socket with _socketAddress
** - after this step the socket is attached to the chosen port
*/
void	Server::bindSocket(void)
{
	if (bind(_serSocketFd, (struct sockaddr *)&_socketAddress, sizeof(_socketAddress)) != 0)
		throw std::runtime_error("Error: socket bind failed");
	std::cout << SUCCESS << "[SERVER] socket successfully bound" << RST << std::endl;
}

/* ======================= socket listening ======================= */
/*
** start listening for incoming client connections.
**
** - listen(): marks the socket as a passive socket
** - SOMAXCONN: maximum number of queued connections
** - the server socket is added to the poll list so poll()
**   can detect new incoming connections
*/
void	Server::listenSocket(void)
{
	struct	pollfd	newPoll;

	if (listen(_serSocketFd, SOMAXCONN) != 0)
		throw std::runtime_error("Error: listen failed");
	std::cout << INFO << "[SERVER] listening on SERV_PORT: " << _port << RST << std::endl;
	newPoll.fd = _serSocketFd;
	newPoll.events = POLLIN;
	newPoll.revents = 0;
	_pollFds.push_back(newPoll);
}

/* ======================= server initialization ======================= */
/*
** initialize the IRC server socket.
**
** steps:
** 1. create the socket
** 2. configure the server address
** 3. set socket options
** 4. bind the socket to the address and port
** 5. start listening for client connections
*/
void	Server::initServer(void)
{
	createSocket();
	configureSocket();
	setSocketOptions();
	bindSocket();
	listenSocket();
}
