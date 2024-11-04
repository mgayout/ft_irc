/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:18:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/11/01 15:52:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::vector<std::string>    Server::splitBuffer(std::string buf)
{
	std::vector<std::string>	command;
	std::string					tmp;

	for (unsigned int i = 0, j = 0; i != buf.size(); i++)
	{
		if (buf[i] == ' ')
		{
			tmp = buf.substr(j, i - j);
			command.push_back(tmp);
			j = i + 1;
		}
		else if (buf[i] == '\n')
		{
			tmp = buf.substr(j, i - (j + 1) );
			command.push_back(tmp);
			break;
		}
	}
	
	return command;
}

int	Server::nicknameUsed(std::string nick)
{
	for (unsigned int i = 1; i != this->_nbClient; i++)
	{
		if (this->_clients[this->_pfds[i].fd]->getNickname() == nick && this->_clients[this->_pfds[i].fd]->getNick())
			return this->_clients[this->_pfds[i].fd]->getSocket();
	}
	return 0;
}

void	Server::sendChannel(Channel *channel, std::string message)
{
	for (unsigned int i = 0; i < channel->getMembers().size(); i++)
		for (unsigned int j = 1; j < this->getNbClient(); j++)
			if (this->_clients[this->_pfds[j].fd]->getNickname() == channel->getMembers()[i])
				send(this->_clients[this->_pfds[j].fd]->getSocket(), message.c_str(), message.size(), 0);
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