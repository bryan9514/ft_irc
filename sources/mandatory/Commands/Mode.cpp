#include "Server.hpp"
#include "IrcCodes.hpp"
#include "Client.hpp"


static std::string		findChannelMode(Server &server, std::string &chanName)
{
	Channel *target = server.getChannel(chanName);
	if (target) {
		std::string modes = "+";
		if (target->getInviteOnly())
			modes += "i";
		if (target->getTopicSetRules())
			modes += "t";
		if (target->getPassword())
			mode += "k";
		if (target->getUserLimit())
			mode += "l";
		return (modes);
	}
	return ("");
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
   if (!server.getChannel(tokens[1]))
   {
	  printMyMsg(ERROR, "MODE", "Error", "No such channel", client.getFdClient());
	  controlErrors(server, client, ERR_NOSUCHCHANNEL, "MODE");
	  return;
   }
   if ((int)tokens.size() == 2)
   {
	  controlRPL(server, client, server.getChannel())
   }
}
