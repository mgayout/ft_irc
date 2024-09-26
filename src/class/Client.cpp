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

#include "../../include/ft_irc.hpp"

Client::Client() : _socket(0), _op(false)
{

}

Client::Client(int socket) : _socket(socket), _op(false)
{

}

Client& Client::operator=(const Client& other)
{
	if (other._socket)
		this->_socket = other._socket;
	return *this;
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

std::string	Client::getNickname()
{
	return this->_nickname;
}

std::string	Client::getUsername()
{
	return this->_username;
}

int	Client::getSocket()
{
	return this->_socket;
}
