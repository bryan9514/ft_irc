/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdsErrors.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:29:18 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 23:27:34 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "IrcCodes.hpp"
#include <iostream>
#include <string>

void	printMyMsg(const std::string & color, const std::string & cmd, const std::string & type,
				const std::string & msg, int fd, const std::string & value)
{
	std::cout << color << "[" << cmd << "] " << type << ": " << msg << " (fd: " << fd << ")";
	if (!value.empty())
		std::cout << " : " << value;
	std::cout << RST << std::endl;
}

void controlErrors(Server & server, Client & client, CmdsError code,
			   const std::string & cmd, const std::string & param)
{
	std::string nick = client.getNickName();
	if (nick.empty())
		nick = "*";
	std::string msg;
	switch (code) {
		case ERR_NONICKNAMEGIVEN:
			msg = ":ircserv 431 * :No nickname given\r\n";
			break;
		case ERR_ERRONEUSNICKNAME:
			msg = ":ircserv 432 " + nick + " " + param + " :Erroneous nickname\r\n";
			break;
		case ERR_NICKNAMEINUSE:
			msg = ":ircserv 433 " + nick + " " + param + " :Nickname is already in use\r\n";
			break;
		case ERR_NEEDMOREPARAMS:
			msg = ":ircserv 461 " + nick + " " + cmd + " :Not enough parameters\r\n";
			break;
		case ERR_ALREADYREGISTERED:
			msg = ":ircserv 462 " + nick + " :You may not reregister\r\n";
			break;
		case ERR_PASSWDMISMATCH:
			msg = ":ircserv 464 " + nick + " :Password incorrect\r\n";
			break;
		default:
			return ;
	}
	if (!msg.empty())
	    server.sendToClient(client, msg);
}
