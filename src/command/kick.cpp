/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:01 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:01 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::kick(std::vector<std::string> args, Client* client)
{
	std::string	msg;

    if (!client->isAuthenticated())
        return "";
    else if (args.size() < 3)
        return this->msg461(client, args[0]);
	else if (!this->getChannel(args[1]))
		return this->msg403(client, args[1]);
    else if (!this->getChannel(args[1])->isOp(client->getNickname()))
        return this->msg482(client, args[1]);
    else if (!this->getChannel(args[1])->isMember(args[2])) {
        return this->msg441(client, args[2], args[1]);}
	msg = this->msgkick(client, args);
	this->sendChannel(args[1], client->getNickname(), msg, false);
	this->_channels[args[1]]->clearClient(args[2]);
	this->getClientWithNick(args[2])->removeChannel(args[1]);
    return msg;
}
