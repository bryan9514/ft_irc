/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 21:07:34 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/03 23:44:07 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

/* =========================== default constructor ========================== */
Client::Client() :
	_fdClient(-1),
	_passClient(""),
	_nickName(""),
	_userName(""),
	_realName(""),
	_buffer(""),
	_outBuffer(""),
	_passOk(false),
	_hasNick(false),
	_hasUser(false),
	_registered(false),
	_toDelete(false)
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

void	Client::setRealName(const std::string & realName)
{
	_realName = realName;
}

void	Client::setBuffer(const std::string & data)
{
	_buffer = data;
}

void	Client::setRegistered(bool registered)
{
	_registered = registered;
}

void	Client::setPassOk(bool value)
{
	_passOk = value;
}

void	Client::setHasNick(bool value)
{
	_hasNick = value;
}

void	Client::setHasUser(bool value)
{
	_hasUser = value;
}

void	Client::appendOutBuffer(const std::string &msg)
{
    _outBuffer += msg;
}

void	Client::appendBuffer(const std::string & newData)
{
	_buffer += newData;
}

void	Client::setToDelete(bool valor)
{
	_toDelete = valor;
}

void	Client::setQuitReason(const std::string &reason)
{
    _quitReason = reason;
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

const std::string &	Client::getRealName(void) const
{
	return (_realName);
}

std::string &	Client::getBuffer(void)
{
	return (_buffer);
}

std::string &	Client::getOutBuffer()
{
    return _outBuffer;
}

bool	Client::getPassOk(void) const
{
	return _passOk;
}

bool	Client::getHasNick(void) const
{
	return _hasNick;
}

bool	Client::getHasUser(void) const
{
	return _hasUser;
}

bool	Client::getRegistered(void) const
{
	return (_registered);
}

int		Client::getInvitationSize(void) const
{
	return (this->_invitation.size());
}

std::vector<std::string>		Client::getInvitations(void) const
{
	return (this->_invitation);
}

bool	Client::getToDelete() const
{
	return _toDelete;
}

const	std::string &Client::getQuitReason(void) const
{
    return _quitReason;
}

void	Client::addInvitation(std::string invitation)
{
	this->_invitation.push_back(invitation);
	return ;
}
