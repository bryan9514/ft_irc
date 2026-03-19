/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:40:36 by ntome             #+#    #+#             */
/*   Updated: 2026/03/19 10:12:56 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string> //std::string
# include <map> //std::map
# include <vector> //std::vector
# include <algorithm> //std::find
# include <Client.hpp>
# include <Topic.hpp>
# include <ChannelRules.hpp>

class Channel
{
	private: // use https://modern.ircdocs.horse/#channels for the infos
		std::string				_name; //Chan name
		std::map<int, Client *>	_members; //Chan members
		std::vector<Client *>	_operators; //Members that are mods
		std::vector<Client *>	_normal_members; //Normal members
		Topic					_topic; //The topic of the chan
		ChannelRules			_rules; //The rules of the chan

	public:
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
};

#endif