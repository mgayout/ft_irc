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

std::string	Server::part(std::vector<std::string> args, Client *client)
{
	Channel	*target;
	std::vector<std::string>	channel;
	std::string					message = "", msg = "";

	if (!client->isAuthenticated())
		return "";
	else if (args.size() == 1)
		return this->msg461(client, args[0]);
	channel = split(args[1], ',');
	for (unsigned int i = 2; i < args.size(); i++)
		message += args[i] + " "; //erase last " ";
	for (unsigned int i = 0; i < channel.size(); i++)
	{
		target = this->getChannel(channel[i]);
		if (!target)
		{
			msg += this->msg476(client, channel[i]);
			continue;
		}
		else if (!target->isMember(client->getNickname()))
		{
			msg += this->msg476(client, channel[i]); //change 442 
			continue;
		}
		msg += this->msgpart(client, channel[i], message);
		if (target->getMembers().size() == 1)
		{
			target->clearAll();
			client->removeChannel(target->getName());
			this->removeChannel(target->getName());
		}
		else
		{
			target->clearClient(client->getNickname());
			client->removeChannel(target->getName());
			this->sendChannel(target, msg);
		}
	}
	return msg;
}
