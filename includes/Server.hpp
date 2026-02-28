/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/02/28 22:16:57 by brturcio         ###   ########.fr       */
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
	std::vector<Client>		_clients;
	std::vector<pollfd>		_pollFds;

public:
	Server(int port, const std::string& pass);
	~Server(void);

	void    createSocket();   // call socket()
	void    bindSocket();     // call a bind()
	void    listenSocket();   // call a listen()
	int     acceptClient();   // call a accept(), return fd del cliente
	void    receiveData(int client_fd);
	void    sendData(int client_fd, const std::string& msg);
};

#endif

