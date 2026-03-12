/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 23:46:34 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"   // definition of the Client class
#include <sys/types.h>  // socket related types (socklen_t, size_t, etc)
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <poll.h>       // poll() and struct pollfd
#include <netinet/in.h> // struct sockaddr_in
#include <string>       // std::string
#include <vector>       // std::vector
#include <map>          // std::map
#include <signal.h>

extern volatile sig_atomic_t gSignalStatus;

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
	void	setNonBlocking(int fd);
	void	configureSocket(void);
	void	setSocketOptions(void);
	void	bindSocket(void);
	void	listenSocket(void);
	
	void	acceptClient(void);
	void	handleClientData(int fd);
	void	removeClient(int fd);

	void	processBuffer(Client & client);

public:
	Server(int port, const std::string& pass);
	~Server(void);

	void	initServer();
	void	runServer();
	void	shutdownServer(void);
	void	sendMsg(int cliendFd, const std::string & msg);
	void	broadcast(const std::string &msg, int excludeFd = -1);
	
	const std::string			&getPass(void) const;
	const std::map<int, Client>	&getClients(void) const;
};

void printMyMsg(const std::string &color, const std::string &module, const std::string &type,
				const std::string &msg, int fd, const std::string &value = "");

void	signalHandler(int signal);
void	handleCmd(Server & server ,Client & client, std::string & line);
void	cmdPass(Server & server, Client & client, std::vector<std::string> & tokens);
void	cmdNick(Server & server, Client & client, std::vector<std::string> & tokens);

#endif

