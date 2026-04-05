/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelRules.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:58:23 by ntome             #+#    #+#             */
/*   Updated: 2026/04/05 11:58:02 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelRules.hpp"

ChannelRules::ChannelRules(void) {
	this->_inviteOnly = false;
	this->_topicSetRule = true;
	this->_password = "";
	this->_userLimit = -1;
}

ChannelRules::~ChannelRules(void) {}

//Setter

void	ChannelRules::setInviteOnly(bool state) {
	this->_inviteOnly = state;
}

void	ChannelRules::setTopicSetRule(bool state) {
	this->_topicSetRule = state;
}

void	ChannelRules::setPassword(std::string password) {
	this->_password = password;
}

void	ChannelRules::setUserLimit(int limit) {
	this->_userLimit = limit;
}

//Getter

bool	ChannelRules::getInviteOnly(void) const {
	return this->_inviteOnly;
}

bool	ChannelRules::getTopicSetRule(void) const {
	return this->_topicSetRule;
}

std::string	ChannelRules::getPassword(void) const {
	return this->_password;
}

int		ChannelRules::getUserLimit(void) const {
	return this->_userLimit;
}