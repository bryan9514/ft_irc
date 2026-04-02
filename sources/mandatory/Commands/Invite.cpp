#include "Server.hpp"
#include "Channel.hpp"

void	cmdInvite(Server &server, Client &Client, std::vector<std::string> &tokens)
{
	if (tokens.size() == 1)
	{
		std::vector<std::string> usr_invit = client->getInvitation();
		for (int i = 0; i < client.getInvitationSize(); i++)
			controlRPL(server, client, RPL_INVITELIST, "INVITE", usr_invit[i]);
		controlRPL(server, client, RPL_ENDOFINVITELIST, "INVITE");
		return;
	}
	if (tokens.size() == 2)
	{
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "INVITE");
		return;
	}
	std::string target = tokens[1];
	std::string stdchan = tokens[2];
	Channel *chan = server.getChannel(stdchan);
	if (!chan)
	{
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "INVITE", stdchan);
		return;
	}
	if (!chan->isMember(client))
	{
		controlErrors(server, client, ERR_NOTONCHANNEL, "INVITE", stdchan);
		return;
	}
	if (chan->getInviteOnly() && !chan->isOperator(client))
	{
		controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "INVITE", stdchan);
		return;
	}
	if (chan->isMemberbyName(target))
	{
		controlErrors(server, client, ERR_USERONCHANNEL, "INVITE", target, stdchan);
		return;
	}
	controlRPL(server, client, RPL_INVITING, target, stdchan);
	chan->addInvited(target);
	//TODO Message au client invite
}
