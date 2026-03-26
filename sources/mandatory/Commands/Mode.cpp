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
        args += " " + std::to_string(target->getUserLimit());
    }
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
void  cmdmode(server &server, client &client, std::vector<std::string> &tokens)
{
	if ((int)tokens.size() < 2)
	{
		printmymsg(error, "mode", "error", "missing argument", client.getfdclient());
		controlerrors(server, client, err_needmoreparams, "mode");
		return;
	}
	channel *channel = server.getchannel(tokens[1]);
	if (!channel)
	{
		printmymsg(error, "mode", "error", "no such channel", client.getfdclient());
		controlerrors(server, client, err_nosuchchannel, "mode");
		return;
	}
	if ((int)tokens.size() == 2)
	{
		controlrpl(server, client, rpl_channelmodeis, findchannelmode(channel));
		return ;
	}
	if (!channel->isoperator(client))
	{
		printmymsg(error, "mode", "error", "you're not operator", client.getfdclient());
		controlerrors(server, client, err_chanoprivsneeded, "mode", channel->getname());
		return ;
	}
	channel->applymode(server, client, tokens);
	std::string msg = ":" + client.getNickName() + "!" + client.getUserName() + "@localhost MODE " + tokens[1];
	for (size_t j = 2; j < tokens.size(); j++)
    msg += " " + tokens[j];
	channel->broadcastToMembers(server, msg);
}
