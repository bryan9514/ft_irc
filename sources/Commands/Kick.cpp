#include "Server.hpp"
#include "Channel.hpp"

static Client *findClientByNick(Server &server, const std::string &nick)
{
	const std::map<int, Client> &clients = server.getClients();
	for (std::map<int, Client>::const_iterator it = clients.begin();
		 it != clients.end(); ++it)
	{
		if (it->second.getNickName() == nick)
			return const_cast<Client *>(&it->second);
	}
	return NULL;
}

void	cmdKick(Server &server, Client &client, std::vector<std::string> &tokens)
{
	if (!client.getRegistered())
	{
		printMyMsg(ERROR, "KICK", "Error", "client not registered", client.getFdClient());
		return ; 
	}
	if (tokens.size() < 3)
	{
		printMyMsg(ERROR, "KICK", "ERROR", "Not enough parameters", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "KICK");
		return ;
	}

	std::string chanName = tokens[1];

	if (!server.hasChannel(chanName))
	{
		printMyMsg(ERROR, "KICK", "ERROR", "Channel inexistant or out of range", client.getFdClient());
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "KICK", chanName);
		return ;
	}
	Channel *chan = server.getChannel(chanName);
	if (!chan->isMember(&client))
	{
		printMyMsg(ERROR, "KICK", "ERROR", "You aren't on the channel", client.getFdClient());
		controlErrors(server, client, ERR_NOTONCHANNEL, "KICK", chanName);
		return ;
	}
	if (!chan->isOperator(&client))
	{
		printMyMsg(ERROR, "KICK", "ERROR", "You're not Operator", client.getFdClient());
		controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "KICK", chanName);
		return ;
	}
	std::vector<std::string> targetNicks = splitString(tokens[2], ',');

	for (int i = 0; i < (int)targetNicks.size(); i++)
	{
		std::string targetNick = targetNicks[i];
		Client *target = findClientByNick(server, targetNick);
		if (!target || !chan->isMember(target))
		{
			printMyMsg(ERROR, "KICK", "ERROR", "User is not in Channel", client.getFdClient());
			controlErrors(server, client, ERR_USERNOTINCHANNEL, "KICK", targetNick);
			continue ;
		}
		if (chan->isOperator(target))
		{
			printMyMsg(ERROR, "KICK", "ERROR", "Operator can't be kicked", client.getFdClient());
			controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "KICK", targetNick);
			continue ;
		}
		std::string reason = "No reason given";
		if (tokens.size() >= 4) {
			std::string raw = tokens[3];
			if (!raw.empty() && raw[0] == ':')
				raw = raw.substr(1);
			for (size_t i = 4; i < tokens.size(); ++i)
				raw += " " + tokens[i];
			if (!raw.empty())
				reason = raw;
		}
		std::string kickMsg = ":" + client.getNickName()
		+ "!" + client.getUserName()
		+ "@ircserv KICK "
		+ chanName + " " + target->getUserName()
		+ " :" + reason + "\r\n";
		chan->broadcastToMembersExcept(server, kickMsg, client.getFdClient());
		chan->removeMember(target);
		printMyMsg(INFO, "KICK", "CMD",
		  	   client.getNickName() + " kicked " + targetNick + " from " + chanName,
		  	   client.getFdClient(), reason);
	}
}

