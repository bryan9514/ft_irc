/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerRun.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:59:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/04 13:58:12 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"   // definition of the Server class
#include "Client.hpp"   // definition of the Client class
#include "IrcCodes.hpp" // definition of colors
#include <algorithm>
#include <cerrno>       // errno values (EAGAIN, EWOULDBLOCK, etc.)
#include <stdexcept>    // std::runtime_error for throwing exceptions
#include <sys/poll.h>   // poll() and struct pollfd
#include <sys/socket.h> // socket functions (accept, recv, send, etc.)
#include <fcntl.h>      // fcntl() to set socket as non-blocking
#include <sys/types.h>
#include <unistd.h>     // close()
#include <iostream>     // std::cout / std::cerr

/* ======================= accept new client ======================= */
/*
** accept incoming client connections and register them in the server.
**
** - accept(): retrieves pending client connections from the server socket
** - if no more clients are waiting (EAGAIN / EWOULDBLOCK), the loop stops
** - the accepted socket is configured as non-blocking using setNonBlocking()
** - a new pollfd structure is created so poll() can monitor the client
** - a Client object is created and stored in the _clients map
** - the client is identified by its file descriptor (fd)
*/
void	Server::acceptClient(void)
{
	while (true)
	{
		struct sockaddr_in	clientAddress;
		socklen_t			lenClientAddress = sizeof(clientAddress);
		Client				newClient;

		int acceptFd = accept(_serSocketFd, (sockaddr*)&(clientAddress), &lenClientAddress);
		if (acceptFd == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break ;
			throw std::runtime_error("Error: accept failed");
		}
		setNonBlocking(acceptFd);
		struct pollfd newPoll;
		newPoll.fd = acceptFd;
		newPoll.events = POLLIN;
		newPoll.revents = 0;
		_pollFds.push_back(newPoll);
		newClient.setFdClient(acceptFd);
		_clients.insert(std::pair<int, Client>(acceptFd, newClient));
		std::cout << SUCCESS << "[SERVER] New client connected (fd: " << acceptFd << ")" << RST << std::endl;
	}
}

/* ======================= remove client ======================= */
/*
** remove a client from the server and clean all related resources.
**
** - validates the file descriptor to avoid invalid operations
** - close(): terminates the socket connection with the client
** - finds the client inside the _clients map using its fd
** - erase(): removes the client from the _clients container if it exists
** - iterates through the _pollFds vector to locate the same fd
** - removes the corresponding pollfd entry so poll() stops monitoring it
**
** this ensures that the disconnected client is completely removed
** from the server and will no longer generate events in poll()
**
** used when:
** - a client closes the connection
** - recv() returns 0
** - poll() detects POLLERR, POLLHUP or POLLNVAL
*/
void Server::removeClient(int fd)
{
	if (fd < 0)
		return;
	close(fd);
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it != _clients.end())
    	_clients.erase(it);
	for (size_t i = 0; i < _pollFds.size(); i++) {
		if (_pollFds[i].fd == fd) {
			_pollFds.erase(_pollFds.begin() + i);
			break;
		}
	}
	std::cout << INFO << "[SERVER] client disconnected fd: " << fd << RST << std::endl;
}

/* ======================= handle client data ======================= */
/*
** read incoming data from a connected client socket.
**
** - recv(): reads available data from the client socket
** - received data is appended to the client's internal buffer
** - if recv() returns 0, the client has closed the connection
**   and the client is removed from the server
** - if recv() returns -1 with EAGAIN / EWOULDBLOCK, no more data
**   is available at the moment and the read loop stops
** - any other recv() error triggers a runtime exception
** - the client's buffer stores incoming IRC messages until they
**   can be parsed and processed
*/
void Server::handleClientData(int fd)
{
	char	buffer[512];
	int		bytes;

	while (true)
	{
		bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);
		if (bytes > 0) {
			std::map<int, Client>::iterator it = _clients.find(fd);
			if (it != _clients.end())
				it->second.appendBuffer(std::string(buffer, bytes));
		} else if (bytes == 0) {
			std::map<int, Client>::iterator it = _clients.find(fd);
			if (it != _clients.end())
				disconnectClient(it->second, "Quit: Connection closed");
			return ;
		} else {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
			else
				throw std::runtime_error("Error: recv failed");
		}
	}
	std::map<int, Client>::iterator it = _clients.find(fd);
	if (it != _clients.end())
	{
		processBuffer(it->second);
		if (it != _clients.end() && it->second.getToDelete())
		{
			disconnectClient(it->second, it->second.getQuitReason());
			return ;
		}
	}
}

/* ======================= server main loop ======================= */
/*
** main event loop of the IRC server using poll().
**
** - poll(): monitors all file descriptors stored in _pollFds
**   (server socket + client sockets)
** - the loop runs until a termination signal updates gSignalStatus
** - if poll() is interrupted by a signal (EINTR), the loop continues
** - if the server socket has activity, acceptClient() is called
**   to accept pending incoming connections
** - if a client socket has activity, handleClientData() reads
**   incoming data from that client
** - if a client socket reports POLLERR, POLLHUP or POLLNVAL,
**   the client is disconnected and removed from the server
** - the loop continuously processes network events without blocking
*/
void	Server::runServer(void)
{
	std::cout << INFO << "[SERVER] Waiting to accept a connection..." << RST << std::endl;
	while (!gSignalStatus)
	{
		int ret = poll(&_pollFds[0], _pollFds.size(), 1000);
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			throw std::runtime_error("Error: poll failed");
		}
		for (size_t i = 0; i < _pollFds.size(); i++) {
			int currentFd = _pollFds[i].fd;
			short currentRevents = _pollFds[i].revents;
			if (currentFd != _serSocketFd && (currentRevents & (POLLERR | POLLHUP | POLLNVAL))) {
				removeClient(currentFd);
				--i;
				continue;
			}
			if (currentRevents & POLLIN) {
				if (currentFd == _serSocketFd)
					acceptClient();
				else
					handleClientData(currentFd);
				if (currentFd != _serSocketFd) {
					if (i >= _pollFds.size() || _pollFds[i].fd != currentFd) {
						--i;
						continue;
					}
				}
			}
			if (currentRevents & POLLOUT) {
				std::map<int, Client>::iterator	it = _clients.find(currentFd);
				if (it == _clients.end()) {
					if (i < _pollFds.size() && _pollFds[i].fd == currentFd)
						_pollFds[i].revents = 0;
					continue;
				}
				std::string	&out = it->second.getOutBuffer();
				if (!out.empty())
				{
					ssize_t sent = send(currentFd, out.c_str(), out.size(), 0);
					if (sent > 0)
						out.erase(0, sent);
				}
				if (out.empty() && i < _pollFds.size() && _pollFds[i].fd == currentFd)
					_pollFds[i].events &= ~POLLOUT;
			}
			if (i < _pollFds.size() && _pollFds[i].fd == currentFd)
				_pollFds[i].revents = 0;
		}
	}
}
