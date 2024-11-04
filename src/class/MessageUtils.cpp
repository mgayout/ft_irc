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

std::string	Server::msgmodechannel(std::string channelname) //to complete
{
	Channel *channel = this->getChannel(channelname);
	std::string msg;

	if (channel->getI())
		msg += "i";
	if (channel->getT())
		msg += "t";
	if (channel->getPassword().size())
		msg += "k";
	if (channel->getMaxClient())
		msg += "l";
	return msg;
}