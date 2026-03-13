/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:46:21 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 23:44:14 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "IrcCodes.hpp"
#include <string>

void	cmdPass(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (tokens.size() < 2) {
		printMyMsg(ERROR, "PASS", "Error", "missing password", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "PASS");
		return;
	}
	if (client.getPassOk()) {
		printMyMsg(ERROR, "PASS", "Error", "password already set", client.getFdClient());
		controlErrors(server, client, ERR_ALREADYREGISTERED);
		return;
	}
	if (tokens[1] != server.getPass()) {
		printMyMsg(ERROR, "PASS", "Error", "wrong password", client.getFdClient());
		controlErrors(server, client, ERR_PASSWDMISMATCH);
		return;
	}
	client.setPassOk(true);
	client.setPassClient(tokens[1]);
	printMyMsg(SUCCESS, "PASS", "Success", "password accepted", client.getFdClient());
	server.checkRegistration(client);
}
