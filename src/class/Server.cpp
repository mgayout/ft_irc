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

Server::Server(char *hostname, int port, std::string pwd)
{
	this->_hostname = hostname;
	this->_port = port;
	this->_password = pwd;
	this->_version = "ft_irc-1.0";
	this->_date = getCurrentDate();
	this->_nbClient = 1;
	this->_nbClientMax = 5;
	this->createSocket();
	this->_pfdstmp.fd = this->_socket;
	this->_pfdstmp.events = POLLIN;
	this->_pfds.push_back(this->_pfdstmp);
	this->launching();
	this->closeServer();
}

Server::~Server()
{

}

void	Server::createSocket()
{
	int	opt = 1;

	if ((this->_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
		throw (Server::SocketCreationError());
	std::memset(&this->_sockstruct, 0, sizeof(this->_sockstruct));
	this->_sockstruct.sin_family = AF_INET;
	this->_sockstruct.sin_addr.s_addr = INADDR_ANY;
	this->_sockstruct.sin_port = htons(this->getPort());
	if (setsockopt(this->getSocket(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw (Server::SocketSetsockoptError());
	if (bind(this->getSocket(), (struct sockaddr *)&this->_sockstruct, sizeof(this->_sockstruct)) < 0)
		throw (Server::SocketBindError());
	if (listen(this->getSocket(), this->getNbClientMax()) < 0)
		throw (Server::SocketListenError());
}

void	Server::launching()
{
	std::cout << "[Server] Waiting for connections on port " << this->getPort() << "..." << std::endl;

	while (!ctrl)
	{
		if (poll(this->_pfds.data(), this->_pfds.size(), -1) == -1 && !ctrl)
			throw (Server::pollException());
		for (unsigned int i = 0; i < this->_pfds.size() && !ctrl; i++)
		{
			if (!this->_pfds[i].revents)
				continue;
			if (!(this->_pfds[i].revents & POLLIN))
				continue;
			if (this->_pfds[i].fd == this->getSocket())
				this->addClient();
			else
				this->clientRequest(i);
			break;
		}
	}
}

void	Server::addClient()
{
	struct sockaddr_in		sockstruct;
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
		this->_clients.insert(std::pair<int, Client *>(clientFd, new Client(clientFd, sockstruct)));
		std::cout << "[Server] New client has been add" << std::endl;
		this->_nbClient++;
	}
}

void	Server::clientRequest(unsigned int idClient)
{
	std::vector<std::string>	cmd;
	std::string					msg, buf;
	int							clientFd = this->getPollfd(idClient);
	char						buffer[1024];
	int							bytes_received;

	bytes_received = recv(clientFd, buffer, sizeof(buffer), 0);
    if (bytes_received == 0)
    {
        std::cout << "[Server] Client disconnected" << std::endl;
        close(clientFd);
        _clients.erase(clientFd);
    }  
	else if (bytes_received)
	{
		buffer[bytes_received] = '\0';
		buf = buffer;
		//buf.erase(std::remove(buf.begin(), buf.end(), '\r'), buf.end());
		cmd = split(buffer, '\n', this->_clients[clientFd]->getHexchat());
		for (unsigned int i = 0; i < cmd.size(); i++)
		{
			std::cout << "cmd[" << i << "] = " << cmd[i] << std::endl;
			msg = this->commands(split(cmd[i], ' ', this->_clients[clientFd]->getHexchat()), clientFd);
			if (msg.size())
				send(clientFd, msg.c_str(), msg.size(), 0);
			std::cout << msg << std::endl;
		}
	}
	else
		throw (Server::RecvError());
}

std::string	Server::commands(std::vector<std::string> buffer, int clientFd)
{
	std::string	commands[18] = {"JOIN", "PART", "KICK", "INVITE", "TOPIC", "MODE", "CAP", "PASS", "NICK", "USER", "PRIVMSG", "privmsg", "QUIT", "WHO", "WHOIS", "SENDFILE", "GETFILE", "BOT"};
	int			i = -1;

	for (unsigned int j = 0; j < buffer.size(); j++)
		std::cout << "buffer[" << j << "] = " << buffer[j] << " et size = " << buffer[j].size() << std::endl;
	while (++i < 19)
		if (buffer[0] == commands[i])
			break ;
	switch (i)
	{
	case 0:
			return this->join(buffer, this->_clients[clientFd]);
	case 1:
			return this->part(buffer, this->_clients[clientFd]);
	case 2:
			return this->kick(buffer, this->_clients[clientFd]);
	case 3:
			return this->invite(buffer, this->_clients[clientFd]);
	case 4:
			return this->topic(buffer, this->_clients[clientFd]);
	case 5:
			return this->mode(buffer, this->_clients[clientFd]);
	case 6:
			return this->cap(this->_clients[clientFd]);
	case 7:
			return this->pass(buffer, this->_clients[clientFd]);
	case 8:
			return this->nick(buffer, this->_clients[clientFd]);
	case 9:
			return this->user(buffer, this->_clients[clientFd]);
	case 10:
			return this->privmsg(buffer, this->_clients[clientFd], false);
	case 11:
			return this->privmsg(buffer, this->_clients[clientFd], true);
	case 12:
			return this->quit(buffer, this->_clients[clientFd]);
	case 13:
			return this->who(buffer, this->_clients[clientFd]);
	case 14:
			return this->whois(buffer, this->_clients[clientFd]);
	case 15:
			return this->sendfile(buffer, this->_clients[clientFd]);
	case 16:
			return this->getfile(buffer, this->_clients[clientFd]);
	case 17:
			return this->bot(buffer, this->_clients[clientFd]);
	default:
			return "";
	}
	return "";
}

void	Server::closeServer()
{
	std::vector<std::string> null;

	for (unsigned int i = 1; i < this->getNbClient(); i++)
		this->quit(null, this->_clients[this->_pfds[i].fd]);
	this->_pfds.erase(this->_pfds.begin());
	close(this->getSocket());
	shutdown(this->getSocket(), SHUT_RDWR);
	std::cout << "\nBye !" << std::endl;
}