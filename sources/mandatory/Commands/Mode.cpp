#include "Server.hpp"
#include "IrcCodes.hpp"
#include "Client.hpp"


/**
* Utilisation :
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
}
