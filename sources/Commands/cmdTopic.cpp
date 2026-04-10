#include "Server.hpp"
#include "Channel.hpp"
#include <ctime>


void	cmdTopic(Server &server, Client &client, std::vector<std::string> &tokens)
{
	if (!client.getRegistered())
	{
		printMyMsg(ERROR, "TOPIC", "Error", "client not registered", client.getFdClient());
		return ; 
	}
	if (tokens.size() < 2)
	{
		printMyMsg(ERROR, "TOPIC", "ERROR", "Need More Params", client.getFdClient());
		controlErrors(server, client, ERR_NEEDMOREPARAMS, "TOPIC");
		return ;
	}
	Channel *chan = server.getChannel(tokens[1]);
	if (!chan)
	{
		printMyMsg(ERROR, "TOPIC", "ERROR", "channel out of range or inexistant", client.getFdClient());
		controlErrors(server, client, ERR_NOSUCHCHANNEL, "TOPIC", tokens[1]);
		return;
	}
	if (!chan->isMember(&client))
	{
		printMyMsg(ERROR, "TOPIC", "ERROR", "Client isn't a member", client.getFdClient());
		controlErrors(server, client, ERR_NOTONCHANNEL, "TOPIC", chan->getName());
		return;
	}
	if (tokens.size() == 2)
	{
		if (chan->getCpTopic().getIsSet()) {
			server.sendToClient(client, RPL_TOPIC(client.getNickName(), chan->getName(), chan->getCpTopic().getTopic()) + "\r\n");
			server.sendToClient(client, RPL_TOPICWHOTIME(client.getNickName(), chan->getName(), chan->getCpTopic().getAuthor()->getNickName(), (chan->getTopic().getTopicTimeString())) + "\r\n");
		}
		else
			server.sendToClient(client, RPL_NOTOPIC(client.getNickName(), chan->getName()));
		return ;
	}
	if (chan->getTopicSetRule() && !chan->isOperator(&client))
	{
		printMyMsg(ERROR, "TOPIC", "ERROR", "isn't operator to perform the command", client.getFdClient());
		controlErrors(server, client, ERR_CHANOPRIVSNEEDED, "TOPIC", chan->getName());
		return;
	}
	else if (tokens.size() >= 3)
	{
		std::string topic = tokens[2];
	    if (!topic.empty() && topic[0] == ':')
		    topic = topic.substr(1);
	    if (topic.empty())
		{
			chan->getCpTopic().setTopic("");
			chan->getCpTopic().setIsSet(false);
			chan->getCpTopic().setTopicTime(0);
			chan->getCpTopic().setAuthor(NULL);
			chan->broadcastToMembers(server, "Clearing the topic on " + chan->getName() + "\r\n");
			return ;
		}
		chan->getCpTopic().setTopic(topic);
		chan->getCpTopic().setIsSet(true);
		chan->getCpTopic().setAuthor(&client);
		time_t t = time(NULL);
		chan->getCpTopic().setTopicTime(t);
		chan->broadcastToMembers(server, RPL_TOPIC(client.getNickName(), chan->getName(), chan->getCpTopic().getTopic()));
		printMyMsg(SUCCESS, "TOPIC", "Success", "New Topic provided on " + chan->getName(), client.getFdClient());
	}
}
