/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:00:10 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/10 08:00:13 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "IrcCodes.hpp"
#include <stdlib.h>
#include <exception>
#include <iostream>
#include <cerrno>
#include <string.h>

volatile sig_atomic_t gSignalStatus = 0;
void	shutdownServer(void);

static bool isNumber(const char *str)
{
	if (!str || !*str)
		return (false);
	for (int i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
	}
	return (true);
}

static int parsePort(const char *str)
{
	char *end;
	long port;

	if (!isNumber(str))
		throw std::runtime_error("port must be numeric");
	errno = 0;
	port = std::strtol(str, &end, 10);
	if (errno != 0 || *end != '\0')
		throw std::runtime_error("invalid port");
	if (port < 1024 || port > 65535)
		throw std::runtime_error("port must be between 1024 and 65535");
	return (static_cast<int>(port));
}

static std::string parsePassword(const char *str)
{
	if (!str || strlen(str) == 0)
		throw std::runtime_error("password cannot be empty");
	return (std::string(str));
}

int	main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << ERROR << "incorrect number of arguments" << RST << std::endl;
		return (1);
	}
	try {
		int port = parsePort(av[1]);
		std::string password = parsePassword(av[2]);
		Server	s(port, password);

		signal(SIGPIPE, SIG_IGN);
		signal(SIGINT, signalHandler);
		signal(SIGQUIT, signalHandler);
		s.initServer();
		s.runServer();
		if (gSignalStatus)
			std::cout << INFO << "\n[SERVER] shutting down..." << RST << std::endl;
		s.shutdownServer();
	} catch (std::exception & e) {
		std::cout << ERROR << e.what() << RST<< std::endl;
	}
	return (0);
}
