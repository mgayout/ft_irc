/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:15:19 by mgayout           #+#    #+#             */
/*   Updated: 2024/11/21 17:15:19 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string    Server::notice(std::vector<std::string> arg, Client *client)
{
    if (!client->isAuthenticated())
        return "";
    if (arg[1][0] != ':')
        return "";
    if (arg[1] == ":PING")
		return this->ping(arg, client);
    return "";
}