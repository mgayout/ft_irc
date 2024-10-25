/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:14:52 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/22 10:05:14 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Channel.hpp"

Channel::Channel(Client *client, std::string name, std::string password)
{
	this->_name = name;
	this->_password = password;
	this->_topic = "";
	this->_i = false;
	this->_t = false;
	this->_k = false;
	if (this->getPassword().size())
		this->_k = true;
	this->_l = false;
	this->_maxClient = 1;
	this->_date = getCurrentDate();
    _members.insert(std::pair<std::string, bool>(client->getUsername(), true));
}

Channel::~Channel() {}

bool	Channel::isInvited(std::string username)
{
	for (unsigned int i = 0; i < this->_invited.size(); i++)
	{
		if (this->_invited[i] == username)
			return true;
	}
	return false;
}

void	Channel::addClient(std::string username)
{
	this->_members.insert(std::pair<std::string, bool>(username, false));
}

void	Channel::removeClient(std::string username)
{
	this->_members.erase(username);
}