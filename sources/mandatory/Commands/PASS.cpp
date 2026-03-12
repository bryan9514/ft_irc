/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:46:21 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 10:18:18 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "ft_irc.hpp"
#include <string>
#include <iostream>

//password del servidor
//estado del cliente
void	cmdPass(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (tokens.size() < 2) {
		std::cout << ERROR << "Error: PASS requires a password for client" << " (fd: " << client.getFdClient() << ")" << RST << std::endl;
		return;
	}
	if (client.getPassOk()) {
		std::cout << ERROR << "Error: PASS already set" << RST << std::endl;
		return;
	}
	if (tokens[1] == server.getPass()) {
		client.setPassOk(true);
		client.setPassClient(tokens[1]);
		std::cout << SUCCESS << "[SERVER] Password accepted" << RST <<std::endl;
	} else {
		std::cout << ERROR << "Error: Wrong password" << RST << std::endl;
	}
}
