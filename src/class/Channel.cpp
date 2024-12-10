/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:14:52 by biaroun           #+#    #+#             */
/*   Updated: 2024/12/10 10:01:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

Channel::Channel(Client *client, std::string name, std::string password)
{
	this->_name = name;
	this->_password = password;
	this->_topic = "";
	this->_i = false;
	this->_t = true;
	this->_maxClient = 0;
	this->_time = getCurrentTime();
    this->addMember(client->getNickname());
	this->addOp(client->getNickname());
}

Channel::~Channel() {}

bool	Channel::isOp(std::string nickname)
{
	for (unsigned int i = 0; i < this->_op.size(); i++)
	{
		if (this->_op[i] == nickname)
			return true;
	}
	return false;
}

bool	Channel::isInvited(std::string nickname)
{
	for (unsigned int i = 0; i < this->_invited.size(); i++)
	{
		if (this->_invited[i] == nickname)
			return true;
	}
	return false;
}

bool	Channel::isMember(std::string nickname)
{
	for (unsigned int i = 0; i < this->_members.size(); i++)
	{
		if (this->_members[i] == nickname)
			return true;
	}
	return false;
}

void	Channel::addOp(std::string nickname)
{
	this->_op.push_back(nickname);
}

void	Channel::addInvited(std::string nickname)
{
	this->_invited.push_back(nickname);
}

void	Channel::addMember(std::string nickname)
{
	this->_members.push_back(nickname);
}

void	Channel::removeOp(std::string nickname)
{
	for (unsigned int i = 0; i < this->_op.size(); i++)
		if (this->_op[i] == nickname)
			this->_op.erase(this->_op.begin() + i);
}

void	Channel::removeInvited(std::string nickname)
{
	for (unsigned int i = 0; i < this->_invited.size(); i++)
		if (this->_invited[i] == nickname)
			this->_invited.erase(this->_invited.begin() + i);
}

void	Channel::removeMember(std::string nickname)
{
	for (unsigned int i = 0; i < this->_members.size(); i++)
		if (this->_members[i] == nickname)
			this->_members.erase(this->_members.begin() + i);
}

void	Channel::clearOp()
{
	for (unsigned int i = 0; i < this->_op.size(); i++)
		this->_op.erase(this->_op.begin() + i);
}

void	Channel::clearInvited()
{
	for (unsigned int i = 0; i < this->_invited.size(); i++)
		this->_invited.erase(this->_invited.begin() + i);
}

void	Channel::clearMember()
{
	for (unsigned int i = 0; i < this->_members.size(); i++)
		this->_members.erase(this->_members.begin() + i);
}

void	Channel::clearAll()
{
	this->clearOp();
	this->clearInvited();
	this->clearMember();
}

void	Channel::clearClient(std::string nickname)
{
	if (this->isOp(nickname))
		removeOp(nickname);
	removeMember(nickname);
}