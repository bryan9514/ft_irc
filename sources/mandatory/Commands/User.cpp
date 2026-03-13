/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 11:08:50 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/13 22:40:11 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "IrcCodes.hpp"
#include "Client.hpp"

void	cmdUser(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (!client.getPassOk())
		return;
	if (client.getRegistered()) {
		printMyMsg(ERROR, "USER", "ERROR", "", client.getFdClient());
		controlErrors(server, client, ERR_ALREADYREGISTERED);
		return ;
	}
	if (tokens.size() < 5) {
		printMyMsg(ERROR, "USER", "ERROR", "", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "USER");
		return ;
	}
	client.setUserName(tokens[1]);
	client.setRealName(tokens[4]);
	client.setHasUser(true);
	printMyMsg(SUCCESS, "USER", "Success", "username set", client.getFdClient(), tokens[1]);
	server.checkRegistration(client);
}

