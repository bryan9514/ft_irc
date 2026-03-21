/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCodes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:22:26 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 21:15:11 by brturcio         ###   ########.fr       */
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

enum CmdsError
{
    ERR_NOSUCHCHANNEL = 403,
    // Returned when the channel cannot be found with the supplied channel name.
    ERR_NONICKNAMEGIVEN = 431,
    // Returned when the NICK command is sent without a nickname parameter.
    ERR_ERRONEUSNICKNAME = 432,
    // Returned when the nickname has an invalid format or contains forbidden characters.
    ERR_NICKNAMEINUSE = 433,
    // Returned when the requested nickname is already used by another client.
    ERR_NEEDMOREPARAMS = 461,
    // Returned when a command is missing required parameters.
    ERR_ALREADYREGISTERED = 462,
    // Returned when a client tries to register again after completing registration.
    ERR_PASSWDMISMATCH = 464,
    // Returned when the password provided with the PASS command is incorrect.
    ERR_KEYSET = 467,
    // Returned when the key for the mode is already set.
    ERR_CHANNELISFULL = 471,
    // Returned when channel is full (from mode 'l').
    ERR_UNKNOWNMODE = 472,
    // Returned when the mode is unknown.
    ERR_CHANOPRIVSNEEDED = 482,
    // Returned when an not Operator client try using MODE.
};

enum CmdsRPL
{
    RPL_WELCOME = 001,
    // Retruned when a client succesfuly register.
    RPL_CHANNELMODEIS = 324,
    // Returned when 'MODE #chan' is typed and tell the mode present in the channel.
    RPL_NOTOPIC = 331,
    // Returned when `TOPIC #chan` is typed and tell if the topic is undefined.
    RPL_TOPIC = 332,
    // Returned when `TOPIC #chan` is typed and tell if the topic is defined.
    RPL_NAMEREPLY = 353,
    // Returned after using `JOIN` and tell the list of the members of the channel.
    RPL_ENDOFNAMES = 366,
    // Returned when its the end of the list of the members.
    RPL_INVITING = 341,
    // Returned when `INVITE` is confirmed.
};


#endif
