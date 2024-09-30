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

void	Server::oper(std::string arg, int clientFd)
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

void	Server::quit(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::join(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::part(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::topic(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::kick(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::privmsg(std::string arg, int clientFd)
{
	if (arg != this->_password)
		std::cout << "bad mdp" << std::endl;
	else
		this->_clients[clientFd]->setAuthenticated(true);
}

void	Server::notice(std::string arg, int clientFd)
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

void	Server::cap(int clientFd)
{
	this->_clients[clientFd]->setHexchat(true);
	std::cout << "hexchat" << std::endl;
}
