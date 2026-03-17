/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:34:14 by ntome             #+#    #+#             */
/*   Updated: 2026/03/17 14:14:15 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.hpp"

Topic::Topic(void) {
	this->_topic = "";
	this->_author = NULL;
	this->_isSet = false;
	this->_topicTime = 0;
}

Topic::~Topic(void) {}


//Setter

void	Topic::setTopic(std::string topic) {
	this->_topic = topic;
}

void	Topic::setAuthor(Client *client) {
	this->_author = client;
}

void	Topic::setIsSet(bool isSet) {
	this->_isSet = isSet;
}

void	Topic::setTopicTime(int topicTime) {
	this->_topicTime = topicTime;
}

//Getter

std::string	Topic::getTopic(void) const {
	return this->_topic;
}

Client		*Topic::getAuthor(void) const {
	return this->_author;
}

bool		Topic::getIsSet(void) const {
	return this->_isSet;
}

int			Topic::getTopicTime(void) const {
	return this->_topicTime;
}