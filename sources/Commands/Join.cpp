/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:18:15 by ntome             #+#    #+#             */
/*   Updated: 2026/04/10 15:57:17 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "IrcCodes.hpp"
#include "Client.hpp"
#include <string>

void	cmdJoin(Server & server, Client & client, std::vector<std::string> & tokens)
{
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;

	if (!client.getRegistered())
	{
		printMyMsg(ERROR, "JOIN", "Error", "client not registered", client.getFdClient());
		return ; 
	}
	if (tokens.size() < 2) {
		printMyMsg(ERROR, "JOIN", "ERROR", "", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "JOIN");
		return ;
	}
	channels = splitString(tokens[1], ',');
	if (tokens.size() > 2)
		keys = splitString(tokens[2], ',');
	
	for (int i = 0; i < (int)channels.size(); i++) {
		if (channels[i].empty() || channels[i][0] != '#') {
			printMyMsg(ERROR, "JOIN", "ERROR", "Channel is inexistant or out of range", client.getFdClient());
			controlErrors(server, client, ERR_NOSUCHCHANNEL, "JOIN");
			continue;
		}
		if (!server.hasChannel(channels[i]))
			server.createChannel(channels[i], &client);
		Channel *channel = server.getChannel(channels[i]);
		if (channel->getRules().getInviteOnly() && !channel->IsInvitedbyName(client.getNickName())) {
			printMyMsg(ERROR, "JOIN", "ERROR", "Invite only channel ", client.getFdClient());
			controlErrors(server, client, ERR_INVITEONLYCHAN, "JOIN");
			server.sendToClient(client, ERR_INVITEONLYCHAN(client.getNickName(), channels[i]) + "\r\n");
			continue;
		}
		if (channel->getRules().getPassword() != "" && (i >= (int)keys.size() || keys[i] != channel->getRules().getPassword())) {
			printMyMsg(ERROR, "JOIN", "ERROR", "Wrong channel key", client.getFdClient());
			controlErrors(server, client, ERR_BADCHANNELKEY, "JOIN");
			for (int i = 0; i < (int)keys.size(); i++)
				std::cout << keys[i] << std::endl;
			continue;
		}
		if (channel->isFull()) {
			printMyMsg(ERROR, "JOIN", "ERROR", "Channel is full ", client.getFdClient());
			controlErrors(server, client, ERR_CHANNELISFULL, "JOIN");
			continue;
		}
		channel->addMember(&client);
		if (channel->getMembersSize() == 1)
			channel->addOperator(&client);
		channel->removeInvited(client.getRealName());
		printMyMsg(SUCCESS, "JOIN", "Success", client.getNickName() + " is joining the channel " + channels[i], client.getFdClient());
		server.getChannel(channels[i])->broadcastToMembers(server, ":" + client.getNickName() + " JOIN " + channels[i] + "\r\n");
		if (channel->getTopic().getIsSet()) {
			server.sendToClient(client, RPL_TOPIC(client.getNickName(), channels[i], channel->getTopic().getTopic()) + "\r\n");
			server.sendToClient(client, RPL_TOPICWHOTIME(client.getNickName(), channels[i], channel->getTopic().getAuthor()->getNickName(), (channel->getTopic().getTopicTimeString())) + "\r\n");
		}
		server.sendToClient(client, RPL_NAMEREPLY(client.getNickName(), "=", channels[i], channel->getMembers()));
		server.sendToClient(client, RPL_ENDOFNAMES(client.getNickName(), channels[i]));
	}
}
