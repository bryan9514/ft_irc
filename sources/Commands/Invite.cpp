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

void	cmdInvite(Server &server, Client &client, std::vector<std::string> &tokens)
{
	if (tokens.size() == 1)
	{
		std::vector<std::string> usr_invit = client.getInvitations();
		for (int i = 0; i < client.getInvitationSize(); i++)
			server.sendToClient(client, RPL_INVITELIST(client.getNickName(), usr_invit[i]));
		server.sendToClient(client, RPL_ENDOFINVITELIST(client.getNickName()));
		printMyMsg(SUCCESS, "INVITE", "Success", "sending list of invitation", client.getFdClient());
		return;
	}
	if (tokens.size() == 2)
	{
		printMyMsg(ERROR, "INVITE", "ERROR", "", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "INVITE");
		return;
	}
	std::string std_target = tokens[1];
	std::string stdchan = tokens[2];
	Channel *chan = server.getChannel(stdchan);
	Client *target = findClientByNick(server, std_target);
	if (!target)
	{
		printMyMsg(ERROR, "INVITE", "ERROR", "nick out of range or inexistant", client.getFdClient());
		controlErrors(server, client, ERR_NOSUCHNICK, "INVITE", std_target);
		return;
	}
	if (!chan)
	{
		printMyMsg(ERROR, "INVITE", "ERROR", "channel out of range or inexistant", client.getFdClient());
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "INVITE", stdchan);
		return;
	}
	if (!chan->isMember(&client))
	{
		printMyMsg(ERROR, "INVITE", "ERROR", "Client isn't a member", client.getFdClient());
		controlErrors(server, client, ERR_NOTONCHANNEL, "INVITE", stdchan);
		return;
	}
	if (chan->getInviteOnly() && !chan->isOperator(&client))
	{
		printMyMsg(ERROR, "INVITE", "ERROR", "isn't operator to perform the command", client.getFdClient());
		controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "INVITE", stdchan);
		return;
	}
	if (chan->isMember(target))
	{
		printMyMsg(ERROR, "INVITE", "ERROR", "is already on the channel", client.getFdClient());
		controlErrors(server, client, ERR_USERONCHANNEL, target->getNickName(), stdchan);
		return;
	}
	server.sendToClient(client, RPL_INVITING(client.getNickName(), stdchan, target->getNickName()));
	chan->addInvited(target->getNickName());
	target->addInvitation(stdchan);
	server.sendToClient(*target, ":" + client.getNickName() + " has invited you to " + stdchan + "\r\n");
}
