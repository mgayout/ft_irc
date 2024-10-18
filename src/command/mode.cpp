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

std::string	Server::mode(std::vector<std::string> arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, "MODE");
	else if (this->getChannel(arg[1]))
		return this->msg403(client, arg[1]);
	else if (arg.size() == 2)
		return (this->msg324(client, arg[1]) + \
				this->msg329(client, this->getChannel(arg[1])));
	return "";
}
