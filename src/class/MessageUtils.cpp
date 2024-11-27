/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:33:35 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 13:33:35 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::getUserPrefix(Client *client) {
	std::string	prefix = ":" + client->getNickname() + "!" + client->getUsername() + "@" + this->getHostname() + " ";
	return prefix;
}

std::string	Server::getServerPrefix(Client *client, std::string code) {
	std::string	prefix = ":" + this->getHostname() + " " + code + " " + client->getNickname() + " ";
	return prefix;
}

std::string	Server::msgclientschannel(std::string channel)
{
	Channel	*tmp = this->getChannel(channel);
	std::string msg;

	for (unsigned int i = 0; i < tmp->getMembers().size(); i++)
	{
		if (tmp->isOp(tmp->getMembers()[i]))
			msg += "@" + tmp->getMembers()[i];
		else
			msg += " " + tmp->getMembers()[i];
	}
	return msg;
}

std::string	Server::msgmodechannel(std::string channelname)
{
	Channel *channel = this->getChannel(channelname);
	std::string mode = " +", arg = "";

	if (channel->getI())
		mode += "i";
	if (channel->getT())
		mode += "t";
	if (channel->getPassword().size())
	{
		mode += "k";
		arg += channel->getPassword();
	}
	if (channel->getMaxClient())
	{
		mode += "l";
		if (arg.size())
			arg += " ";
		arg += channel->getMaxClient();
	}
	if (mode.size() == 2)
		return "";
	if (!arg.size())
		return mode;
	return mode + " " + arg;
}