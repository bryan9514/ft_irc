/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/02/28 16:27:23 by brturcio         ###   ########.fr       */
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
#include <list>

class Server
{
private:
	int							_serverFd;
	int							_port;
	std::string					_pass;
	std::vector<int>			_clients;
	std::list<struct pollfd>	_pollFds;

public:
	Server(void);
	~Server(void);
};

#endif

