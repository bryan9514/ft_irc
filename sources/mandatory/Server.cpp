/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/16 11:25:35 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
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

const std::string	&Server::getPass(void) const
{
	return (_pass);
}

const std::map<int, Client>	&Server::getClients(void) const
{
	return (_clients);
}

Client	&Server::getClient(int fd)
{
	return (_clients[fd]);
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

void	Server::sendToClient(Client & client, const std::string & msg)
{
	client.appendOutBuffer(msg);

	for (size_t i = 0; i < _pollFds.size(); i++)
	{
		if (_pollFds[i].fd == client.getFdClient())
		{
			_pollFds[i].events |= POLLOUT;
			break;
		}
	}
}

void Server::broadcast(const std::string &msg, int excludeFd)
{
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first != excludeFd)
			sendToClient(it->second, msg);
	}
}

void	Server::checkRegistration(Client & client)
{
	if (!client.getRegistered() && client.getPassOk() && client.getHasNick() && client.getHasUser())
	{
		client.setRegistered(true);

		std::string nick = client.getNickName();
		printMyMsg(SUCCESS, "REGISTER", "Success", "client registered", client.getFdClient(), nick);
    controlRPL(server, client, RPL_WELCOME)
		sendToClient(client, msg);
	}
}

//=========================getterChannel

Channel*  Server::getChannel(const std::string &name)
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it++)
    {
        if (it->first == name)
            return (it->second);
    }
    return (NULL);
}
