/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:39:51 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 11:39:51 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_irc.hpp"

Server::Server(char **argv) : _nbClient(0), _port(std::atoi(argv[1])), _password(argv[2]), _socket(0) , structSize(sizeof(this->_sockstruct))
{

}

Server::~Server()
{

}

void	Server::startServer()
{
	int	opt = 1;

	if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "Error: fail to create socket" << std::endl;
		return;
	}
	if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		std::cout << "Error: fail to attach socket" << std::endl;
		return;
	}
	this->_sockstruct.sin_family = AF_INET;
	this->_sockstruct.sin_addr.s_addr = INADDR_ANY;
	this->_sockstruct.sin_port = htons(this->_port);
	if (bind(this->_socket, (struct sockaddr *)&this->_sockstruct, sizeof(this->_sockstruct)) < 0)
	{
		std::cout << "Error: fail to connect" << std::endl;
		return;
	}
	if (listen(this->_socket, 5) < 0)
	{
		std::cout << "Error: fail to listen" << std::endl;
		return;
	}
	std::cout << "Serveur en attente de connexions sur le port " << this->_port << "..." << std::endl;
}

void	Server::waitingClients()
{
	int socket;

	while (1)
	{
		if ((socket = accept(this->_socket, (struct sockaddr *)&this->_sockstruct, (socklen_t*)&this->structSize)) < 0)
			std::cout << "Error: fail to accept new client" << std::endl;
		else
		{
			std::cout << "[Server] new client has been add" << std::endl;
			this->_clients[_nbClient] = new Client(socket);
			this->_nbClient++;
		}
	}
}

void	Server::closeServer()
{
	close(this->_socket);
}