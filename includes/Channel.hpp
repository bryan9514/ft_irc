/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:40:36 by ntome             #+#    #+#             */
/*   Updated: 2026/04/02 20:09:19 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string> //std::string
# include <map> //std::map
# include <vector> //std::vector
# include <algorithm> //std::find
# include <iostream> //std::cout
# include <Client.hpp>
# include <Server.hpp>
# include <Topic.hpp>
# include <ChannelRules.hpp>

class Server;

class Channel
{
	private: // use https://modern.ircdocs.horse/#channels for the infos
		std::string					_name; //Chan name
		std::map<int, Client *>		_members; //Chan members
		std::vector<Client *>		_operators; //Members that are mods
		std::vector<Client *>		_normal_members; //Normal members
		Topic						_topic; //The topic of the chan
		ChannelRules				_rules; //The rules of the chan
		std::vector<std::string>	_invited;

	public:
		Channel(void);
		Channel(std::string name);
		~Channel(void);

		//Setter

		void	setName(std::string name);
		void	addMember(Client *client);
		void	addOperator(Client *client);
		void	addNormalMember(Client *client);
		void	removeMember(Client *client);
		void	removeOperator(Client *client);
		void	removeNormalMember(Client *client);

		//Getter

		std::string	getName(void) const;
		bool		isMember(Client *client) const;
		bool		isOperator(Client *client) const;
		bool		isNormalMember(Client *client) const;

		void		broadcastToMembers(Server &server, const std::string &msg);
		bool		getInviteOnly(void) const;
		bool        getTopicSetRule(void) const;
		std::string getPassword(void) const;
		int         getUserLimit(void) const;

		void		setInviteOnly(bool state);
		void		setTopicSetRule(bool state);
		void		setPassword(std::string password);
		void		setUserLimit(int limit);

		void		applyMode(Server &server, Client &client, std::vector<std::string> &tokens);
		void		addOperatorByString(std::string name);
		void		removeOperatorByString(std::string name);

		bool		IsMembersbyName(std::string name);
		bool		IsInvitedbyName(std::string name);
		void		addInvited(std::string name);
		void		removeInvited(std::string name);

		std::string	getMembers(void) const;
		std::string getOperators(void) const;
		int			getMembersSize(void) const;

		ChannelRules	getRules(void) const;
		Topic			getTopic(void) const;

		bool		isFull(void) const;
};

#endif
