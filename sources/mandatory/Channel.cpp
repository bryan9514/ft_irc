/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:56:59 by ntome             #+#    #+#             */
/*   Updated: 2026/03/31 18:41:28 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void)
{
	this->_name = "";
	this->_topic = Topic();
	this->_rules = ChannelRules();
}

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

void	Channel::addInvitation(Client *client) {
	this->_invited.push_back(client);
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

void	Channel::removeInvitation(Client *client) {
	std::vector<Client *>::iterator it = std::find(this->_invited.begin(), this->_invited.end(), client);
	if (it != this->_invited.end())
		this->_invited.erase(it);
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

bool		Channel::isInvited(Client *client) const {
	(void)client;
	if (!this->_rules.getInviteOnly())
		return (true);
	return (false);
	//TODO refaire cette fonction pour verifier la condition.
}

bool		Channel::isFull(void) const {
	if (this->_rules.getUserLimit() == -1)
		return (false);
	else if ((int)this->_members.size() >= this->_rules.getUserLimit())
		return (true);
	return (false);
}

ChannelRules	Channel::getRules(void) const {
	return (this->_rules);
}

Topic			Channel::getTopic(void) const {
	return (this->_topic);
}