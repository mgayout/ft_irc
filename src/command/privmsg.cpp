/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:27:28 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/22 17:27:28 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::privmsg(std::vector<std::string> arg, Client *client)
{
	std::string	msg = "";

	if (!client->isAuthenticated())
		return "";
	else if (arg.size() < 3)
	for (unsigned int i = 2; i < arg.size(); i++)
		msg += arg[i] + " ";
	if (arg[1][0] == '#')
		return this->privmsgChannel(arg[1], msg, client);
	else
		return this->privmsgClient(arg[1], msg, client);
	return "";
}

std::string	Server::privmsgChannel(std::string channel, std::string msg, Client *client)
{
	Channel	*target = this->getChannel(channel);

	if (!target)
		return "";
	else if (!target->isMember(client->getNickname()))
		return "";
	this->sendChannel(target, this->msgprivmsg(client, channel, msg));
	return "";
}

std::string	Server::privmsgClient(std::string target, std::string message, Client *client)
{
	std::string	msg = this->msgprivmsg(client, target, message);

	if (this->getClientWithNick(target))
		return "";
	send(this->getClientWithNick(target)->getSocket(), msg.c_str(), msg.size(), 0);
	return "";
}
