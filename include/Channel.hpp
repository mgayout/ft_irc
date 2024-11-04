/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:13:42 by biaroun           #+#    #+#             */
/*   Updated: 2024/11/01 15:58:44 by mgayout          ###   ########.fr       */
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

			const std::string			&getName();
			const std::string			&getPassword();
			const std::string			&getTopic();
			const std::string			&getTopicUser();
			const std::string			&getTopicTime();
			const std::string			&getDate();
			const bool					&getI();
			const bool					&getT();
			const unsigned int			&getMaxClient();
			std::vector<std::string>	&getInvited();
			std::vector<std::string>	&getMembers();
			std::vector<std::string>	&getOp();
			int							getNbClient();

			void	setPassword(std::string password);
			void	setTopic(std::string topic);
			void	setI(bool i);
			void	setT(bool t);
			void	setMaxClient(unsigned int max);

			bool	isOp(std::string nickname);
			bool	isInvited(std::string nickname);
			bool	isMember(std::string nickname);
			void	addOp(std::string nickname);
			void	addInvited(std::string nickname);
			void	addMember(std::string nickname);
			void	removeOp(std::string nickname);
			void	removeInvited(std::string nickname);
			void	removeMember(std::string nickname);
			void	clearOp();
			void	clearInvited();
			void	clearMember();
			void	clearAll();
			void	clearClient(std::string nickname);

	private:
			std::string						_name;
			std::string						_password;
			std::string						_topic;
			std::string						_topicUser;
			std::string						_topicTime;
			std::string						_date;
            bool        					_i;
			bool							_t;
            unsigned int					_maxClient;
			std::vector<std::string>		_invited;
			std::vector<std::string>		_members;
			std::vector<std::string>		_op;
};

#endif