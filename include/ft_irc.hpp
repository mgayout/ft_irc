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

# include <iostream>
# include <algorithm>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>

class	Client
{
	public:
			Client();
			Client(int socket);
			Client&	operator=(const Client& other);
			~Client();

			void		setNickname(const std::string nick);
			void		setUsername(const std::string user);
			std::string	getNickname();
			std::string	getUsername();
			int			getSocket();

	private:
			int			_socket;
			std::string	_nickname;
			std::string	_username;
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

			void	authentication();
			std::string	findNickname(char *buffer);
			std::string	findUsername(char *buffer);
			void	setNickClient(std::string nick);
			void	setUserClient(std::string user);

			int		nicknameUsed(std::string nick);
			int		usernameUsed(std::string user);

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