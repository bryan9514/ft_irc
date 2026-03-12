/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 00:00:43 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include <string>

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

const std::string	&Server::getPass(void) const
{
	return (_pass);
}

const std::map<int, Client>	&Server::getClients(void) const
{
	return (_clients);
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
		handleCmd(*this, client, line);
	}
}

void	Server::sendMsg(int clientFd, const std::string & msg)
{
	send(clientFd, msg.c_str(), msg.size(), 0);
}

void Server::broadcast(const std::string &msg, int excludeFd)
{
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second.getFdClient() != excludeFd)
			sendMsg(it->second.getFdClient(), msg);
	}
}
