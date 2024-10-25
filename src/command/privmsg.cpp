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
	if (!this->getChannel(channel))
		return "";
	else if (!client->isConnected(channel))
		return "";
	this->sendChannel(this->getChannel(channel), this->msgprivmsg(client, channel, msg));
	return "";
}

std::string	Server::privmsgClient(std::string target, std::string msg, Client *client)
{
	if (!this->usernameUsed(target))
		return "";
	this->sendClient(this->getClientWithName(target), this->msgprivmsg(client, target, msg));
	return "";
}
