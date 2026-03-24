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
void  cmdMode(Server &server, Client &client, std::vector<std::string> &tokens)
{
   if ((int)tokens.size() < 2)
   {
      printMyMsg(ERROR, "MODE", "Error", "missing argument", client.getFdClient());
	  controlErrors(server, client, ERR_NEEDMOREPARAMS, "MODE");
	  return;
   }
   Channel *channel = server.getChannel(tokens[1]);
   if (!channel)
   {
	  printMyMsg(ERROR, "MODE", "Error", "No such channel", client.getFdClient());
	  controlErrors(server, client, ERR_NOSUCHCHANNEL, "MODE");
	  return;
   }
   if ((int)tokens.size() == 2)
   {
	  controlRPL(server, client, RPL_CHANNELMODEIS, findChannelMode(channel));
	  return ;
   }
   if (!channel->isOperator(client))
   {
	  printMyMsg(ERROR, "MODE", "Error", "You're not operator", client.getFdClient());
	  controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "MODE", channel->getName());
	  return ;
   }
}
