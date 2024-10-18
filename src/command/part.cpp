/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:50:45 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:50:45 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::part(std::vector<std::string> arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i].at(0) != '#') 
		{
			//sendMessage(clientFd, "ERR_NOSUCHCHANNEL: Invalid channel name\n");
			continue;
		}
		/*if (arg[i].find(" :") != std::string::npos)
			partReason(arg[i], client);
		else
			partDefault(arg[i], client);*/
	}
	return "";
}

/*std::string	Server::partReason(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string reason = arg.substr(arg.find(" ") + 1);
	std::string msg = client->getNickname() + " has left " + channelName +"(" + reason + ")";

	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[channelName]->removeMember(client);
		this->_channels[channelName]->SendMessChan(msg, client);
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}

std::string	Server::partDefault(std::string arg, Client *client)
{
	std::string msg = client->getNickname() + " has left " + arg;
	if(this->_channels.find(arg) != this->_channels.end())
	{
		this->_channels[arg]->removeMember(client);
		_channels[arg]->SendMessChan(msg, client);
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}*/