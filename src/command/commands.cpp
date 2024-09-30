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

void	Server::join(std::string arg, int clientFd)
{
	std::string	msg = "New channel has been created : " + arg + "\n";
	
	std::cout << "New channel has been created : " << arg << "\n";
	sendMessage(clientFd, msg);
}

void	Server::part(std::string arg, int clientFd)
{
	std::string	msg = "A client left channel \"" + arg + "\"\n";
	
	std::cout << "A client left channel \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::kick(std::string arg, int clientFd)
{
	std::string	msg = "A client was kicked out from channel \"" + arg + "\"\n";
	
	std::cout << "A client was kicked out from channel \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::invite(std::string arg, int clientFd)
{
	std::string	msg = "A client invited someone on channel \"" + arg + "\"\n";
	
	std::cout << "A client was kicked out from channel \"" << arg << "\"\n";
	sendMessage(clientFd, msg);
}

void	Server::topic(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::mode(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::cap(int clientFd)
{
	this->_clients[clientFd]->setHexchat(true);
	std::cout << "hexchat" << std::endl;
}

void	Server::pass(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::nick(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::user(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::op(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::deop(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::msg(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::quit(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::sendfile(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::getfile(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::bot(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}
