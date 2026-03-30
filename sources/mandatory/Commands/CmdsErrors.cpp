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
    case ERR_NOSUCHNICK:
      msg = ":ircserv 401 " + nick + " " + param + " :No such nick\r\n";
      break;
    case ERR_NOSUCHCHANNEL:
      msg = ":ircserv 403 " + nick + " " + param + " :No such channel\r\n";
      break;
		case ERR_NONICKNAMEGIVEN:
			msg = ":ircserv 431 * :No nickname given\r\n";
			break;
		case ERR_ERRONEUSNICKNAME:
			msg = ":ircserv 432 " + nick + " " + param + " :Erroneous nickname\r\n";
			break;
		case ERR_NICKNAMEINUSE:
			msg = ":ircserv 433 " + nick + " " + param + " :Nickname is already in use\r\n";
			break;
    case ERR_USERNOTINCHANNEL:
      msg = ":ircserv 441 " + nick + " " + param + " :They aren't on that channel\r\n";
      break;
    case ERR_NOTONCHANNEL:
      msg = ":ircserv 442 " + nick + " " + param + " :You're not on that channel\r\n";
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
    case ERR_KEYSET:
      msg = ":ircserv 467 " + nick + " " + param + " :Channel key already set\r\n";
      break;
    case ERR_CHANNELISFULL:
      msg = ":ircserv 471 " + nick + " " + param + " :Cannot join channel (+l)\r\n";
      break;
    case ERR_UNKNOWNMODE:
      msg = ":ircserv 472 " + nick + " " + param + " :is unknown mode char to me\r\n";
      break;
    case ERR_CHANOPRIVSNEEDED:
      msg = ":ircserv 482 " + nick + " " + param + " :You're not channel operator\r\n";
      break;
		default:
			return ;
	}
	if (!msg.empty())
	    server.sendToClient(client, msg);
}

void controlRPL(Server & server, Client & client, CmdsRPL code,
			   const std::string & cmd, const std::string & param)
{
	std::string nick = client.getNickName();
	if (nick.empty())
		nick = "*";
	std::string msg;
	switch (code) {
    case RPL_WELCOME:
      msg = ":ircserv 001 " + nick + " :Welcome to the ircserv Network " + nick + "!" + client.getUserName() + "@localhost\r\n";
      break;
    case RPL_CHANNELMODEIS:
      msg = ":ircserv 324 " + nick + " " + cmd + " " + param + "\r\n";
      break;
    case RPL_NOTOPIC:
      msg = ":ircserv 331 " + nick + " " + param + " :No topic is set\r\n";
      break;
    case RPL_TOPIC:
      msg = ":ircserv 332 " + nick + " " + cmd + " :" + param + "\r\n";
      break;
    case RPL_ENDOFNAMES:
      msg = ":ircserv 366 " + nick + " " + cmd + " :End of /NAME list\r\n";
      break;
    case RPL_INVITING:
      msg = ":ircserv 341 " + nick + " " + cmd + " " + param + "\r\n";
      break;
	default:
	  return ;
	}
	if (!msg.empty())
	    server.sendToClient(client, msg);
}
