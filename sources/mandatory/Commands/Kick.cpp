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
	if (tokens.size() < 3)
	{
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "KICK", "");
		return;
	}
	const std::string &chanName   = tokens[1];
	const std::string &targetNick = tokens[2];
	std::string reason = "No reason given";
	if (tokens.size() >= 4)
	{
		std::string raw = tokens[3];
		if (!raw.empty() && raw[0] == ':')
			raw = raw.substr(1);
		for (size_t i = 4; i < tokens.size(); ++i)
			raw += " " + tokens[i];
		if (!raw.empty())
			reason = raw;
	}
	Channel *chan = server.getChannel(chanName);
	if (!chan)
	{
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "KICK", chanName);
		return;
	}
	if (!chan->isMember(&client))
	{
		controlErrors(server, client, ERR_NOTONCHANNEL, "KICK", chanName);
		return;
	}
	if (!chan->isOperator(&client))
	{
		controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "KICK", chanName);
		return;
	}
	Client *target = findClientByNick(server, targetNick);
	if (!target)
	{
		controlErrors(server, client, ERR_NOSUCHNICK, "KICK", targetNick);
		return;
	}
	if (!chan->isMember(target))
	{
		controlErrors(server, client, ERR_USERNOTINCHANNEL, "KICK", targetNick);
		return;
	}
	std::string kickMsg = ":" + client.getNickName()
		+ "!" + client.getUserName()
		+ "@ircserv KICK "
		+ chanName + " " + targetNick
		+ " :" + reason + "\r\n";

	chan->broadcastToMembers(server, kickMsg);
	if (chan->isOperator(target))
		chan->removeOperator(target);
	else
		chan->removeNormalMember(target);
	chan->removeMember(target);
	printMyMsg(INFO, "KICK", "CMD",
			   client.getNickName() + " kicked " + targetNick + " from " + chanName,
			   client.getFdClient(), reason);
}
