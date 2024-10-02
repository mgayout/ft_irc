/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 09:29:49 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 09:29:49 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <algorithm>
# include <sys/socket.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <vector>
# include <map>
# include <stdlib.h>

# include "Client.hpp"

class Client;

class	Server
{
	public:
			Server(char **argv);
			~Server();

			int		getSocket();
			void	launching();
			void	addClient();
			void	clientRequest(unsigned int idClient);
			void	parseCommand(int clientFd, std::string line);

			void		join(std::string arg, int clientFd);
			void		part(std::string arg, int clientFd);
			void		kick(std::string arg, int clientFd);
			void		invite(std::string arg, int clientFd);
			void		topic(std::string arg, int clientFd);
			void		mode(std::string arg, int clientFd);
			void		cap(int clientFd);
			void		pass(std::string arg, int clientFd);
			void		nick(std::string arg, int clientFd);
			void		user(std::string arg, int clientFd);
			void		op(std::string arg, int clientFd);
			void		deop(std::string arg, int clientFd);
			void		msg(std::string arg, int clientFd);
			void		quit(int clientFd);
			void		sendfile(std::string arg, int clientFd);
			void		getfile(std::string arg, int clientFd);
			void		bot(std::string arg, int clientFd);
			
			void		sendMessage(int clienFd, std::string msg);

			/*void	authentication();
			std::string	findNickname(char *buffer);
			std::string	findUsername(char *buffer);
			void	setNickClient(std::string nick);
			void	setUserClient(std::string user);*/

			int		nicknameUsed(std::string nick);
			int		usernameUsed(std::string user);

			class sendException : public std::exception
			{
			public:
				virtual const char *what() const throw();
			};
			class pollException : public std::exception
			{
			public:
				virtual const char *what() const throw();
			};

	private:
			unsigned int				_port;
			std::string					_password;
			unsigned int				_nbClient;
			unsigned int				_nbClientMax;
			std::vector<struct pollfd>	_pfds;
			struct pollfd				_pfdstmp;
			std::map<int, Client *>		_clients;
			int							_socket;
};

#endif