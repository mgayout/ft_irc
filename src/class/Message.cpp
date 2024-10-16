/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:03:24 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:03:24 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"

std::string	Server::msg001(Client *client) {
	std::string	msg = this->getServerPrefix(client, "001") + "Welcome to the ft_irc " + client->getNickname() + "\r\n";
	return msg;
}

std::string	Server::msg002(Client *client) {
	std::string	msg = this->getServerPrefix(client, "002") + ":Your host is " + this->getHostname() + ", running version " + this->getVersion() + "\r\n";
	return msg;
}

std::string	Server::msg003(Client *client) {
	std::string	msg = this->getServerPrefix(client, "003") + ":This server was created " + this->getDate() + "\r\n";
	return msg;
}

std::string	Server::msg004(Client *client) {
	std::string	msg = this->getServerPrefix(client, "004") + this->getHostname() + " " + this->getVersion() + " 0 itkol" + "\r\n";
	return msg;
}