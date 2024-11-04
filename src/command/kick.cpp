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
	Client		*target = this->getClientWithNick(args[2]);
    std::string msg;

    if (!client->isAuthenticated())
        return "";
    else if (args.size() < 3)
        return this->msg461(client, args[0]);

    std::string reason = args.size() > 3 ? args[3] : "";

    if (args[1][0] != '#')
        return this->msg403(client, args[1]);
    else if (this->_channels.find(args[1]) == this->_channels.end())
        return this->msg403(client, args[1]);
    else if (!this->_channels[args[1]]->isOp(client->getNickname()))
        return this->msg482(client, args[1]);
    else if (!target || !this->_channels[args[1]]->isMember(target->getNickname()))
        return this->msg441(client, args[2], args[1]);

    this->_channels[args[1]]->removeMember(target->getNickname());
    msg += ":" + client->getNickname() + " KICK " + args[1] + " " + args[2];
    if (!reason.empty()) {
        msg += " :" + reason;
    }
    msg += "\r\n";

    return msg;
}
