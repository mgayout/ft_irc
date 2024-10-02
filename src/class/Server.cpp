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

#include "../../include/Server.hpp"

Server::Server(char **argv)
{
	this->_port = std::atoi(argv[1]);
	this->_password = argv[2];
	this->_nbClient = 1;
	this->_nbClientMax = 5;
	this->_socket = getSocket();
	this->_pfdstmp.fd = this->_socket;
	this->_pfdstmp.events = POLLIN;
	this->_pfds.push_back(this->_pfdstmp);
}

Server::~Server()
{
	close(this->_socket);
}

int	Server::getSocket()
{
	struct sockaddr_in	sockstruct;
	int	sock, opt = 1;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		std::cout << "Error: fail to create socket" << std::endl;
		exit(-1);
	}
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		std::cout << "Error: fail to attach socket" << std::endl;
		exit(-1);
	}
	sockstruct.sin_family = AF_INET;
	sockstruct.sin_addr.s_addr = INADDR_ANY;
	sockstruct.sin_port = htons(this->_port);
	if (bind(sock, (struct sockaddr *)&sockstruct, sizeof(sockstruct)) < 0)
	{
		std::cout << "Error: fail to connect" << std::endl;
		exit(-1);
	}
	if (listen(sock, this->_nbClientMax) < 0)
	{
		std::cout << "Error: fail to listen" << std::endl;
		exit(-1);
	}
	//std::cout << "[Server] Waiting for connections on port " << this->_port << "..." << std::endl;

	return sock;
}

void	Server::launching()
{
	while (1)
	{
		int	poll_count = poll(this->_pfds.data(), this->_pfds.size(), -1);
		if (poll_count == -1)
			throw (Server::pollException());
		for (unsigned int i = 0; i < this->_pfds.size(); i++)
		{
			//std::cout << i << std::endl;
			if (!this->_pfds[i].revents)
				continue;
			if (!(this->_pfds[i].revents & POLLIN))
				continue;
			if (this->_pfds[i].fd == this->_socket)
				this->addClient();
			else
				this->clientRequest(i);
			break;
		}
	}
}

void	Server::addClient()
{
	struct sockaddr_storage	sockstruct;
	int						clientFd;
	socklen_t				structlen = sizeof(sockstruct);

	if (this->_nbClient == this->_nbClientMax)
		std::cout << "Error: can't accept new client because server is full" << std::endl;
	else if ((clientFd = accept(this->_socket, (struct sockaddr*)&sockstruct, &structlen)) == -1)
		std::cout << "Error: fail to accept new client" << std::endl;
	else
	{
		this->_pfdstmp.fd = clientFd;
		this->_pfds.push_back(this->_pfdstmp);
		this->_clients.insert(std::pair<int, Client *>(clientFd, new Client(clientFd)));
		std::cout << "[Server] New client has been add" << std::endl;
		sendMessage(clientFd, "Welcome to ft_irc\n");
		this->_nbClient++;
	}
}

void	Server::clientRequest(unsigned int idClient)
{
	std::string	msg, line;
	int			clientFd = this->_pfds[idClient].fd;
	char		buffer[1024] = {0};
	int			bytes_received, end, lines = 0;

	bytes_received = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytes_received > 0)
	{
		buffer[bytes_received] = '\0';
		msg = buffer;
		for (int i = 0; i != bytes_received; i++)
			if (msg[i] == '\n')
				lines++;
		while (lines)
		{
			if (this->_clients[clientFd]->getHexchat())
			{
				end = msg.find('\n');
				line = msg.substr(0, end - 1);
			}
			else
			{
				end = msg.find('\n');
				line = msg.substr(0, end);
			}
			//std::cout << line << std::endl;
			this->parseCommand(clientFd, line);
			msg = msg.substr(end + 1, msg.size() - (end + 1));
			lines--;
		}
	}
	else if (bytes_received <= 0)
		this->quit(clientFd);

}

void	Server::parseCommand(int clientFd, std::string line)
{
	std::string	commands[17] = {"JOIN", "PART", "KICK", "INVITE", "TOPIC", "MODE", "CAP", "PASS", "NICK", "USER", "OP", "DEOP", "MSG", "QUIT", "SENDFILE", "GETFILE", "BOT"};
	std::string	command, arg;
	int			i = -1;
	int			space;

	if ((space = line.find(' ')) > 0)
	{
		command = line.substr(0, space);
		arg = line.substr(space + 1, line.size() - (space + 1));
	}
	else
		command = line;
	//std::cout << command << " et " << arg << std::endl;
	while (++i < 18)
		if (command == commands[i])
			break ;
	switch (i)
	{
	case 0:
			this->join(arg, clientFd);
			break;
	case 1:
			this->part(arg, clientFd);
			break;
	case 2:
			this->kick(arg, clientFd);
			break;
	case 3:
			this->invite(arg, clientFd);
			break;
	case 4:
			this->topic(arg, clientFd);
			break;
	case 5:
			this->mode(arg, clientFd);
			break;
	case 6:
			this->cap(clientFd);
			break;
	case 7:
			this->pass(arg, clientFd);
			break;
	case 8:
			this->nick(arg, clientFd);
			break;
	case 9:
			this->user(arg, clientFd);
			break;
	case 10:
			this->op(arg, clientFd);
			break;
	case 11:
			this->deop(arg, clientFd);
			break;
	case 12:
			this->msg(arg, clientFd);
			break;
	case 13:
			this->quit(clientFd);
			break;
	case 14:
			this->sendfile(arg, clientFd);
			break;
	case 15:
			this->getfile(arg, clientFd);
			break;
	case 16:
			this->bot(arg, clientFd);
			break;
	default:
			sendMessage(clientFd, "Nothing\n");
			break;
	}
}
