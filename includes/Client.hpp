/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:33:33 by brturcio          #+#    #+#             */
/*   Updated: 2026/04/03 23:44:17 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>

class Client
{
	private:
		int				_fdClient;
		std::string		_passClient;
		std::string		_nickName;
		std::string		_userName;
		std::string		_realName;
		std::string		_buffer;
		std::string		_outBuffer;
		std::string		_quitReason;
		bool			_passOk;
		bool			_hasNick;
		bool			_hasUser;
		bool			_registered;
		bool 			_toDelete;
		std::vector<std::string> _invitation;

	public:
		Client(void);

		void	setFdClient(int fdClient);
		void	setPassClient(const std::string & passClient);
		void	setNickName(const std::string & nickName);
		void	setUserName(const std::string & userName);
		void	setRealName(const std::string & realName);
		void	setBuffer(const std::string & data);
		void	setQuitReason(const std::string &reason);
		void	setRegistered(bool registered);
		void	setToDelete(bool valor);

		void	setPassOk(bool value);
		void	setHasNick(bool value);
		void	setHasUser(bool value);
		
		void	appendOutBuffer(const std::string &msg);
		void	appendBuffer(const std::string &newData);

		int					getFdClient(void) const;
		const std::string &	getPassClient(void) const;
		const std::string &	getNickName(void) const;
		const std::string &	getUserName(void) const;
		const std::string &	getRealName(void) const;
		std::string &		getBuffer(void);
		std::string &		getOutBuffer(void);
		const std::string &	getQuitReason(void) const;

		bool	getPassOk(void) const;
		bool	getHasNick(void) const;
		bool	getHasUser(void) const;
		bool	getRegistered(void) const;
		int		getInvitationSize(void) const;
		bool	getToDelete() const;
		std::vector<std::string>		getInvitations(void) const;
};

#endif
