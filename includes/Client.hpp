/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:33:33 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/09 21:36:08 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
private:
	int				_fdClient;
	std::string		_passClient;
	std::string		_nickName;
	std::string		_userName;
	std::string		_buffer;
	bool			_registered;

public:
	Client(void);

	void	setFdClient(int fdClient);
	void	setPassClient(const std::string & passClient);
	void	setNickName(const std::string & nickName);
	void	setUserName(const std::string & userName);
	void	setBuffer(const std::string & data);
	void	setRegistered(bool registered);
	
	void	appendBuffer(const std::string &newData);

	int					getFdClient(void) const;
	const std::string &	getPassClient(void) const;
	const std::string &	getNickName(void) const;
	const std::string &	getUserName(void) const;
	const std::string &	getBuffer(void) const;
	bool				getRegistered(void) const;
};

#endif
