/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:18:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/11/19 17:56:10 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

int	Server::nicknameUsed(std::string nick)
{
	for (unsigned int i = 1; i != this->_nbClient; i++)
	{
		if (this->_clients[this->_pfds[i].fd]->getNickname() == nick && this->_clients[this->_pfds[i].fd]->getNick())
			return this->_clients[this->_pfds[i].fd]->getSocket();
	}
	return 0;
}

void	Server::sendChannel(std::string channelname, std::string sender, std::string message, bool sendme)
{
	Channel	*channel = getChannel(channelname);

	for (unsigned int i = 0; i < channel->getMembers().size(); i++)
	{
		std::cout << "member [" << i << "] = " << channel->getMembers()[i] << std::endl;
		if (sendme || (!sendme && channel->getMembers()[i] != sender))
			send(this->getClientWithNick(channel->getMembers()[i])->getSocket(), message.c_str(), message.size(), 0);
	}
}

void	Server::sendAll(std::string username, std::string msg)
{
	for (unsigned int i = 1; i < this->getNbClient(); i++)
		if (this->_clients[this->_pfds[i].fd]->getNickname() != username)
			send(this->_clients[this->_pfds[i].fd]->getSocket(), msg.c_str(), msg.size(), 0);
}

void	Server::removeChannel(std::string channel)
{
	delete this->_channels[channel];
	this->_channels.erase(channel);
}