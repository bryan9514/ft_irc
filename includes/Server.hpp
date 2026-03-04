/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/04 10:41:40 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

/* For sorcket, bind, listen,   */
#include <sys/types.h>
#include <sys/socket.h>

/* For poll */
#include <poll.h>

/* For struct sockaddr_in */
#include <netinet/in.h>

/* For containers */
#include <string>
#include <vector>
#include <map>

class Client;

class Server
{
private:
	int						_port;
	int						_serSocketFd;
	std::string				_pass;
	std::map<int, Client>	_clients;
	std::vector<pollfd>		_pollFds;
	struct sockaddr_in 		_socketAddress;

	void	createSocket(void);
	void	configureSocket(void);
	void	setSocketOptions(void);
	void	bindSocket(void);
	void	listenSocket(void);
	
	void	acceptClient(void);
	void	handleClientData(int fd);
	void	removeClient(int fd);

public:
	Server(int port, const std::string& pass);
	~Server(void);

	void	initServer();
	void	runServer();

};

#endif

