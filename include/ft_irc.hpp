/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:20:07 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/25 11:20:07 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

#include <iostream>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

class	Client
{
	public:
			Client();
			Client(int socket);
			Client&	operator=(const Client& other);
			~Client();

	private:
			int			_socket;
			std::string	_name;
			bool		_op;
};

class	Server
{
	public:
			Server(char **argv);
			~Server();

			void	startServer();
			void	waitingClients();
			void	closeServer();

	private:
			Client*				_clients[1024];
			unsigned int		_nbClient;
			unsigned int		_port;
			std::string			_password;
			int					_socket;
			struct sockaddr_in	_sockstruct;
			int					structSize;
};

int		parse(char *arg);

#endif