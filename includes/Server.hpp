/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 14:57:12 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/05 12:08:40 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Client.hpp"   // definition of the Client class
#include "Channel.hpp"
#include "IrcCodes.hpp"
#include <sys/types.h>  // socket related types (socklen_t, size_t, etc)
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send(), recv()
#include <poll.h>       // poll() and struct pollfd
#include <netinet/in.h> // struct sockaddr_in
#include <string>       // std::string
#include <vector>       // std::vector
#include <map>          // std::map
#include <signal.h>

extern volatile sig_atomic_t gSignalStatus;

class Channel;

class Server
{
	private:
		int								_port;
		int								_serSocketFd;
		std::string						_pass;
		std::map<int, Client>			_clients;
		std::vector<pollfd>				_pollFds;
		struct sockaddr_in 				_socketAddress;
		std::map<std::string, Channel*>	_channels;

		void	createSocket(void);
		void	setNonBlocking(int fd);
		void	configureSocket(void);
		void	setSocketOptions(void);
		void	bindSocket(void);
		void	listenSocket(void);
		
		void	acceptClient(void);
		void	handleClientData(int fd);

		void	processBuffer(Client & client);

	public:
		Server(int port, const std::string& pass);
		~Server(void);

		void	initServer();
		void	runServer();
		void	shutdownServer(void);
		void	sendToClient(Client & client, const std::string & msg);
		void	broadcast(const std::string &msg, int excludeFd = -1);
		void	removeClient(int fd);
		void	checkRegistration(Client & client);
		void	disconnectClient(Client &client, const std::string &reason);

		const std::string					&getPass(void) const;
		const std::map<int, Client>			&getClients(void) const;
		Client						        &getClient(int fd);
		Channel*							getChannel(const std::string &name);
		bool								hasChannel(const std::string &name) const;
		Channel*  							createChannel(const std::string &name, Client *client);
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
void	cmdJoin(Server & server, Client & client, std::vector<std::string> & tokens);
void	cmdKick(Server &server, Client &client, std::vector<std::string> &tokens);
void	cmdTopic(Server &server, Client &client, std::vector<std::string> &tokens);
void	cmdInvite(Server &server, Client &client, std::vector<std::string> &tokens);
void	cmdMode(Server &server, Client &client, std::vector<std::string> &tokens);
void	cmdPrivMsg(Server &server, Client &client, std::vector<std::string> &tokens);
void	cmdQuit(Server &server, Client &client, std::vector<std::string> &tokens);
void	cmdBot(Server &server, Client &client, std::vector<std::string> &tokens);

std::vector<std::string>	splitString(std::string s, char sep);

#endif
