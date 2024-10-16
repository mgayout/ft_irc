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

std::string	Server::msg433(Client *client, std::string nickname) {
	std::string	msg = this->getServerPrefix(client, "433") + " " + nickname + " :Nickname is already use" + "\r\n";
	return msg;
}

std::string	Server::msg461(Client *client, std::string command) {
	std::string	msg = this->getServerPrefix(client, "461") + command + " :Not enough parameters" + "\r\n";
	return msg;
}

std::string	Server::msg462(Client *client) {
	std::string	msg = this->getServerPrefix(client, "462") + ":You may not reregister" + "\r\n";
	return msg;
}

std::string	Server::msg464(Client *client) {
	std::string	msg = this->getServerPrefix(client, "464") + ":Password incorrect" + "\r\n";
	return msg;
}
