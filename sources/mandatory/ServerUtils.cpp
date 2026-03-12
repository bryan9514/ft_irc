/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:23:14 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 23:25:03 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "IrcCodes.hpp"
#include <iostream>

void	signalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		gSignalStatus   = 1;
}

void printMyMsg(const std::string &color, const std::string &module, const std::string &type,
				const std::string &msg, int fd, const std::string &value)
{
	std::cout << color << "[" << module << "] " << type << ": " << msg << " (fd: " << fd << ")";
	if (!value.empty())
		std::cout << " : " << value;
	std::cout << RST << std::endl;
}
