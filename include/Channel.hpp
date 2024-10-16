/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:42 by biaroun           #+#    #+#             */
/*   Updated: 2024/10/11 17:54:40 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include "Server.hpp"

class Client;

class	Channel
{
	public:
			Channel(Client *fonda, std::string name, std::string password);
			~Channel();

			void	addMember(Client *client, std::string password);
			void	removeMember(Client *client);
            bool    isOP(Client *client);
			bool	isInvited(Client *client);
			bool	isInviteOnly();
			bool	isMember(Client *client);
			bool	isTopicProtected();

			void	ADDInvited(Client *client);
            
			void	OP(Client *client);
			void	DEOP(Client *client);
			void	setTopicChange(bool b);
			void	setTopic(std::string topic);
			void	setPassword(std::string password);
            void    setPrivate(bool priv);
			void	setMaxClients(int maxClients);
            
			bool	isFull();
            bool    getPrivate();
			std::string getPassword();
			std::string	getName();
			std::string	getTopic();

			void	SendMessChanAll(std::string msg);
			void	SendMessChan(std::string msg, Client *send);
			Client  *findClient(std::string nick);

	private:
			std::string						_name;
			std::string						_password;
			std::string						_topic;
            bool        					_private;
			bool							_TopicChange;
			bool							_limitClients;
            unsigned int					_maxClients;
			std::set<Client*>				_invited;
			std::map<Client*, std::string>	_members;
};

#endif