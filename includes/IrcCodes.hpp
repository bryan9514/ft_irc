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
    ERR_PASSWDMISMATCH = 464
    // Returned when the password provided with the PASS command is incorrect.
};

#endif
