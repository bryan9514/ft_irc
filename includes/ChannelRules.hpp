/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelRules.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:56:59 by ntome             #+#    #+#             */
/*   Updated: 2026/03/17 14:13:17 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELRULES_HPP
# define CHANNELRULES_HPP

# include <string>

class ChannelRules
{
	private:
		bool		_inviteOnly; //+i = true | -i = false
		bool		_topicSetRule; //+t = true = mods only | -t = false = everyone
		std::string	_password; //+k <password> | -k = ""
		int			_userLimit; //+l <limit> | -l = no limite
	
	public:
		ChannelRules(void);
		~ChannelRules(void);

		//Setter
		void	setInviteOnly(bool state);
		void	setTopicSetRule(bool state);
		void	setPassword(std::string password);
		void	setUserLimit(int limit);

		//Getter
		bool		getInviteOnly(void) const;
		bool		getTopicSetRule(void) const;
		std::string	getPassword(void) const;
		int			getUserLimit(void) const;
};

#endif