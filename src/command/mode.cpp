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
	/*if ((args.size() > 3 && (!((args[2][0] == '+' && args[2][0] == 'k') || ((args[2][0] == '+' || args[2][0] == '-') && args[2][1] == 'o') || (args[2][0] == '+' && args[2][0] == 'i')))) || args[2].size() != 2)
		return this->msg421(client, args[0]);*/
	channel = this->getChannel(args[1]);
	if (args[2] == "+i" && args.size() == 3)
		channel->setI(true);
	else if (args[2] == "-i" && args.size() == 3)
	{
		channel->setI(false);
		channel->clearInvited();
	}
	else if (args[2] == "+k" && args.size() == 4)
		channel->setPassword(args[3]);
	else if (args[2] == "-k" && args.size() == 3)
		channel->setPassword("");
	else if (args[2] == "+l" && atoi(args[3].c_str()) > 0 && args.size() == 4)
		channel->setMaxClient(atoi(args[3].c_str()));
	else if (args[2] == "-l" && args.size() == 3)
		channel->setMaxClient(-1);
	else if (args[2] == "+o" && args.size() == 4)
		channel->addOp(args[3]);
	else if (args[2] == "-o" && args.size() == 4)
		channel->removeOp(args[3]);
	else if (args[2] == "+t" && args.size() == 3)
		channel->setT(false);
	else if (args[2] == "-t" && args.size() == 3)
		channel->setT(true);
	else
		return msg472(client, args[2]);
	this->sendChannel(channel->getName(), client->getNickname(), this->msgmode(client, args));
	return this->msgmode(client, args);
}

