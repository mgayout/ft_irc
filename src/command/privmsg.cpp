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

std::string	Server::privmsg(std::vector<std::string> args, Client *client)
{
	std::string	msg = "";

	for (unsigned int i = 0; i < args.size(); i++)
		std::cout << "arg[" << i << "] = " << args[i] << std::endl;
	if (!client->isAuthenticated())
		return "";
	else if (args.size() < 3)
	for (unsigned int i = 2; i < args.size(); i++)
		msg += args[i] + " ";
	if (args[1][0] == '#')
		return this->privmsgChannel(args[1], msg, client);
	else
		return this->privmsgClient(args[1], msg, client);
	return "";
}

std::string	Server::privmsgChannel(std::string channel, std::string msg, Client *client)
{
	Channel	*target = this->getChannel(channel);

	if (!target)
		return "";
	else if (!target->isMember(client->getNickname()))
		return "";
	this->sendChannel(channel, client->getNickname(), this->msgprivmsg(client, channel, msg));
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
