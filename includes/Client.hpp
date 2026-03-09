/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:33:33 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/09 12:33:09 by brturcio         ###   ########.fr       */
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
	bool			_registered;

public:
	void	setFdClient(int fdClient) {
		_fdClient = fdClient;
	}
	void	setPassClient(const std::string & passClient);
	void	setNickName(const std::string & passName);
	void	setUserName(const std::string & userName);
};

#endif
