/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:52:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:52:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::topic(std::vector<std::string> args, Client *client)
{
	std::string	msg, arg;

    if (!client->isAuthenticated())
        return "";
    else if (args.size() < 2)
        return this->msg461(client, "TOPIC");
    else if (!this->getChannel(args[1]))
        return this->msg403(client, args[1]);
    else if (args.size() == 2)
	{
        if (!this->getChannel(args[1])->getTopic().size())
            return this->msg331(client, args[1]);
        return this->msg332(client, this->getChannel(args[1])) + this->msg333(client, this->getChannel(args[1]));
    }
	else
	{
		if (!this->getChannel(args[1])->getT() && !this->getChannel(args[1])->isOp(client->getNickname()))
			return this->msg482(client, args[1]);
		for (unsigned int i = 2; i < args.size(); i++)
			arg += args[i] + " ";
		arg.erase(arg.size() - 1, 1);
		this->getChannel(args[1])->setTopic(arg);
		msg = this->msgtopic(client, args[1], arg);
		this->sendChannel(args[1], client->getNickname(), msg, false);
	}
    return msg;
}
