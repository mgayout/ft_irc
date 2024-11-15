/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:48:08 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:48:08 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::join(std::vector<std::string> arg, Client *client)
{
	std::vector<std::string>	args = split(arg[1], ',');
	std::string					channel, password, msg;

	if (!client->isAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, arg[0]);
	while (args.size())
	{
		channel = args[0];
		args.erase(args.begin());
		password = "";
		if (args.size() && args[0][0] != '#')
		{
			password = args[0];
			args.erase(args.begin());
		}
		if (channel[0] != '#')
		{
			msg += this->msg476(client, channel);
			continue;
		}
		else if (!this->getChannel(channel))
			msg += this->createChannel(channel, password, client);
		else
			msg += this->joinChannel(channel, password, client);
		if (!this->getChannel(channel)->isMember(client->getNickname()))
			continue;
		if (this->_channels[channel] && this->_channels[channel]->getTopic() != "")
			msg += this->msg332(client, this->_channels[channel]) + this->msg333(client, this->_channels[channel]);
		msg += this->msg353(client, channel) + this->msg366(client, channel);
	}
	return msg;
}

std::string	Server::createChannel(std::string channel, std::string password, Client *client)
{
	this->_channels[channel] = new Channel(client, channel, password);
	client->addChannel(channel);
	return (this->msgjoin(client, channel) + \
			this->msgjoinop(client, channel));
}

std::string	Server::joinChannel(std::string channelname, std::string password, Client *client)
{
	Channel	*channel = this->getChannel(channelname);
	std::string	msg = "";

	if (channel->getI() && !channel->isInvited(client->getNickname()))
		return this->msg473(client, channelname);
	else if (channel->getPassword() != password)
		return this->msg475(client, channelname);
	else if (channel->getMaxClient() && channel->getMembers().size() >= channel->getMaxClient())
		return this->msg471(client, channelname);
	if (channel->getTopic().size())
		msg = this->msg332(client, channel) + this->msg333(client, channel);
	this->sendChannel(channelname, client->getNickname(), this->msgjoin(client, channelname), false);
	channel->addMember(client->getNickname());
	channel->removeInvited(client->getNickname());
	client->addChannel(channelname);
	return (this->msgjoin(client, channelname) + msg);
}
