/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::kick(std::vector<std::string> arg, Client *client)
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
			kickReason(arg[i], client);
		else
			kickDefault(arg[i], client);*/
	}
	return "";
}

/*std::string	Server::kickReason(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string nickname = arg.substr(arg.find(" ") + 1, arg.find(" :") - (arg.find(" ") + 1));
	std::string reason = arg.substr(arg.find(" :") + 2);

	if (this->_channels.find(channelName) != this->_channels.end())
	{
		Channel* channel = this->_channels[channelName];

		if (channel->isOP(client))
		{
			Client* targetClient = findClient(nickname);
			if (targetClient && this->_channels[channelName]->isMember(targetClient))
			{
				channel->removeMember(targetClient);
				channel->SendMessChan(nickname + " has been kicked by " + client->getNickname() + " (" + reason + ")\n", client);
				sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + client->getNickname() + "\n");
			}
			else
			{
				sendMessage(client->getSocket(), "ERR_USERNOTINCHANNEL: User is not in the channel\n");
			}
		}
		else
			sendMessage(client->getSocket(), "ERR_CHANOPRIVSNEEDED: You're not channel operator\n");
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}

std::string	Server::kickDefault(std::string arg, Client *client)
{
	std::string channelName = arg.substr(0, arg.find(" "));
	std::string nickname = arg.substr(arg.find(" ") + 1);

	if (this->_channels.find(channelName) != this->_channels.end())
	{
		Channel* channel = this->_channels[channelName];

		if (channel->isOP(client))
		{
			Client* targetClient = findClient(nickname);
			if (targetClient && channel->isMember(targetClient))
			{
				channel->removeMember(targetClient);
				//channel->SendMessChan(nickname + " has been kicked by " + this->_clients[clientFd]->getNickname(), this->_clients[clientFd] + "\n");
				sendMessage(targetClient->getSocket(), "You have been kicked from " + channelName + " by " + client->getNickname() + "\n");
			}
			else
			{
				sendMessage(client->getSocket(), "ERR_USERNOTINCHANNEL: User is not in the channel\n");
			}
		}
		else
			sendMessage(client->getSocket(), "ERR_CHANOPRIVSNEEDED: You're not channel operator\n");
	}
	else
		sendMessage(client->getSocket(), "ERR_NOSUCHCHANNEL: Invalid channel name\n");
	return "";
}*/