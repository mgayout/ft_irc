/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:10:11 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 14:10:11 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string	currentDateTime()
{
	time_t		now = time(0);
	struct tm	timestruct;
	char		buffer[1024];
	timestruct = *localtime(&now);

	strftime(buffer, sizeof(buffer), "%X", &timestruct);

	return buffer;
}

void	Server::sendMessage(int clienFd, std::string msg)
{
	std::string	newMsg = "[" + currentDateTime() + "] :" + msg;
	if (!this->_clients[clienFd]->getHexchat())
	{
		if (send(clienFd, newMsg.c_str(), newMsg.size(), 0) == -1)
			throw (Server::sendException());
	}
	else
	{
		if (send(clienFd, msg.c_str(), msg.size(), 0) == -1)
			throw (Server::sendException());	
	}
}