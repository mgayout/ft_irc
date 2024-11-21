/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:08:09 by mgayout           #+#    #+#             */
/*   Updated: 2024/09/27 10:08:09 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Server.hpp"

class	Client
{
	public:
			Client(int socket);
			~Client();
			bool	isAuthenticated();
			void	addChannel(std::string channel);
			void	removeChannel(std::string channel);

			const int					&getSocket();
			const std::string			&getNickname();
			const std::string			&getUsername();
			const std::string			&getRealname();
			const bool					&getPwd();
			const bool					&getNick();
			const bool					&getUser();
			const bool					&getReal();
			const bool					&getHexchat();
			std::vector<std::string>	getChannel();

			void						setNickname(const std::string nick);
			void						setUsername(const std::string user);
			void						setRealname(const std::string real);
			void						setPwd(bool b);
			void						setNick(bool b);
			void						setUser(bool b);
			void						setReal(bool b);
			void						setHexchat(bool b);

	private:
			int							_socket;
			std::string					_nickname;
			std::string					_username;
			std::string					_realname;
			bool						_pwd;
			bool						_nick;
			bool						_user;
			bool						_real;
			bool						_hexchat;
			std::vector<std::string>	_channels;
};

#endif