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

	if (!client->isAuthenticated())
		return "";
	else if (arg.size() > 1)
		this->sendAll(client->getUsername(), this->msgquit(client, arg));
	tmp = client->getChannel();
	for (unsigned int i = 0; i < tmp.size(); i++)
	{
		this->_channels[tmp[i]]->removeClient(client->getUsername());
		if (!this->_channels[tmp[i]]->getNbClient())
		{
			std::cout << "salut" << std::endl;
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
	this->_nbClient--;
	return "";
}