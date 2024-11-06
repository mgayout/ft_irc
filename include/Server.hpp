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

# include "Utils.hpp"
# include "Client.hpp"
# include "Channel.hpp"

class	Channel;

class	Client;

class	Server
{
	public:
			Server(char *hostname, int port, std::string pwd);
			~Server();

			const std::string			&getHostname();
			const int					&getPort();
			const std::string			&getPassword();
			const std::string			&getVersion();
			const std::string			&getDate();
			const unsigned int			&getNbClient();
			const unsigned int			&getNbClientMax();
			const int					&getSocket();
			const struct sockaddr_in	&getSockstruct();
			const int					&getPollfd(int idClient);
			Client						*getClient(int clientFd);
			Channel						*getChannel(std::string channel);
			Client						*getClientWithUser(std::string username);
			Client						*getClientWithNick(std::string nickname);

			void		createSocket();
			void		launching();
			void		addClient();
			void		clientRequest(unsigned int idClient);
			std::string	commands(std::vector<std::string> command, int clientFd);
			void		closeServer();

			std::vector<std::string>	splitBuffer(std::string buf);
			int							nicknameUsed(std::string nick);
			void						sendChannel(std::string channelname, std::string sender, std::string message);
			void						sendAll(std::string username, std::string msg);
			void						removeChannel(std::string channel);

			# include "Command.hpp"
			# include "Message.hpp"
			# include "ServerException.hpp"

	private:
			std::string							_hostname;
			int									_port;
			std::string							_password;
			std::string							_version;
			std::string							_date;
			unsigned int						_nbClient;
			unsigned int						_nbClientMax;
			std::vector<struct pollfd>			_pfds;
			struct pollfd						_pfdstmp;
			std::map<int, Client *>				_clients;
			int									_socket;
			struct sockaddr_in					_sockstruct;
			std::map<std::string, Channel *>	_channels;
};

#endif