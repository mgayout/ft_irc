/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:38:17 by mgayout           #+#    #+#             */
/*   Updated: 2024/11/21 17:38:17 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::ping(std::vector<std::string> arg, Client* client)
{
	std::string	message, msg;

	if (!client->isAuthenticated())
        return "";
    msg = this->msgping(client, arg[1]);
    send(client->getSocket(), msg.c_str(), msg.size(), 0);
	return "";
}