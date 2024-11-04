/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:42:54 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 17:42:54 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"


std::string	Server::cap(Client *client)
{
	client->setHexchat(true);
	return "";
}

std::string	Server::who(std::vector<std::string> arg, Client *client)
{
	std::string	msg;

	if (!client->isAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, arg[0]);
	else if (arg[1][0] == '#')
	{
		if (!this->getChannel(arg[1]))
			msg = this->msg403(client, arg[1]);
		else
			msg = this->msg352(client, arg[1]) + this->msg315(client, arg[1]);
	}
	else
	{
		if (!this->nicknameUsed(arg[1]))
			msg = this->msg401(client, arg[1]);
		else
			msg = this->msg352(client, arg[1]) + this->msg315(client, arg[1]);
	}
	return msg;
}

std::string	Server::sendfile(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	
	std::cout << "sendfile \"" << arg[1] << "\"\n";
	return "";
}

std::string	Server::getfile(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	
	std::cout << "getfile \"" << arg[1] << "\"\n";
	return "";
}

std::string	Server::bot(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	
	std::cout << "bot \"" << arg[1] << "\"\n";
	return "";
}
