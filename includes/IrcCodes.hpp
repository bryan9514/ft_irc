/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCodes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:22:26 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/02 20:20:52 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_CODES_HPP
#define IRC_CODES_HPP

# define RST "\033[0m"
# define ERROR "\033[0;91m"
# define WARNING "\033[0;93m"
# define SUCCESS "\033[0;92m"
# define INFO "\033[0;96m"
# define INP "\033[0;94m"

# define RPL_JOIN(client, channel) (":" + (client) + " JOIN :" + (channel) + "\r\n")
# define RPL_WELCOME(client, nick, user) (":" + (client) + " 001 " + (nick) + " :Welcome to the ircserv Network " + (nick) + "!" + (user) + "@localhost\r\n")
# define RPL_CHANNELMODEIS(client, channel, modes) (":" + (client) + " 324 " + (client) + " " + (channel) + " " + (modes) + "\r\n")
# define RPL_NOTOPIC(client, channel) (":" + (client) + " 331 " + (client) + " " + (channel) + " :No topic is set\r\n")
# define RPL_TOPIC(client, channel, topic) (":" + (client) + " 332 " + (client) + " " + (channel) + " :" + (topic) + "\r\n")
# define RPL_NAMEREPLY(client, symbol, channel, members) (":" + (client) + " 353 " + (client) + " " + (symbol) + " " + (channel) + " :" + (members) + "\r\n")
# define RPL_ENDOFNAMES(client, channel) (":" + (client) + " 366 " + (channel) + " :End of /NAME list\r\n")
# define RPL_INVITING(client, channel, target) (":" + (client) + " 341 " + (client) + " " + (channel) + " " + (target) + "\r\n")
# define RPL_INVITELIST(client, channel) (":" + (client) + " 336 " + (client) + " " + (channel) + "\r\n")
# define RPL_ENDOFINVITELIST(client) (":" + (client) + " 337 " + (client) + " :End of /INVITE list\r\n")
# define RPL_TOPICWHOTIME(client, channel, setter, time) (":" + (client) + " 333 " + (client) + " " + (channel) + " " + (setter) + " " + (time) + "\r\n")

# define ERR_NOSUCHNICK(client, target) (":" + (client) + " 401 " + (client) + " " + (target) + " :No such nick\r\n")
# define ERR_NOSUCHCHANNEL(client, channel) (":" + (client) + " 403 " + (client) + " " + (channel) + " :No such channel\r\n")
# define ERR_NONICKNAMEGIVEN(client) (":" + (client) + " 431 * :No nickname given\r\n")
# define ERR_ERRONEUSNICKNAME(client, nick) (":" + (client) + " 432 " + (client) + " " + (nick) + " :Erroneous nickname\r\n")
# define ERR_NICKNAMEINUSE(client, nick) (":" + (client) + " 433 " + (client) + " " + (nick) + " :Nickname is already in use\r\n")
# define ERR_USERNOTINCHANNEL(client, channel) (":" + (client) + " 441 " + (client) + " " + (channel) + " :They aren't on that channel\r\n")
# define ERR_NOTONCHANNEL(client, channel) (":" + (client) + " 442 " + (client) + " " + (channel) + " :You're not on that channel\r\n")
# define ERR_USERONCHANNEL(client, command, target) (":" + (client) + " 443 " + (client) + " " + (command) + " " + (target) + " :is already on channel\r\n")
# define ERR_NEEDMOREPARAMS(client, command) (":" + (client) + " 461 " + (client) + " " + (command) + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTERED(client) (":" + (client) + " 462 " + (client) + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(client) (":" + (client) + " 464 " + (client) + " :Password incorrect\r\n")
# define ERR_KEYSET(client, channel) (":" + (client) + " 467 " + (client) + " " + (channel) + " :Channel key already set\r\n")
# define ERR_CHANNELISFULL(client, channel) (":" + (client) + " 471 " + (client) + " " + (channel) + " :Cannot join channel (+l)\r\n")
# define ERR_INVITEONLYCHAN(client, channel) (":" + (client) + " 473 " + (client) + " " + (channel) + " :Cannot join channel (+i)\r\n")
# define ERR_BADCHANNELKEY(client, channel) (":" + (client) + " 475 " + (client) + " " + (channel) + " :Cannot join channel (+k)\r\n")
# define ERR_UNKNOWNMODE(client, mode) (":" + (client) + " 472 " + (client) + " " + (mode) + " :is unknown mode char to me\r\n")
# define ERR_CHANOPRIVSNEEDED(client, channel) (":" + (client) + " 482 " + (client) + " " + (channel) + " :You're not channel operator\r\n")

enum CmdsError
{
	ERR_NOSUCHCHANNEL = 403,
	// Returned when JOIN has a non channel name as input (like "fu" -> "#fu").
    ERR_NOSUCHNICK = 401,
    // Returned when the nick cannot be found.
    ERR_NONICKNAMEGIVEN = 431,
    // Returned when the NICK command is sent without a nickname parameter.
    ERR_ERRONEUSNICKNAME = 432,
    // Returned when the nickname has an invalid format or contains forbidden characters.
    ERR_NICKNAMEINUSE = 433,
    // Returned when the requested nickname is already used by another client.
    ERR_USERNOTINCHANNEL = 441,
    // Returned when the target user is not in the specified channel.
    ERR_NOTONCHANNEL = 442,
    // Returned when the client is not on the specified channel.
	ERR_USERONCHANNEL = 443,
	// Returned when the invited user is already on the specified channel.
    ERR_NEEDMOREPARAMS = 461,
    // Returned when a command is missing required parameters.
    ERR_ALREADYREGISTERED = 462,
    // Returned when a client tries to register again after completing registration.
    ERR_PASSWDMISMATCH = 464,
    // Returned when the password provided with the PASS command is incorrect.
    ERR_KEYSET = 467,
    // Returned when the key for the mode is already set.
    ERR_CHANNELISFULL = 471,
	// Returned when the channel you want to join is full.
	ERR_INVITEONLYCHAN = 473,
	// Returned when we try to join a invite only chan without invitation.
	ERR_BADCHANNELKEY = 475,
	// Rreturned when the key don't match the channel key in JOIN command.
    ERR_UNKNOWNMODE = 472,
    // Returned when the mode is unknown.
    ERR_CHANOPRIVSNEEDED = 482,
    // Returned when an not Operator client try using MODE.
};

#endif
