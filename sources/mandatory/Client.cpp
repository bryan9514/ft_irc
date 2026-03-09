/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:07:34 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/09 21:32:51 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* =========================== default constructor ========================== */
Client::Client() :
	_fdClient(-1),
	_passClient(""),
	_nickName(""),
	_userName(""),
	_buffer(""),
	_registered(false)
{}

/* ================================ setters ================================= */

void	Client::setFdClient(int fdClient)
{
	_fdClient = fdClient;
}

void	Client::setPassClient(const std::string & passClient)
{
	_passClient = passClient;
}

void	Client::setNickName(const std::string & nickName)
{
	_nickName = nickName;
}

void	Client::setUserName(const std::string & userName)
{
	_userName = userName;
}

void	Client::setBuffer(const std::string & data)
{
	_buffer = data;
}

void	Client::setRegistered(bool registered)
{
	_registered = registered;
}

void	Client::appendBuffer(const std::string & newData)
{
	_buffer += newData;
}

/* ================================= getters ================================ */

int	Client::getFdClient(void) const
{
	return (_fdClient);
}

const std::string &	Client::getPassClient(void) const
{
	return (_passClient);
}

const std::string &	Client::getNickName(void) const
{
	return (_nickName);
}

const std::string &	Client::getUserName(void) const
{
	return (_userName);
}

const std::string &	Client::getBuffer(void) const
{
	return (_buffer);
}

bool	Client::getRegistered(void) const
{
	return (_registered);
}




