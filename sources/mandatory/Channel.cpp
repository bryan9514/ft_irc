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

void Channel::broadcastToMembers(Server &server, const std::string &msg)
{
    for (std::map<int, Client*>::iterator it = _members.begin(); it != _members.end(); it++)
        server.sendToClient(*it->second, msg);
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
