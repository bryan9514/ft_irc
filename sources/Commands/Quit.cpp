/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:57:17 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/04 13:58:13 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Server.hpp"

void	cmdQuit(Server & server, Client & client, std::vector<std::string> & tokens)
{
	(void)server;
	std::string	reason = "Quit: ";
	if (tokens.size() >= 2)
	{
		reason = tokens[1];
		for (size_t i = 2; i < tokens.size(); i++)
			reason += " " + tokens[i];
	}
	client.setQuitReason(reason);
	client.setToDelete(true);
}
