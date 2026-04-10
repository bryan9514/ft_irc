#include "Server.hpp"
#include "IrcCodes.hpp"
#include "Client.hpp"

static std::string findChannelMode(Channel *target)
{
    std::string modes = "+";
    std::string args = "";
    if (target->getInviteOnly())
        modes += "i";
    if (target->getTopicSetRule())
        modes += "t";
    if (target->getPassword() != "")
    {
        modes += "k";
        args += " " + target->getPassword();
    }
    if (target->getUserLimit() > 0)
    {
        modes += "l";
        std::ostringstream oss;
        oss << target->getUserLimit();
        args += " " + oss.str();
    }
    if (modes == "+")
        return ("");
    return (modes + args);
}

/**
* example :
*
* $> MODE #chan +i secret
* tokens[0] = "MODE"
* tokens[1] = "#chan"
* tokens[2] = "+i"
* tokens[3] = "password"
**/
void  cmdMode(Server &server, Client &client, std::vector<std::string> &tokens)
{
	if (!client.getRegistered())
	{
		printMyMsg(ERROR, "MODE", "Error", "client not registered", client.getFdClient());
		return ; 
	}
	if ((int)tokens.size() < 2)
	{
		printMyMsg(ERROR, "MODE", "ERROR", "missing argument", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "mode");
		return;
	}
	Channel *channel = server.getChannel(tokens[1]);
	if (!channel)
	{
		printMyMsg(ERROR, "MODE", "ERROR", "no such channel", client.getFdClient());
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "mode");
		return;
	}
	if ((int)tokens.size() == 2)
	{
		server.sendToClient(client, RPL_CHANNELMODEIS(client.getNickName(), channel->getName(), findChannelMode(channel)));
		return ;
	}
	if (!channel->isOperator(&client))
	{
		printMyMsg(ERROR, "MODE", "ERROR", "you're not operator", client.getFdClient());
		controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "MODE", channel->getName());
		return ;
	}
	channel->applyMode(server, client, tokens);
	std::string msg = ":" + client.getNickName() + "!" + client.getUserName() + "@localhost MODE " + tokens[1];
	for (size_t j = 2; j < tokens.size(); j++)
    msg += " " + tokens[j];
	msg += "\r\n";
	channel->broadcastToMembersExcept(server, msg, client.getFdClient());
}
