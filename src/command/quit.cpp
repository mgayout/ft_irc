/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::quit(std::vector<std::string> arg, Client *client)
{
	std::vector<std::string>	tmp;
	int							fd;

	if (arg.size() > 1 && client->isAuthenticated())
		this->sendAll(client->getNickname(), this->msgquit(client, arg));
	tmp = client->getChannel();
	for (unsigned int i = 0; i < tmp.size(); i++)
	{
		this->_channels[tmp[i]]->removeMember(client->getNickname());
		if (!this->_channels[tmp[i]]->getNbClient())
		{
			delete this->_channels[tmp[i]];
			this->_channels.erase(tmp[i]);
		}
	}
	fd = client->getSocket();
	delete this->_clients[fd];
	this->_clients.erase(fd);
	close(fd);
	for (unsigned int i = 1; i < this->_pfds.size(); i++)
		if (this->_pfds[i].fd == fd)
			this->_pfds.erase(this->_pfds.begin() + i);
	if (arg.size())
		this->_nbClient--;
	return "";
}