/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/02/28 18:56:47 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <string>
#include <poll.h>
#include <vector>

class Server
{
private:
	int						_port;
	int						_serSocketFd;
	std::string				_pass;
	std::vector<pollfd>		_pollFds;

public:
	Server(int port, const std::string& pass);
	~Server(void);

	
};

#endif

