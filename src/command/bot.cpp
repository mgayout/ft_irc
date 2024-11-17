/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:54:05 by mgayout           #+#    #+#             */
/*   Updated: 2024/11/17 18:06:42 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::bot(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	else if (arg.size() != 2)
		return ""/*this->msgBot(client)*/;
	else if (!this->getChannel(arg[1]))
		return ""/*this->msgBot(client)*/;
	this->sendChannel(arg[1], client->getNickname(), "SHIFUMI ?\r\n", false);
	this->setBot(true);
	return "";
}