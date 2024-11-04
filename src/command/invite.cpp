/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:50:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:50:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string Server::invite(std::vector<std::string> args, Client* client)
{
    Client		*target = this->getClientWithNick(args[1]);
	std::string msg;

    if (!client->isAuthenticated())
        return "";
    else if (args.size() < 3)
        return this->msg461(client, args[0]);
    else if (!target)
        return this->msg401(client, args[1]);
    else if (args[2][0] != '#')
        return this->msg403(client, args[2]);
    else if (this->_channels.find(args[2]) == this->_channels.end())
        return this->msg403(client, args[2]);
    else if (!this->_channels[args[2]]->isOp(client->getNickname()))
        return this->msg482(client, args[2]);
    else if (this->_channels[args[2]]->isMember(target->getNickname()))
        return this->msg443(client, args[1], args[2]);
    this->_channels[args[2]]->addInvited(target->getNickname());
    return this->msginvite(client, args[1], args[2]);
}
