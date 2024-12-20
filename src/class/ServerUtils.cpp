/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:18:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/12/10 12:52:50 by mgayout          ###   ########.fr       */
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
		if (sendme || (!sendme && channel->getMembers()[i] != sender))
			send(this->getClientWithNick(channel->getMembers()[i])->getSocket(), message.c_str(), message.size(), 0);
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

std::vector<std::string>	Server::addBuffer(std::vector<std::string> cmd)
{
	std::string	buf = "";
	for (unsigned int i = 0; i != this->_buffer.size(); i++)
		buf += this->_buffer[i];
	this->_buffer.clear();
	cmd[0] = buf + cmd[0];
	return cmd;
}