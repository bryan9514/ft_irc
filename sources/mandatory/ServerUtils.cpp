/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 09:23:14 by brturcio          #+#    #+#             */
/*   Updated: 2026/03/11 17:05:08 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	signalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGQUIT)
		gSignalStatus   = 1;
}
