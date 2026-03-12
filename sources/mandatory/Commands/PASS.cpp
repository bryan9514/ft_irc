/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:46:21 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 23:24:07 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "IrcCodes.hpp"
#include <string>
#include <iostream>

void	cmdPass(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (tokens.size() < 2) {
		std::cout << ERROR << "[PASS] Error: missing password (fd: " << client.getFdClient() << ")" << RST << std::endl;
		return;
	}
	if (client.getPassOk()) {
		std::cout << ERROR << "[PASS] Error: already set from (fd: " << client.getFdClient() << ") : " << tokens[1] << RST << std::endl;
		return;
	}
	if (tokens[1] == server.getPass()) {
		client.setPassOk(true);
		client.setPassClient(tokens[1]);
		std::cout << SUCCESS << "[PASS] Success: Password accepted (fd: " << client.getFdClient() << ") : " << tokens[1] << RST <<std::endl;
	} else {
		std::cout << ERROR << "[PASS] Error: Wrong password (fd: " << client.getFdClient() << ") : " << tokens[1]  << RST << std::endl;
	}
}
