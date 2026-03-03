/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:00:10 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/03 17:03:39 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"
#include "Server.hpp"
#include <stdlib.h>
#include <exception>
#include <iostream>


int	main(int ac, char **av)
{
	if (ac != 3) {
		std::cout << ERROR << "incorrect number of arguments" << RST << std::endl;
		return (1);
	}
	try {
		Server	s(std::atoi(av[1]), av[2]);

		s.initServer();
		//s.runServer();

	} catch (std::exception & e) {
		std::cout << ERROR << e.what() << RST<< std::endl;
	}
	return (0);
}
