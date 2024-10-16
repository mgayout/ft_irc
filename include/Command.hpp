/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:05:57 by mgayout           #+#    #+#             */
/*   Updated: 2024/10/16 14:05:57 by mgayout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Utils.hpp"

std::string		join(std::string arg, Client *client);
std::string		joinPsswrd(std::string arg, Client *client);
std::string		joinDefault(std::string arg, Client *client);
std::string		part(std::string arg, Client *client);
std::string		partDefault(std::string arg, Client *client);
std::string		partReason(std::string arg, Client *client);
std::string		kick(std::string arg, Client *client);
std::string		kickDefault(std::string arg, Client *client);
std::string		kickReason(std::string arg, Client *client);
std::string		invite(std::string arg, Client *client);
std::string		topic(std::string arg, Client *client);
std::string		mode(std::string arg, Client *client);
std::string		modeOp(Client *client, Channel *channel, std::string mode, std::vector<std::string> args);
std::string		cap(Client *client);
std::string		pass(std::string arg, Client *client);
std::string		nick(std::string arg, Client *client);
std::string		user(std::string arg, Client *client);
std::string		op(std::string arg, Client *client);
std::string		deop(std::string arg, Client *client);
std::string		msg(std::string arg, Client *client);
std::string		quit(Client *client);
std::string		sendfile(std::string arg, Client *client);
std::string		getfile(std::string arg, Client *client);
std::string		bot(std::string arg, Client *client);

#endif