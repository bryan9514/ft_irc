/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 01:14:08 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <string>
#include <iostream>


/* ======================== parameter constructor =========================== */
Server::Server(int port, const std::string& pass) :
	_port(port),
	_serSocketFd(-1),
	_pass(pass),
	_clients(),
	_pollFds()
{}

/* ================================ destructor ============================== */
Server::~Server(void)
{}

std::string	Server::getPass(void) const
{
	return (_pass);
}


/* ============================== member functions ========================== */
void Server::shutdownServer(void)
{
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		close(it->first);
	_clients.clear();
	_pollFds.clear();
	if (_serSocketFd != -1) {
		close(_serSocketFd);
		_serSocketFd = -1;
	}
}


void	Server::processBuffer(Client & client)
{
	std::string	&buffer = client.getBuffer();
	size_t		pos;

	while ((pos = buffer.find("\r\n")) != std::string::npos)
	{
		std::string	line = buffer.substr(0, pos);
		buffer.erase(0, pos + 2);
		//std::cout << "[CMD] " << line << std::endl;
		handleCmd(*this, client, line);
	}
}
