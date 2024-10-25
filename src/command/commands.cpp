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

std::string	Server::op(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	
	std::cout << "op \"" << arg[1] << "\"\n";
	return "";
}

std::string	Server::deop(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	
	std::cout << "deop \"" << arg[1] << "\"\n";
	return "";
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
