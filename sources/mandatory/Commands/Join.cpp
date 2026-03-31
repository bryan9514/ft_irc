/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:18:15 by ntome             #+#    #+#             */
/*   Updated: 2026/03/31 13:21:43 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "IrcCodes.hpp"
#include "Client.hpp"
#include <iostream>
#include <string>

std::vector<std::string>	splitString(std::string s, char sep)
{
	std::vector<std::string>	result;
	int							start = 0;

	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == sep) {
			result.push_back(s.substr(start, i - start));
			start = i + 1;
		}
	}
	result.push_back(s.substr(start, s.length() - start));
	return (result);
}

void	cmdJoin(Server & server, Client & client, std::vector<std::string> & tokens)
{
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;

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
			printMyMsg(ERROR, "JOIN", "ERROR", "", client.getFdClient());
			controlErrors(server, client, ERR_NOSUCHCHANNEL, "JOIN");
			continue;
		}
		if (!server.hasChannel(channels[i]))
			server.createChannel(channels[i], client);
		Channel channel(server.getChannel(channels[i]));
		if (channel.getRules().getInviteOnly() && !channel.isInvited(&client)) {
			printMyMsg(ERROR, "JOIN", "ERROR", "", client.getFdClient());
			controlErrors(server, client, ERR_INVITEONLYCHAN, "JOIN");
			continue;
		}
		if (channel.getRules().getPassword() != "" && (i > (int)keys.size() || keys[i] != channel.getRules().getPassword())) {
			printMyMsg(ERROR, "JOIN", "ERROR", "", client.getFdClient());
			controlErrors(server, client, ERR_BADCHANNELKEY, "JOIN");
			continue;
		}
		if (channel.isFull()) {
			printMyMsg(ERROR, "JOIN", "ERROR", "", client.getFdClient());
			controlErrors(server, client, ERR_CHANNELISFULL, "JOIN");
			continue;
		}
		channel.addMember(&client);
		channel.removeInvitation(&client);
		printMyMsg(SUCCESS, "JOIN", "SUCCES", client.getUserName() + " is joining the channel " + channels[i], client.getFdClient());
		//TODO envoyer un message a tout les membres du channel pour prevenir de l'arriver du membre.
		if (channel.getTopic().getIsSet()) {
			//TODO envoyer le topic a l'user mais je sais pas comment faire.
			//TODO envoyer le topicwhotime.
		}
		//TODO envoyer la liste des membres a l'user.
	}
}