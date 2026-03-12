/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 12:10:38 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 00:06:32 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "IrcCodes.hpp"

static void	controlErrors(Server & server, Client & client, const std::vector<std::string> & tokens, NickError code)
{
	std::string msg;

	if (code == ERR_NONICKNAMEGIVEN) {
		printMyMsg(ERROR, "NICK", "Error", "missing nickname", client.getFdClient());
		msg = ":server 431 * :No nickname given\r\n";
	}
	else if (code == ERR_ERRONEUSNICKNAME) {
		printMyMsg(ERROR, "NICK", "Error", "invalid nickname", client.getFdClient(), tokens[1]);
		msg = ":server 432 " + tokens[1] + " :Erroneous nickname\r\n";
	}
	else if (code == ERR_NICKNAMEINUSE) {
		printMyMsg(ERROR, "NICK", "Error", "nickname already in use", client.getFdClient(), tokens[1]);
		msg = ":server 433 " + tokens[1] + " :Nickname is already in use\r\n";
	}
	server.sendMsg(client.getFdClient(), msg);
}

static bool	isValidNick(const std::string & nick)
{
	if (nick.empty())
		return false;
	if (nick[0] == '#' || nick[0] == '&' || nick[0] == '+' || nick[0] == '!' || !std::isalpha(nick[0]))
		return (false);
	for (size_t i = 1; i < nick.length(); i++) {
		if (nick[i] == ' ' || nick[i] == ':' || nick[i] == '@' || nick[i] == '#' || nick[i] == '!')
			return (false);
	}
	return (true);
}

static void	checkOldNick(Server & server, Client & client, const std::string & newNick)
{
	if (client.getHasNick()) {
		std::string	oldNick = client.getNickName();
		std::string	msg = ":" + oldNick + " NICK " + newNick + "\r\n";
		
		server.broadcast(msg, client.getFdClient());
	}
	client.setNickName(newNick);
	client.setHasNick(true);
}

void	cmdNick(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (!client.getPassOk())
		return;
	
	const std::map<int, Client> &mapClients = server.getClients();
	if (tokens.size() < 2) {
		controlErrors(server, client, tokens, ERR_NONICKNAMEGIVEN);
		return ;
	}
	if (!isValidNick(tokens[1])) {
		controlErrors(server, client, tokens, ERR_ERRONEUSNICKNAME);
		return ;
	}
	for (std::map<int, Client>::const_iterator it = mapClients.begin(); it != mapClients.end(); ++it) {
		if (it->second.getFdClient() != client.getFdClient() &&  it->second.getNickName() == tokens[1]) {
			controlErrors(server, client, tokens, ERR_NICKNAMEINUSE);
			return ;
		}
	}
	checkOldNick(server, client, tokens[1]);
	printMyMsg(SUCCESS, "NICK", "Success", "nickname set", client.getFdClient(), tokens[1]);
}
