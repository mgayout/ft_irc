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
	std::vector<std::string>	channel, password;
	std::string					msg;

	if (!client->isAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, arg[0]);
	channel = split(arg[1], ',');
	if (arg.size() > 2)
		password = split(arg[2], ',');
	else
		password.push_back("");
	for (unsigned int i = 0; i < channel.size(); i++)
	{
		if (password.size() < i)
			password.push_back("");
		if (channel[i][0] != '#')
		{
			msg += this->msg476(client, channel[i]);
			continue;
		}
		else if (!this->getChannel(channel[i]))
			msg += this->createChannel(channel[i], password[i], client);
		else
			msg += this->joinChannel(channel[i], password[i], client);
		if (this->_channels[channel[i]] && this->_channels[channel[i]]->getTopic() != "")
			msg += this->msg332(client, this->_channels[channel[i]]) + this->msg333(client, this->_channels[channel[i]]);
		msg += this->msg353(client, channel[i]) + this->msg366(client, channel[i]);
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
	this->sendChannel(channel, this->msgjoin(client, channelname));
	channel->addMember(client->getNickname());
	channel->removeInvited(client->getNickname());
	client->addChannel(channelname);
	return (this->msgjoin(client, channelname) + msg);
}
