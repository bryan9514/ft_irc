/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SplitString.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:52:14 by ntome             #+#    #+#             */
/*   Updated: 2026/04/02 20:52:23 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>	splitString(std::string s, char sep)
{
	std::vector<std::string>	result;
	int							start = 0;

	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == sep) {
			result.push_back(s.substr(start, i - start));
			start = i + 1;
		}
	}
	result.push_back(s.substr(start, s.length() - start));
	return (result);
}