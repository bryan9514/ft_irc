/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:53:53 by ntome             #+#    #+#             */
/*   Updated: 2026/03/17 14:14:03 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP
# define TOPIC_HPP

# include <string>
# include <Client.hpp>

class Topic
{
	private: // Look https://modern.ircdocs.horse/#topic-message
		std::string	_topic; //The topic
		Client		*_author; //The author of the topic
		bool		_isSet; //If the topic is set or not
		int			_topicTime; //When the topic was updated
	
	public:
		Topic(void);
		~Topic(void);

		//Setter
		void	setTopic(std::string topic);
		void	setAuthor(Client *client);
		void	setIsSet(bool isSet);
		void	setTopicTime(int topicTime);

		//Getter
		std::string	getTopic(void) const;
		Client		*getAuthor(void) const;
		bool		getIsSet(void) const;
		int			getTopicTime(void) const;
};

#endif