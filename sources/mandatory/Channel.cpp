/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:56:59 by ntome             #+#    #+#             */
/*   Updated: 2026/03/19 10:28:26 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name) {
	this->_name = name;
	this->_topic = Topic();
	this->_rules = ChannelRules();
}

Channel::~Channel(void) {}

//Setter

void	Channel::setName(std::string name) {
	this->_name = name;
}

void	Channel::addMember(Client *client) {
	this->_members[client->getFdClient()] = client;
}

void	Channel::addOperator(Client *client) {
	this->_operators.push_back(client);
}

void	Channel::addNormalMember(Client *client) {
	this->_normal_members.push_back(client);
}

void	Channel::removeMember(Client *client) {
	if (this->isOperator(client))
		removeOperator(client);
	this->_members.erase(client->getFdClient());
}

void	Channel::removeOperator(Client *client) {
	std::vector<Client *>::iterator it = std::find(this->_operators.begin(), this->_operators.end(), client);
	if (it != this->_operators.end())
		this->_operators.erase(it);
}

void	Channel::removeNormalMember(Client *client) {
	std::vector<Client *>::iterator it = std::find(this->_normal_members.begin(), this->_normal_members.end(), client);
	if (it != this->_normal_members.end())
		this->_normal_members.erase(it);
}

//Getter

std::string	Channel::getName(void) const {
	return this->_name;
}

bool		Channel::isMember(Client *client) const {
	int	fd = client->getFdClient();
	return _members.find(fd) != _members.end(); //This work the same way that removeOperator
}

bool		Channel::isOperator(Client *client) const {
	for (size_t i = 0; i < this->_operators.size(); i++) {
		if (this->_operators[i] == client)
			return true;
	}
	return false;
}

bool		Channel::isNormalMember(Client *client) const {
	for (size_t i = 0; i < this->_normal_members.size(); i++) {
		if (this->_normal_members[i] == client)
			return true;
	}
	return false;
}
//Modes utility
void Channel::broadcastToMembers(Server &server, const std::string &msg)
{
    for (std::map<int, Client*>::iterator it = _members.begin(); it != _members.end(); it++)
        server.sendToClient(*it->second, msg);
}

void	Channel::applyMode(Server &server, Client &client, std::vector<std::string> &tokens)
{
	std::string modes = tokens[2];
	std::vector<std::string> args(tokens.begin() + 3, tokens.end());
	int argIndex = 0;
	bool plusminus = false;
	for (size_t i = 0; i < modes.size(); i++)
	{
		char c = modes[i];
		if (c == '+')
			plusminus = true;
		else if (c == '-')
			plusminus = false;
		else if (c == 'i')
			this->setInviteOnly(plusminus);
		else if (c == 't')
			this->setTopicSetRule(plusminus);
		else if (c == 'k')
		{
			if (plusminus == true)
				this->setPassword(args[argIndex]);
			else
				this->setPassword("");
			argIndex++;
		}
		else if (c == 'l')
		{
			if (plusminus == true)
				this->setUserLimit(std::atoi(args[argIndex].c_str()));
			else
				this->setUserLimit(-1);
			argIndex++;
		}
		else if (c == 'o')
		{
			if (plusminus == true)
				addOperator(client);
			else
				removeOperator(client);
		}
	}
}

//Getter of rules
bool Channel::getInviteOnly(void) const
{
    return _rules.getInviteOnly();
}

bool Channel::getTopicSetRule(void) const
{
    return _rules.getTopicSetRule();
}

std::string Channel::getPassword(void) const
{
    return _rules.getPassword();
}

int Channel::getUserLimit(void) const
{
    return _rules.getUserLimit();
}

//Setter of rules
void    Channel::setInviteOnly(bool state)
{
	this->_rules.setInviteOnly(state);
	return ;
}

void    Channel::setTopicSetRule(bool state)
{
	this->_rules.setTopicSetRule(state);
	return ;
}

void    Channel::setPassword(std::string password)
{
	this->_rules.setPassword(password);
	return ;
}

void    Channel::setUserLimit(int limit)
{
	this->_rules.setUserLimit(limit);
	return ;
}
