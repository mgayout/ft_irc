/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:40:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 11:40:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Client.hpp"

Client::Client(int socket)
{
	this->_socket = socket;
	this->_nickname = "";
	this->_username = "";
	this->_hexchat = false;
}

Client::~Client()
{

}

void	Client::setNickname(const std::string nick)
{
	this->_nickname = nick;
}

void	Client::setUsername(const std::string user)
{
	this->_username = user;
}

void	Client::setPassword(bool b)
{
	this->_password = b;
}

void	Client::setHexchat(bool b)
{
	this->_hexchat = b;
}

std::string	Client::getNickname()
{
	return this->_nickname;
}

std::string	Client::getUsername()
{
	return this->_username;
}

bool	Client::getAuthenticated()
{
	if (this->_password && this->_nickname.size() && this->_username.size())
		return true;
	return false;
}

int	Client::getSocket()
{
	return this->_socket;
}

bool	Client::getHexchat()
{
	return this->_hexchat;
}