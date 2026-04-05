/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:01:42 by ntome             #+#    #+#             */
/*   Updated: 2026/04/05 12:15:17 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <string>

std::string	megaphon(std::string s)
{
	for (int i = 0; i < (int)s.length(); i++) {
		s[i] = std::toupper(s[i]);
	}
	return (s);
}

void	cmdBot(Server & server, Client & client, std::vector<std::string> & tokens)
{
	if (tokens.size() < 2) {
		printMyMsg(ERROR, "BOT", "ERROR", "", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "BOT");
		return ;
	}
	for (int i = 1; i < (int)tokens.size();  i++) {
		server.broadcast(megaphon(tokens[i]), -1);
		server.broadcast(" ",  -1);
	}
}