/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:18:12 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/01 14:55:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

int	Server::nicknameUsed(std::string nick)
{
	for (unsigned int i = 1; i != this->_nbClient; i++)
	{
		if (this->_clients[this->_pfds[i].fd]->getNickname() == nick)
			return this->_clients[this->_pfds[i].fd]->getSocket();
	}
	return 0;
}

int	Server::usernameUsed(std::string user)
{
	for (unsigned int i = 1; i != this->_nbClient; i++)
	{
		if (this->_clients[this->_pfds[i].fd]->getUsername() == user)
			return this->_clients[this->_pfds[i].fd]->getSocket();
	}
	return 0;
}
