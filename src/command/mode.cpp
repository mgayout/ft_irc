/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:18 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:18 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::mode(std::vector<std::string> args, Client *client)
{
    Channel		*channel;
	std::string	msg = "";

	if (!client->isAuthenticated())
        return "";
    else if (args.size() == 1)
        return msg461(client, args[0]);
	else if (!this->getChannel(args[1]))
		return msg403(client, args[0]);
	else if (args.size() == 2)
		return this->msg324(client, args[1]) + this->msg329(client, this->getChannel(args[1]));
	else if (!this->getChannel(args[1])->isOp(client->getNickname()))
		return this->msg482(client, args[1]);
	else if ((args.size() > 3 && (!((args[2][0] == '+' && args[2][0] == 'k') || ((args[2][0] == '+' || args[2][0] == '-') && args[2][1] == 'o') || (args[2][0] == '+' && args[2][0] == 'i')))) || args[2].size() != 2)
		return this->msg421(client, args[0]);
	
	channel = this->getChannel(args[1]);
	if (args[2] == "+i")
		channel->setI(true);
	else if (args[2] == "-i")
	{
		channel->setI(false);
		channel->clearInvited();
	}
	else if (args[2] == "+k")
		channel->setPassword(args[3]);
	else if (args[2] == "-k")
		channel->setPassword("");
	else if (args[2] == "+l" && atoi(args[3].c_str()) > 0)
		channel->setMaxClient(atoi(args[3].c_str()));
	else if (args[2] == "-l")
		channel->setMaxClient(-1);
	else if (args[2] == "+o")
		channel->addOp(args[3]);
	else if (args[2] == "-o")
		channel->removeOp(args[3]);
	else if (args[2] == "+t")
		channel->setT(false);
	else if (args[2] == "-t")
		channel->setT(true);
	else
		return msg472(client, args[2]);
	msg = this->msgmode(client, args);
	this->sendChannel(channel, msg);
	return msg;
}

