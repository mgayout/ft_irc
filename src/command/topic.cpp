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

std::string	Server::topic(std::vector<std::string> arg, Client *client)
{
	if (!client->getAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, "TOPIC");
	return "";
}
