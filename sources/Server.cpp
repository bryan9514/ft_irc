/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:08 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/04 14:51:22 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
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
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		delete it->second;
	_channels.clear();
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
		if (client.getToDelete())
			break;
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

void    Server::checkRegistration(Client & client)
{
    if (!client.getRegistered() && client.getPassOk() && client.getHasNick() && client.getHasUser())
    {
        client.setRegistered(true);

        std::string nick = client.getNickName();
        std::string msg = ":ircserv 001 " + nick + " :Welcome to the ircserv Network " + nick + "!" + client.getUserName() + "@localhost\r\n";
        printMyMsg(SUCCESS, "REGISTER", "Success", "client registered", client.getFdClient(), nick);
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

bool Server::hasChannel(const std::string &name) const
{
	for (std::map<std::string, Channel*>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (it->first == name)
			return (true);
	}
	return (false);
}

Channel*  Server::createChannel(const std::string &name, Client *client)
{
	if (hasChannel(name))
		return (getChannel(name));
	Channel *newChannel = new Channel(name);
	newChannel->addMember(client);
	_channels[name] = newChannel;
	return (newChannel);
}

void Server::disconnectClient(Client &client, const std::string &reason)
{
	std::string msg = ":" + client.getNickName() + "!" + client.getUserName() +
				"@localhost QUIT :" + reason + "\r\n";
	for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		Channel *chan = it->second;
		if (chan->isMember(&client)) {
			chan->broadcastToMembersExcept(*this, msg, client.getFdClient());
			chan->removeNormalMember(&client);
			chan->removeMember(&client);
		}
	}
	removeClient(client.getFdClient());
}
