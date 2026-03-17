/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:00:10 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/16 10:57:08 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "IrcCodes.hpp"
#include <stdlib.h>
#include <exception>
#include <iostream>

volatile sig_atomic_t gSignalStatus = 0;
void	shutdownServer(void);

int	main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << ERROR << "incorrect number of arguments" << RST << std::endl;
		return (1);
	}
	try {
		Server	s(std::atoi(av[1]), av[2]);

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
