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

std::string	Server::privmsg(std::vector<std::string> args, Client *client, bool sendme)
{
	std::string	msg = "";

	if (!client->isAuthenticated())
		return "";
	for (unsigned int i = 2; i < args.size(); i++)
		msg += args[i] + " ";
	if (msg[0] != ':')
		msg = "";
	if (args[1][0] == '#')
		return this->privmsgChannel(args[1], msg, client, sendme);
	else
		return this->privmsgClient(args[1], msg, client);
	return "";
}

std::string	Server::privmsgChannel(std::string channel, std::string msg, Client *client, bool sendme)
{
	Channel	*target = this->getChannel(channel);

	if (!target)
		return "";
	else if (!target->isMember(client->getNickname()))
		return "";
	this->sendChannel(channel, client->getNickname(), this->msgprivmsg(client, channel, msg), sendme);
	return "";
}

std::string	Server::privmsgClient(std::string target, std::string message, Client *client)
{
	std::string	msg = this->msgprivmsg(client, target, message);

	if (!this->getClientWithNick(target))
		return "";
	send(this->getClientWithNick(target)->getSocket(), msg.c_str(), msg.size(), 0);
	return "";
}
