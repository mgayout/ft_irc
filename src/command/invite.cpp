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

std::string	Server::invite(std::vector<std::string> arg, Client *client)
{
	if (!client->isAuthenticated())
		return "";
	else if (arg.size() == 1)
		return this->msg461(client, "INVITE");
	return "";
}
