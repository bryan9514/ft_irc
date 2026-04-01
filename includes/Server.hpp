/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 21:42:08 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"   // definition of the Client class
#include "IrcCodes.hpp"
#include <sys/types.h>  // socket related types (socklen_t, size_t, etc)
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <poll.h>       // poll() and struct pollfd
#include <netinet/in.h> // struct sockaddr_in
#include <string>       // std::string
#include <vector>       // std::vector
#include <map>          // std::map
#include <signal.h>
#include <sstream>

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
	std::map<std::string, Channel*>  _channels;

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
	void	sendToClient(Client & client, const std::string & msg);
	void	broadcast(const std::string &msg, int excludeFd = -1);
	void	checkRegistration(Client & client);
	
	const std::string					&getPass(void) const;
	const std::map<int, Client>			&getClients(void) const;
	Client						        &getClient(int fd);
	Channel*							getChannel(const std::string &name);
  //Channel*  createChannel(const std::string &name, Client *client); sera necessaire
};

void printMyMsg(const std::string & color, const std::string & cmd, const std::string & type,
				const std::string & msg, int fd, const std::string & value = "");
void controlErrors(Server & server, Client & client, CmdsError code,
			   const std::string & cmd = "", const std::string & param = "");

void	signalHandler(int signal);
void	handleCmd(Server & server ,Client & client, std::string & line);
void	cmdPass(Server & server, Client & client, std::vector<std::string> & tokens);
void	cmdNick(Server & server, Client & client, std::vector<std::string> & tokens);
void	cmdUser(Server & server, Client & client, std::vector<std::string> & tokens);
void  cmdMode(Server &server, Client &client, std::vector<std::string> &tokens);

#endif

