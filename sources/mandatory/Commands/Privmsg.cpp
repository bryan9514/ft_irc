/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:04:27 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/03 17:05:54 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "IrcCodes.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <string>

/* PRIVMSG nick Hola
   PRIVMSG nick :Hola como estas
   PRIVMSG   #canal  :Hola a todos 
   token[0] token[1]  token[2]*/

static bool	checkTokens(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (!client.getRegistered()) {
		printMyMsg(ERROR, "PRIVMSG", "Error", "client not registered", client.getFdClient());
		return (false);
	}
	if (tokens.size() < 2) {
		controlErrors(server, client, ERR_NORECIPIENT);
		printMyMsg(ERROR, "PRIVMSG", "Error", "no recipient", client.getFdClient());
		return (false);
	}
	if (tokens.size() < 3) {
		controlErrors(server, client, ERR_NOTEXTTOSEND);
		printMyMsg(ERROR, "PRIVMSG", "Error", "no text to send", client.getFdClient());
		return (false);
	}
	return (true);
}

static void isChannelMsg(Server & server, Client & client, std::string & target, std::string & message)
{
	Channel *chan = server.getChannel(target);

	if (!chan) {
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "", target);
		printMyMsg(ERROR, "PRIVMSG", "Error", "channel not found", client.getFdClient(), target);
		return ;
	}
	if (!chan->isMember(&client)) {
		controlErrors(server, client, ERR_CANNOTSENDTOCHAN, "", target);
		printMyMsg(ERROR, "PRIVMSG", "Error", "not in channel", client.getFdClient(), target);
		return ;
	}
	std::string msg = ":" + client.getNickName() + "!" + client.getUserName() + 
			"@localhost PRIVMSG " + target + " :" + message + "\r\n";
	chan->broadcastToMembers(server, msg);
}

static Client *findClientByNick(Server &server, const std::string &nick)
{
	const std::map<int, Client> &clients = server.getClients();
	for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickName() == nick)
			return (const_cast<Client *>(&it->second));
	}
	return (NULL);
}

static void isUserMsg(Server & server, Client & client, std::string & target, std::string & message)
{
	Client *targetClient = findClientByNick(server, target);

	if (!targetClient) {
		controlErrors(server, client, ERR_NOSUCHNICK, "", target);
		printMyMsg(ERROR, "PRIVMSG", "Error", "nick not found", client.getFdClient(), target);
		return ;
	}
	std::string msg = ":" + client.getNickName() + "!" + client.getUserName()
			+ "@localhost PRIVMSG " + target + " :" + message + "\r\n";
	server.sendToClient(*targetClient, msg);
}

void	cmdPrivMsg(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (!checkTokens(server, client, tokens))
		return ;
	std::string target = tokens[1];
	std::string message = tokens[2];
	if (target[0] == '#')
		isChannelMsg(server, client, target, message);
	else
		isUserMsg(server, client, target, message);
}
