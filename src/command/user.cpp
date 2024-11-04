/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:46 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/18 10:51:46 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::user(std::vector<std::string> arg, Client *client)
{
	if (!client->getPwd())
		return this->msg451(client, arg[0]);
	if (arg[1].size() != 5)
	{
		if (client->isAuthenticated())
			return this->msg462(client);
		client->setUsername(arg[1]);
		client->setRealname(arg[4]);
		client->setUser(true);
		client->setReal(true);
		if (client->isAuthenticated())
			return (this->msg001(client) + \
					this->msg002(client) + \
					this->msg003(client) + \
					this->msg004(client));
	}
	else
		return this->msg461(client, arg[0]);
	return "";
}
