/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 01:03:47 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/12 20:23:53 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include <vector>
#include <string>

std::vector<std::string>	Tokenizer(std::string & line)
{
	std::vector<std::string>	token;
	size_t						start = 0;
	size_t						i = 0;

	if (!line.empty() && line[0] == ':') {
		while (i < line.length() && line[i] != ' ')
			i++;
		i++;
		start = i;
	}
	while (i < line.length()) {
		if (line[i] == ' ') {
			if (i > start)
				token.push_back(line.substr(start, i - start));
			start = i + 1;
		}
		else if (line[i] == ':' && i == start) {
			if (i > start)
				token.push_back(line.substr(start, i - start));
			token.push_back(line.substr(i + 1));
			return (token);
		}
		i++;
	}
	if (start < line.size())
		token.push_back(line.substr(start));
	return (token);
}


void	handleCmd(Server & server, Client & client, std::string & line)
{
	(void)client;
	std::vector<std::string>	tokens = Tokenizer(line);
	
	if (tokens.empty())
		return ;
	std::string cmd = tokens[0];
	if (cmd == "PASS") {
		cmdPass(server, client, tokens);
	}
	else if (cmd == "NICK")
		cmdNick(server, client, tokens);
	// else if (cmd == "USER")
	// 	cmdUser(client, tokens);
	// else if (cmd == "JOIN")
	// 	cmdJoin(client, tokens);
}
