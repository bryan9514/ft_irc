/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IrcCodes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 23:22:26 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 23:23:26 by brturcio         ###   ########.fr       */
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

enum NickError
{
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433
};

#endif
